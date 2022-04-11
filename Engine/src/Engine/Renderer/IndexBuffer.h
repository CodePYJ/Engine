#pragma once

#include "Engine/Core/Core.h"

namespace EE {

	class EE_API IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(const void* data, unsigned int count);
		~IndexBuffer();

		void Bind();
		void Unbind();

		unsigned int GetCount() { return m_Count; }

	private:
		unsigned int m_Count;
		unsigned int m_RendererID;
	};

}



