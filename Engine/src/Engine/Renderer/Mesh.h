#pragma once

#include "Engine/EEpch.h"
#include <glm/glm.hpp>

#include "Engine.h"
#include "Texture.h"


namespace EE {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	//struct Textrue
	//{

	//};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh();

		void SetupMesh();
		void Draw();
		void SetViewProjection(glm::mat4 view_projection);

	private:
		std::shared_ptr<VertexArray> vao = nullptr;
		std::shared_ptr<VertexBuffer> vbo = nullptr;
		std::shared_ptr<IndexBuffer> ebo = nullptr;
		std::shared_ptr<Shader> shader_test = nullptr;

		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<Texture> m_textures;
		glm::mat4 m_view_projection;
	};
}


