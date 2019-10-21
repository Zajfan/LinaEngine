/*
Author: Inan Evin
www.inanevin.com

Copyright 2018 Inan Evin

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
and limitations under the License.

Class: MeshRendererComponent
Timestamp: 4/14/2019 1:37:59 AM

*/

#pragma once

#ifndef RenderableMeshComponent_HPP
#define RenderableMeshComponent_HPP

#include "ECS/ECSComponent.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/Material.hpp"

using namespace LinaEngine::Graphics;

namespace LinaEngine::ECS
{


	struct MeshRendererComponent : public ECSComponent<MeshRendererComponent>
	{
		VertexArray* vertexArray = nullptr;
		MeshMaterial* material = nullptr;
	};
}


#endif