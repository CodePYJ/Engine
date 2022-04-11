#pragma once

#include "Engine/Core/Core.h"

namespace EE {
	
	class EE_API VertexBuffer
	{
	public:
		VertexBuffer(unsigned int size);
		~VertexBuffer();

		void Bind();
		void Unbind();
		void SetData(const void* data, uint32_t size);
	private:
		unsigned int m_RendererID;
	};

}



