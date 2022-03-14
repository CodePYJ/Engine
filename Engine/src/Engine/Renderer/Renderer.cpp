#include "Renderer.h"
#include <glad/glad.h>

namespace EE {

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::Draw(VertexArray& vao, IndexBuffer& ebo, Shader& shader)
	{
		shader.Bind();
		vao.Bind();
		ebo.Bind();
		glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}