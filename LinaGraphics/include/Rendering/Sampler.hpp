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
Class: Sampler

Represents a data structure for texture samplers created in the GPU backend.

Timestamp: 4/26/2019 6:20:27 PM
*/

#pragma once

#ifndef Sampler_HPP
#define Sampler_HPP

#include "PackageManager/PAMRenderDevice.hpp"

namespace LinaEngine::Graphics
{
	class Sampler
	{
	public:

		Sampler() {};

		// Destructor releases sampler data through render engine
		FORCEINLINE ~Sampler()
		{
			m_EngineBoundID = renderDevice->ReleaseSampler(m_EngineBoundID);
		}

		FORCEINLINE void Construct(RenderDevice& deviceIn, SamplerParameters samplerParams, TextureBindMode bindMode)
		{
			renderDevice = &deviceIn;
			m_EngineBoundID = renderDevice->CreateSampler(samplerParams);
			m_TargetBindMode = bindMode;
			m_Params = samplerParams;
		}

		FORCEINLINE void UpdateSettings(SamplerParameters samplerParams) 
		{
			m_Params = samplerParams;
			renderDevice->UpdateSamplerParameters(m_EngineBoundID, samplerParams);
			renderDevice->UpdateTextureParameters(m_TargetBindMode, m_TargetTextureID, samplerParams);
		}

		FORCEINLINE SamplerParameters& GetSamplerParameters() { return m_Params; }

		FORCEINLINE uint32 GetID() const { return m_EngineBoundID; }
		FORCEINLINE void SetTargetTextureID(uint32 id) { m_TargetTextureID = id; }
	private:

		uint32 m_TargetTextureID;
		TextureBindMode m_TargetBindMode;
		SamplerParameters m_Params;
		RenderDevice* renderDevice;
		uint32 m_EngineBoundID;


	};
}


#endif