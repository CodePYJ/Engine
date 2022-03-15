#pragma once

#include "Engine/Core/Core.h"

namespace EE {
	
	class EE_API VertexBuffer
	{
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void Bind();
		void Unbind();
	private:
		unsigned int m_RendererID;
	};

}



