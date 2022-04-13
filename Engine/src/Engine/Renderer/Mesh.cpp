#include "Mesh.h"
#include <glad/glad.h>

namespace EE {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		:m_vertices(vertices), m_indices(indices), m_textures(textures)
	{
		SetupMesh();
	}

	Mesh::~Mesh()
	{

	}
	void Mesh::SetupMesh()
	{
		vao = std::make_shared<VertexArray>();
		vbo = std::make_shared<VertexBuffer>(sizeof(Vertex) * m_vertices.size(), &m_vertices[0]);
		ebo = std::make_shared<IndexBuffer>(&m_indices[0], m_indices.size());
		vao->AddEBO(ebo);

		VertexBufferLayout layout;
		layout.PushFloat(3);	//position
		layout.PushFloat(3);	//normal
		layout.PushFloat(2);	//texcoords

		vao->AddBuffer(*vbo, layout);
		shader_test = std::make_shared<Shader>("assets/shaders/mesh.shader");
		vao->Unbind();
	}

	void Mesh::Draw()
	{
		/*for (int i = 0; i < m_textures.size(); i++) {
			if (m_textures[i].type == "diffuse") {
				m_textures[i].Bind(i);
				shader_test->Bind();
				shader_test->SetUniform1i("diffuse", 0);
			}
			else if (m_textures[i].type == "specular") {
				m_textures[i].Bind(i);
			}
		}*/

		vao->Bind();
		vbo->Bind();
		shader_test->Bind();
		shader_test->SetUniformMat4("u_ViewProjection", m_view_projection);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		vao->Unbind();
		vbo->Unbind();
		//shader_test->Unbind();
		//m_textures[i].Unbind();
		
	}
	void Mesh::SetViewProjection(glm::mat4 view_projection)
	{
		m_view_projection = view_projection;
	}
}