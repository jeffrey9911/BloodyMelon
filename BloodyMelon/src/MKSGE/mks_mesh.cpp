#include "mks_mesh.h"
#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
mks_mesh::mks_mesh(std::vector<struVertex> vertices, std::vector<GLuint> indices, std::vector<struTexture> textures)
{
	this->meshVertices;
	this->meshIndices;
	this->meshTextures;

	meshSetup();
}

void mks_mesh::meshDraw(mks_shader& shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint normalNr = 1;
	GLuint heightNr = 1;
	for (GLuint i = 0; i < meshTextures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string aNumber;
		std::string aName = meshTextures[i].texType;
		if (aName == "tex_diff") {
			aNumber = std::to_string(diffuseNr++);
		}
		else if (aName == "tex_spec")
		{
			aNumber = std::to_string(specularNr++);
		}
		else if (aName == "tex_norm") {
			aNumber = std::to_string(normalNr++);
		}
		else if (aName == "tex_height") {
			aNumber = std::to_string(heightNr++);
		}

		glUniform1i(glGetUniformLocation(shader.shaderID, (aName + aNumber).c_str()), i);

		glBindTexture(GL_TEXTURE_2D, meshTextures[i].texID);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, meshIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void mks_mesh::meshSetup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, meshVertices.size() * sizeof(struVertex), &meshVertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshIndices.size() * sizeof(GLuint), &meshIndices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struVertex), (void*)offsetof(struVertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(struVertex), (void*)offsetof(struVertex, texVerts));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(struVertex), (void*)offsetof(struVertex, tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(struVertex), (void*)offsetof(struVertex, bitangent));

	glBindVertexArray(0);
}
