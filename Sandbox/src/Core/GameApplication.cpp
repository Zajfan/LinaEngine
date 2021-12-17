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

#include "Core/GameApplication.hpp"
#include "Core/EditorApplication.hpp"
#include "Core/Engine.hpp"

namespace Lina
{
	void GameApplication::Initialize(ApplicationInfo appInfo)
	{
		Application::Initialize(appInfo);

		if (appInfo.m_appMode == ApplicationMode::Editor)
		{	
			m_editor = new Editor::EditorApplication();
			m_editor->Initialize();
			m_editor->Refresh();

			// Update props.
			auto& windowProps = Graphics::WindowBackend::Get()->GetProperties();

			// Set the app window size back to original after loading editor resources.
			Graphics::WindowBackend::Get()->SetPos(Vector2::Zero);
			Graphics::WindowBackend::Get()->SetSize(Vector2(windowProps.m_workingAreaWidth, windowProps.m_workingAreaHeight));

			Lina::Engine::Get()->SetPlayMode(false);
		}
		else
		{
			Lina::Engine::Get()->StartLoadingResources();
			Lina::Engine::Get()->SetPlayMode(true);
		}

		// Initialize game manager.
		m_gameManager.Initialize();

		// Set vsync
		// Graphics::WindowBackend::Get()->SetVsync(2);

		 Run();

		// After engine has finished running.
		if (m_editor != nullptr)
			delete m_editor;

	}
}


int main(int argc, char** argv)
{
	Lina::GameApplication* game = new Lina::GameApplication();
	ApplicationInfo appInfo;
	appInfo.m_appMode = ApplicationMode::Editor;
	appInfo.m_appName = "Lina Sandbox Game";
	appInfo.m_bundleName = "Example";
	appInfo.m_windowProperties.m_width = 1440;
	appInfo.m_windowProperties.m_height = 900;
	appInfo.m_windowProperties.m_windowState = WindowState::Maximized;
	appInfo.m_windowProperties.m_decorated = false;
	appInfo.m_windowProperties.m_resizable = true;
	appInfo.m_windowProperties.m_fullscreen = false;
	appInfo.m_windowProperties.m_msaaSamples = 4;
	appInfo.m_windowProperties.m_title = "Lina Engine - Configuration [] - Build Type [] - Project [] - Build []";
	game->Initialize(appInfo);
	delete game;
}