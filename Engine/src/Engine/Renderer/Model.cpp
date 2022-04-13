#include "Model.h"
#include <glm/glm.hpp>


namespace EE {
	Model::Model(const std::string path)
	{
		LoadModel(path);
	}

	Model::~Model()
	{

	}

	void Model::LoadModel(const std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			EE_ERROR(importer.GetErrorString());
			return;
		}
		//directory = path.substr(0, path.find_last_of('\\'));

		ProcessNode(*scene->mRootNode, *scene);
	}

	Mesh Model::ProcessMesh(aiMesh& mesh, const aiScene& scene)
	{
		std::vector<Vertex> temp_vertices;
		std::vector<unsigned int> temp_indices;
		std::vector<Texture> temp_textures;
		
		for (unsigned int i = 0; i < mesh.mNumVertices; i++) {
			Vertex ver;
			ver.position.x = mesh.mVertices[i].x;
			ver.position.y = mesh.mVertices[i].y;
			ver.position.z = mesh.mVertices[i].z;

			ver.normal.x = mesh.mNormals[i].x;
			ver.normal.y = mesh.mNormals[i].y;
			ver.normal.z = mesh.mNormals[i].z;
			if (mesh.mTextureCoords[0]) {
				ver.texCoords.x = mesh.mTextureCoords[0][i].x;
				ver.texCoords.y = mesh.mTextureCoords[0][i].y;
			}
			else
				ver.texCoords = glm::vec2(0.0f, 0.0f);
			temp_vertices.push_back(ver);
		}

		for (unsigned int i = 0; i < mesh.mNumFaces; i++) {
			for (int j = 0; j < mesh.mFaces[i].mNumIndices; j++) {
				temp_indices.push_back(mesh.mFaces[i].mIndices[j]);
			}
		}

		return Mesh(temp_vertices, temp_indices, {});
	}

	void Model::Draw()
	{
		for (Mesh mesh : meshes) {
			mesh.SetViewProjection(m_view_projection);
			mesh.Draw();
		}
	}

	void Model::SetViewProjection(glm::mat4 view_projection)
	{
		m_view_projection = view_projection;
	}

	void Model::ProcessNode(aiNode& node, const aiScene& scene)
	{
		for (int i = 0; i < node.mNumMeshes; i++) {
			aiMesh* curMesh = scene.mMeshes[node.mMeshes[i]];
			meshes.push_back(ProcessMesh(*curMesh, scene));
		}
		for (int i = 0; i < node.mNumChildren; i++) {
			ProcessNode(*node.mChildren[i], scene);
		}
	}

}