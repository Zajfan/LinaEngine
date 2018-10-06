/*
Author: Inan Evin
www.inanevin.com

BSD 2-Clause License
Lina Engine Copyright (c) 2018, Inan Evin All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.

-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO
-- THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
-- BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
-- GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
-- STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
-- OF SUCH DAMAGE.

4.0.30319.42000
10/4/2018 1:00:21 AM

*/

#pragma once

#ifndef Lina_InputHandler_H
#define Lina_InputHandler_H
#include <Lina_InputBinding.h>
#include <list>
#include <Lina_EventDispatcher.h>



class Lina_InputHandler
{

public:
	Lina_InputHandler();
	const Uint8 *state;
	std::list<Lina_InputBinding> mousePressEventContainers;
	std::list<Lina_InputBinding> keyPressEventContainers;
	void Bind(Lina_InputBinding& binding);
	void Unbind(Lina_InputBinding& binding);
	void Update();
	void HandleEvents(SDL_Event& e);
	Lina_EventDispatcher inputDispatcher;

	/* INPUT HANDLER EVENTS */
	Lina_Event<SDL_Scancode> onKey;
	Lina_Event<SDL_Scancode> onKeyDown;
	Lina_Event<SDL_Scancode> onKeyUp;
	Lina_Event<int> onMouse;
	Lina_Event<int> onMouseDown;
	Lina_Event<float, float> onMouseMotion;


};


#endif