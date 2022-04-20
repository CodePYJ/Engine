#include "Mesh.h"
#include <glad/glad.h>

namespace EE {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		:m_vertices(vertices), m_indices(indices), m_textures(textures)
	{
		SetupMesh(m_shader_path);
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, std::string shader_path)
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
		//float ambientStrength;
		//float specularStrength;
		//int specularIndex;
		//vec3 lightPos;
		//vec3 lightColor;
		vao->Bind();
		vbo->Bind();
		shader_test->Bind();
		shader_test->SetUniformMat4("u_transform", m_property.transform);
		shader_test->SetUniform3f("u_color", m_property.color);
		shader_test->SetUniform1i("u_entity", m_property.entity);
		shader_test->SetUniform1f("specularStrength", m_property.specularStrength);
		shader_test->SetUniform1i("shininess", m_property.shininess);
		//GLuint indices[3];
		//const GLchar* names[] = { "lightCount", "lights[0]", "lights[1]" };
		//glGetUniformIndices(shader_test->GetId(), 3, names, indices);
		//EE_TRACE(indices[0]);
		//EE_TRACE(indices[1]);
		//EE_TRACE(indices[2]);
		//int blocksize = 0;
		//int offset[3];
		//glGetActiveUniformBlockiv(shader_test->GetId(), 1, GL_UNIFORM_BLOCK_DATA_SIZE, &blocksize);
		//glGetActiveUniformsiv(shader_test->GetId(), 3, indices, GL_UNIFORM_OFFSET, offset);
		//EE_TRACE(blocksize);
		//EE_TRACE(offset[0]);
		//EE_TRACE(offset[1]);
		//EE_TRACE(offset[2]);

		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		vao->Unbind();
		vbo->Unbind();

		//shader_test->Unbind();
		//m_textures[i].Unbind();
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
}