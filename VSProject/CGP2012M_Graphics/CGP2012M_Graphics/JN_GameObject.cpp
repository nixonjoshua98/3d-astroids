#include "JN_GameObject.h"
#include "JN_Shader.h"

#include <ctime>

float GetTime()
{
	return (time(0) % 3600);
}

JN_GameObject::JN_GameObject()
{
}


JN_GameObject::~JN_GameObject()
{
}

void JN_GameObject::SetShaders(std::string v, std::string f)
{
	JN_Shader vShader = JN_Shader(JN_Shader::ShaderType::Vertex, v);
	JN_Shader fShader = JN_Shader(JN_Shader::ShaderType::Fragment, f);

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vShader.GetShaderID());
	glAttachShader(shaderProgram, fShader.GetShaderID());
	glLinkProgram(shaderProgram);
}
