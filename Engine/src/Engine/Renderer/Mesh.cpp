#include "Mesh.h"
#include <glad/glad.h>

namespace EE {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures)
		:m_vertices(vertices), m_indices(indices), m_textures(textures)
	{
		SetupMesh(m_shader_path);
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures, std::string shader_path)
		:m_vertices(vertices), m_indices(indices), m_textures(textures), m_shader_path(shader_path)
	{
		SetupMesh(m_shader_path);
	}

	Mesh::~Mesh()
	{

	}
	void Mesh::SetupMesh(std::string shader_path)
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

		shader_test = std::make_shared<Shader>(shader_path);
		vao->Unbind();
	}

	void Mesh::Draw()
	{
		vao->Bind();
		vbo->Bind();
		shader_test->Bind();

		//for (int i = 0; i < m_textures.size(); i++) {
		//	m_textures[i]->Bind(i);
		//}
		if (texture_ptr)
			texture_ptr->Bind();
		shader_test->SetUniformMat4("u_transform", m_property.transform);
		shader_test->SetUniform3f("u_color", m_property.color);
		shader_test->SetUniform1i("u_entity", m_property.entity);
		shader_test->SetUniform1f("specularStrength", m_property.specularStrength);
		shader_test->SetUniform1i("shininess", m_property.shininess);

		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		vao->Unbind();
		vbo->Unbind();
		//for (int i = 0; i < m_textures.size(); i++) {
		//	m_textures[i]->Unbind();
		//}
		if (texture_ptr)
			texture_ptr->Unbind();
	}

	void Mesh::DrawLight()
	{
		vao->Bind();
		vbo->Bind();
		shader_test->Bind();
		shader_test->SetUniformMat4("u_transform", m_property.transform);
		shader_test->SetUniform3f("u_color", m_property.color);
		shader_test->SetUniform1i("u_entity", m_property.entity);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		vao->Unbind();
		vbo->Unbind();
	}

	void Mesh::SetMeshProperty(MeshProperty property)
	{
		m_property.transform = property.transform;
		m_property.color = property.color;
		m_property.entity = property.entity;
		m_property.specularStrength = property.specularStrength;
		m_property.shininess = property.shininess;
	}

	void Mesh::AddTexture(std::shared_ptr<Texture> texture)
	{
		texture_ptr = texture;
		//m_textures.push_back(texture);
	}
}



