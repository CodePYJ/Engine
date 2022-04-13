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
		Model(const std::string path);
		~Model();

		void LoadModel(const std::string path);
		void ProcessNode(aiNode& node, const aiScene& scene);
		Mesh ProcessMesh(aiMesh& mesh, const aiScene& scene);
		void Draw();
		void SetViewProjection(glm::mat4 view_projection);

	private:
		std::vector<Mesh> meshes;
		std::string directory = "assets/models";
		glm::mat4 m_view_projection;
	};
}
