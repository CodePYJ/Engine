#include "Renderer.h"
#include <glad/glad.h>

namespace EE {

	Renderer::Renderer()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Draw(VertexArray& vao, IndexBuffer& ebo, Shader& shader)
	{
		shader.Bind();
		vao.Bind();
		ebo.Bind();
		glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}
}