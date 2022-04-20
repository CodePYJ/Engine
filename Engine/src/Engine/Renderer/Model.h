#pragma once

#include "Engine/EEpch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Engine.h"

namespace EE {

	class Model
	{
	public:
		Model() = default;
		Model(const std::string path);
		Model(const std::string path, std::string shader_path);
		~Model();

		void LoadModel(const std::string path);
		void LoadModel(const std::string path, std::string shader_path);
		void ProcessNode(aiNode& node, const aiScene& scene);
		Mesh ProcessMesh(aiMesh& mesh, const aiScene& scene, std::string shader_path);
		void Draw(MeshProperty property);
		void DrawLight(MeshProperty property);

	private:
		std::vector<Mesh> meshes;
		std::string directory = "assets/models";
		glm::mat4 m_view_projection;
		std::string m_shader_path;
	};
}
