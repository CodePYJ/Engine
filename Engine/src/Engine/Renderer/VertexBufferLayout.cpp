#include "VertexBufferLayout.h"
#include <glad/glad.h>


namespace EE {

	unsigned int VertexBufferElement::GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:					return 4;
			case GL_INT:							return 4;
			case GL_UNSIGNED_INT:		return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		//EE_ASSERT(false);
		return 0;
	}

	void VertexBufferLayout::PushFloat(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count ,GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	void VertexBufferLayout::PushInt(unsigned int count)
	{
		m_Elements.push_back({ GL_INT, count ,GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_INT) * count;
	}

	void VertexBufferLayout::PushByte(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count ,GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
}