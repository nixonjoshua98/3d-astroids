#ifndef JN_SQUARE_H
#define JN_SQUARE_H

#include <GL/glew.h>
#include <string>

#include "JN_Texture.h"


class JN_Square
{
public:
	JN_Square();
	~JN_Square();

	void Init(std::string);
	void Render();

private:
	GLuint VBO, VAO, EBO;

	JN_Texture texture;

	GLfloat vertices[32] = {
		 0.1f,  0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
		 0.1f, -0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
		-0.1f, -0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		-0.1f,  0.1f, 0.0f,		 0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	};

	GLuint indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	void SetBuffers();
};

#endif // !JN_SQUARE_H