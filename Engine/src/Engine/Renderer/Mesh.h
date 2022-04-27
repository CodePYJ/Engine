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

	struct MeshProperty {
		glm::mat4 transform;
		glm::vec3 color;
		int entity;
		float specularStrength = 0.2f;
		int shininess = 1;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures);
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures, std::string shader_path);
		~Mesh();

		void SetupMesh(std::string shader_path);
		void Draw();
		void DrawLight();
		void SetMeshProperty(MeshProperty property);
		void AddTexture(std::shared_ptr<Texture> texture);

	private:
		std::shared_ptr<VertexArray> vao = nullptr;
		std::shared_ptr<VertexBuffer> vbo = nullptr;
		std::shared_ptr<IndexBuffer> ebo = nullptr;
		std::shared_ptr<Shader> shader_test = nullptr;

		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<std::shared_ptr<Texture>> m_textures;
		std::shared_ptr<Texture> texture_ptr;
		MeshProperty m_property;
		std::string m_shader_path = "assets/shaders/mesh.shader";
	};

}


