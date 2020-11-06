/*
This file is a part of: Lina Engine
https://github.com/inanevin/LinaEngine

Author: Inan Evin
http://www.inanevin.com

Copyright (c) [2018-2020] [Inan Evin]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "FPSDemo/FPSDemoLevel.hpp"
#include "Core/EditorCommon.hpp"
#include "Rendering/RenderEngine.hpp"
#include "ECS/Components/CameraComponent.hpp"
#include "ECS/Components/FreeLookComponent.hpp"
#include "Core/Application.hpp"
#include "ECS/Components/MeshRendererComponent.hpp"
#include "ECS/Components/SpriteRendererComponent.hpp"
#include "ECS/Components/RigidbodyComponent.hpp"
#include "FPSDemo/HeadbobComponent.hpp"
#include "FPSDemo/PlayerMotionComponent.hpp"
#include "Drawers/ComponentDrawer.hpp"
#include "ECS/Systems/CameraSystem.hpp"
#include "Utility/Math/Matrix.hpp"

namespace LinaEngine
{
	using namespace LinaEngine::ECS;
	using namespace LinaEngine::Graphics;

	bool FPSDemoLevel::Install(bool loadFromFile, const std::string& path, const std::string& levelName)
	{
		Level::Install(loadFromFile, path, levelName);
		return true;
	}

	Matrix portalView(Matrix originalView, Transformation* srcTransform, Transformation* destTransform)
	{
		Vector3 loc = destTransform->GetLocation();
		Quaternion rot = destTransform->GetRotation();
		return Matrix::InitLookAt(loc, loc + rot.GetForward(), rot.GetUp());

		//Matrix mv = originalView * srcTransform->ToMatrix();
		//Vector3 location = srcTransform->GetLocation();
		//Quaternion rotation = srcTransform->GetRotation();
		//Matrix portalCam = mv * Matrix::InitRotation(rotation) * destTransform->ToMatrix().Inverse();
		//return portalCam;
	}

	void FPSDemoLevel::Initialize()
	{
		m_registry = &Application::GetECSRegistry();

		Application::GetApp().PushLayerToPlayStack(m_player);

		RenderEngine& renderEngine = Application::GetRenderEngine();
		RenderDevice& rd = renderEngine.GetRenderDevice();
		Vector2 viewportSize = renderEngine.GetViewportSize();

		// Setup portal rt
		m_portalRTParams.m_textureParams.m_pixelFormat = PixelFormat::FORMAT_RGB;
		m_portalRTParams.m_textureParams.m_internalPixelFormat = PixelFormat::FORMAT_RGBA16F;
		m_portalRTParams.m_textureParams.m_minFilter = m_portalRTParams.m_textureParams.m_magFilter = SamplerFilter::FILTER_LINEAR;
		m_portalRTParams.m_textureParams.m_wrapS = m_portalRTParams.m_textureParams.m_wrapT = SamplerWrapMode::WRAP_REPEAT;
		m_portalTexture.ConstructRTTexture(rd, viewportSize, m_portalRTParams, false);
		m_portalBuffer.Construct(rd, RenderBufferStorage::STORAGE_DEPTH, viewportSize);
		m_portalRT.Construct(rd, m_portalTexture, viewportSize, TextureBindMode::BINDTEXTURE_TEXTURE2D, FrameBufferAttachment::ATTACHMENT_COLOR, FrameBufferAttachment::ATTACHMENT_DEPTH, m_portalBuffer.GetID());

		LinaEngine::Application::GetEngineDispatcher().SubscribeAction<void*>("fpsdemo_preDraw", LinaEngine::Action::ActionType::PreDraw, std::bind(&FPSDemoLevel::PreDraw, this));

		// Component drawer.
		m_componentDrawer.AddComponentDrawFunctions();

		
	}

	void FPSDemoLevel::Tick(bool isInPlayMode, float delta)
	{
		if (!m_isInPlayMode && isInPlayMode)
		{
			ECSEntity fpsCam = m_registry->GetEntity("FPS Cam");

			if (fpsCam != entt::null)
				LinaEngine::Application::GetRenderEngine().GetCameraSystem()->SetActiveCamera(fpsCam);
		}

		m_isInPlayMode = isInPlayMode;
	}

	void FPSDemoLevel::SerializeRegistry(LinaEngine::ECS::ECSRegistry& registry, cereal::BinaryOutputArchive& oarchive)
	{
		entt::snapshot{ registry }
			.entities(oarchive)
			.component<
			LinaEngine::ECS::ECSEntityData,
			LinaEngine::ECS::CameraComponent,
			LinaEngine::ECS::FreeLookComponent,
			LinaEngine::ECS::PointLightComponent,
			LinaEngine::ECS::DirectionalLightComponent,
			LinaEngine::ECS::SpotLightComponent,
			LinaEngine::ECS::RigidbodyComponent,
			LinaEngine::ECS::MeshRendererComponent,
			LinaEngine::ECS::SpriteRendererComponent,
			LinaEngine::ECS::TransformComponent,
			LinaEngine::ECS::HeadbobComponent,
			LinaEngine::ECS::PlayerMotionComponent
			>(oarchive);
	}

	void FPSDemoLevel::DeserializeRegistry(LinaEngine::ECS::ECSRegistry& registry, cereal::BinaryInputArchive& iarchive)
	{
		entt::snapshot_loader{ registry }
			.entities(iarchive)
			.component<
			LinaEngine::ECS::ECSEntityData,
			LinaEngine::ECS::CameraComponent,
			LinaEngine::ECS::FreeLookComponent,
			LinaEngine::ECS::PointLightComponent,
			LinaEngine::ECS::DirectionalLightComponent,
			LinaEngine::ECS::SpotLightComponent,
			LinaEngine::ECS::RigidbodyComponent,
			LinaEngine::ECS::MeshRendererComponent,
			LinaEngine::ECS::SpriteRendererComponent,
			LinaEngine::ECS::TransformComponent,
			LinaEngine::ECS::HeadbobComponent,
			LinaEngine::ECS::PlayerMotionComponent
			>(iarchive);
	}


	void FPSDemoLevel::PreDraw()
	{
		if (!m_isInPlayMode) return;
		RenderEngine& renderEngine = Application::GetRenderEngine();
		RenderDevice& rd = renderEngine.GetRenderDevice();
		Vector2 viewportSize = renderEngine.GetViewportSize();

		TransformComponent& p1tr = m_registry->get<TransformComponent>(m_registry->GetEntity("Portal1"));
		TransformComponent& p2tr = m_registry->get<TransformComponent>(m_registry->GetEntity("Portal2"));

		rd.SetFBO(m_portalRT.GetID());
		rd.SetViewport(Vector2::Zero, viewportSize);

		// Clear color.
		rd.Clear(true, true, true, renderEngine.GetCameraSystem()->GetCurrentClearColor(), 0xFF);
		Matrix vm = portalView(renderEngine.GetCameraSystem()->GetViewMatrix(), &p1tr.transform, &p2tr.transform);
		//renderEngine.GetCameraSystem()->InjectViewMatrix(Matrix::Identity());

		LINA_CLIENT_TRACE("Updating from client");
		//	renderEngine.UpdateSystems();

		//	renderEngine.DrawSceneObjects(renderEngine.GetMainDrawParams());



		Material::GetMaterial(m_registry->get<MeshRendererComponent>(m_registry->GetEntity("Portal1")).m_materialID).SetTexture(MAT_TEXTURE2D_DIFFUSE, &m_portalTexture);
	}
}