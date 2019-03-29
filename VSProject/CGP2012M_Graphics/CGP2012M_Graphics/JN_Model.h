#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>


class JN_Model
{
public:
	JN_Model();
	~JN_Model();

	std::vector<glm::vec3> vertices;
	std::vector<GLuint> indices;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	std::vector<GLfloat> modelData;

	GLuint VBO, VAO;

	void SetBuffers();
	void Render();
};

