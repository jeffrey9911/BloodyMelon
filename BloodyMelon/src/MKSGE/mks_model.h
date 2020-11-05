#pragma once
#include <iostream>
#include <MKSGE/mks_mesh.h>
#include<MKSGE/mks_shader.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/scene.h>



GLuint textureFile(std::string textureFilePath, const std::string& directory, bool ifGamma = false);
class mks_model
{
public:
	// Data
	std::vector<struVertex> textureStore;
	std::vector<mks_mesh> meshes;
	std::string directory;
	bool isGammaCorrect;

	mks_model(std::string const& filePath, bool ifGamma = false);

	void drawModel(mks_shader& shaderID);

private:
	void loadModel(std::string const& filePath);

	void processNodes(aiNode* node, const aiScene* scene);

	mks_mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<struTexture> loadMaterial(aiMaterial* materi, aiTextureType type, std::string typeName);
};

