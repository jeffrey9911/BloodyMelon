#include "mks_model.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <glad/glad.h>
#include <MKSGE/mks_mesh.h>
#include <MKSGE/mks_shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GLFW/glfw3.h>
#include <assimp/scene.h>

GLuint textureFile(std::string textureFilePath, const std::string& directory, bool ifGamma) {
	std::string fileName = std::string(textureFilePath);
	fileName = directory + '/' + fileName;

	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;

	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);

	if (data) {
		GLenum format;
		if (nrComponents == 1) {
			format = GL_RED;
		}
		else if (nrComponents == 3) {
			format = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			format == GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

	}
	else {
		std::cout << std::endl << "[X] - Failed to load texture: " << textureFilePath;
		stbi_image_free(data);
	}
	return textureID;
}


mks_model::mks_model(std::string const& filePath, bool ifGamma) : isGammaCorrect(ifGamma) {
	mks_model::loadModel(filePath);
}

void mks_model::drawModel(mks_shader& shaderID) {
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		meshes[i].meshDraw(shaderID);
	}
}

void  mks_model::loadModel(std::string const& filePath) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << std::endl << "[X] - Failed to Assimp import: " << importer.GetErrorString();
		return;
	}

	directory = filePath.substr(0, filePath.find_last_of('/'));

	processNodes(scene->mRootNode, scene);
}

void mks_model::processNodes(aiNode* node, const aiScene* scene) {
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNodes(node->mChildren[i], scene);
	}
}

mks_mesh mks_model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<struVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<struTexture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		struVertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texVerts = vec;

			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.tangent = vector;

			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.bitangent = vector;
		}
		else {
			vertex.texVerts = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<struTexture> diffuseMaps = loadMaterial(material, aiTextureType_DIFFUSE, "tex_diff");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	std::vector<struTexture> specularMaps = loadMaterial(material, aiTextureType_SPECULAR, "tex_spec");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	std::vector<struTexture> normalMaps = loadMaterial(material, aiTextureType_HEIGHT, "tex_norm");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	std::vector<struTexture> heightMaps = loadMaterial(material, aiTextureType_AMBIENT, "tex_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return mks_mesh(vertices, indices, textures);
}