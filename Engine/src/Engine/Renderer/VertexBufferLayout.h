#pragma once

#include "Engine/EEpch.h"
#include "Engine/Core/Core.h"


namespace EE {

	struct EE_API VertexBufferElement
	{
		unsigned int type;
		unsigned int	count;
		unsigned char normalized;
		static unsigned int GetSizeOfType(unsigned int type);
	};

	class EE_API VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			:m_Stride(0) {
			
		}

		void PushFloat(unsigned int count);
		void PushInt(unsigned int count);
		void PushByte(unsigned int count);
		
		inline const std::vector<VertexBufferElement> GetElements() { return m_Elements; }
		inline unsigned int GetStride() { return m_Stride; }

	private:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride;
	};
}

