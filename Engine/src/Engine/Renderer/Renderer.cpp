#include "Renderer.h"
#include <glad/glad.h>

namespace EE {

	void Renderer::Clear()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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