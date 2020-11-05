#pragma once
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <MKSGE/mks_shader.h>

struct struVertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texVerts;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct struTexture {
	GLuint texID;
	std::string texType;
	std::string texPath;
};

class mks_mesh
{
public:
	std::vector<struVertex> meshVertices;
	std::vector<GLuint> meshIndices;
	std::vector<struTexture> meshTextures;
	GLuint VAO;

	mks_mesh(std::vector<struVertex> vertices, std::vector<GLuint> indices, std::vector<struTexture> textures);
	void meshDraw(mks_shader& shader);
	
private:
	GLuint VBO, EBO;
	void meshSetup();
};

