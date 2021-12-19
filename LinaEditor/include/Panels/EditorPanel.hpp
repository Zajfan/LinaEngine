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

/*
Class: EditorPanel

Base class defining functions for all panels.

Timestamp: 5/23/2020 4:16:05 PM
*/

#pragma once

#ifndef EditorPanel_HPP
#define EditorPanel_HPP

#include "Math/Vector.hpp"

namespace Lina::Editor
{
	class GUILayer;

	class EditorPanel
	{	

	public:
		
		EditorPanel() { };
		virtual ~EditorPanel() {};
		virtual void Initialize(const char* id);
		virtual void Draw() = 0;
		virtual void Open() { m_show = true; }
		virtual void Close() { m_show = false; }
		virtual void ToggleCollapse();
		virtual void ToggleMaximize();
		virtual bool CanDrawContent();

	protected:

		bool m_show = true;
		bool m_collapsed = false;
		bool m_maximized = false;
		Lina::Vector2 m_sizeBeforeMaximize = Lina::Vector2::Zero;
		Lina::Vector2 m_sizeBeforeCollapse = Lina::Vector2::Zero;
		Lina::Vector2 m_posBeforeMaximize = Lina::Vector2::Zero;
		const char* m_id;
		int m_windowFlags;
	};
}

#endif
