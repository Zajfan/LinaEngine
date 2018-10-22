/*
Author: Inan Evin
www.inanevin.com

MIT License

Lina Engine, Copyright (c) 2018 Inan Evin

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

4.0.30319.42000
9/30/2018 4:59:45 PM

*/

#pragma once

#ifndef Lina_RenderingEngine_H
#define Lina_RenderingEngine_H

//#include<list>
#include "Rendering/Lina_Window.h"
#include "Core/Lina_ObjectHandler.h"
#include "Math/Lina_Vector3F.h"
#include "Rendering/Lights/Lina_DirectionalLight.h"

class Lina_PhongShader;
class Lina_BasicShader;
class Lina_ForwardAmbientShader;
class Lina_ForwardDirectionalShader;
class Lina_Camera;
class Lina_GameCore;
class Lina_Actor;

class Lina_RenderingEngine
{

public:

	Lina_RenderingEngine();
	~Lina_RenderingEngine();

	void SetCurrentActiveCamera(Lina_Camera*);
	Lina_Camera* GetCurrentActiveCamera();
	
	Lina_Window* m_GameWindow;

	Lina_ObjectHandler eventHandler;
	Lina_PhongShader* GetPhongShader();
	Lina_BasicShader* GetBasicShader();

	float GetAspectRatio();
	int GetScreenWidth();
	int GetScreenHeight();

	Lina_Vector3F GetAmbientLight();
	Lina_DirectionalLight GetDirectionalLight();

private:

	friend class Lina_Core;

	void Initialize(Lina_GameCore*);
	void Render();
	void CleanUp();
	void ClearScreen();

	void InitializeShaders();
	void SetTextures(bool);
	void ClearColors(float, float, float, float);
	void CreateDisplayWindow();

	Lina_BasicShader* basicShader;
	Lina_PhongShader* phongShader;
	Lina_ForwardAmbientShader* forwardAmbientShader;
	Lina_ForwardDirectionalShader* forwardDirectionalShader;

	Lina_Camera* currentActiveCamera;
	Lina_GameCore* game;

	int screenHeight = 0;
	int screenWidth = 0;
	std::string screenTitle = "";

	Lina_RenderingEngine(const Lina_RenderingEngine&) = delete;
	Lina_RenderingEngine& operator= (const Lina_RenderingEngine&) = delete;

	Lina_Vector3F ambientLight = Vector3(0.3f, 0.3f, 0.3f);
	Lina_DirectionalLight directionalLight;
	
};


#endif