#include "VertexArray.h"
#include <glad/glad.h>

namespace EE {

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	
	void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		unsigned int	offset = 0;
		const std::vector<VertexBufferElement>& elements = layout.GetElements();
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void *)offset);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}