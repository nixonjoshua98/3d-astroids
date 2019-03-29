#include "JN_Square.h"
#include "JN_Shader.h"


JN_Square::JN_Square()
{
}


JN_Square::~JN_Square()
{
}


void JN_Square::Init(std::string texFile, std::string vertexShaderFile, std::string fragmentShaderFile)
{
	JN_Shader vShader = JN_Shader(JN_Shader::ShaderType::Vertex, vertexShaderFile);
	JN_Shader fShader = JN_Shader(JN_Shader::ShaderType::Fragment, fragmentShaderFile);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vShader.GetShaderID());
	glAttachShader(shaderProgram, fShader.GetShaderID());
	glLinkProgram(shaderProgram);

	texture.Load(texFile.c_str());

	SetBuffers();
}


void JN_Square::Render()
{
	// Using
	glUseProgram(shaderProgram);

	// Binds
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// Binds
	glBindVertexArray(0);
}


void JN_Square::SetBuffers()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}
