
#include "JN_Shader.h"

#include <fstream>


// Default constructor
JN_Shader::JN_Shader()
{

}


// Constructor overload
JN_Shader::JN_Shader(ShaderType type, std::string path)
{
	this->type = type;
	
	Load(path);
	Compile();
}


JN_Shader::~JN_Shader()
{
	glDeleteShader(shaderID);
}


// Load the shader file into memory
void JN_Shader::Load(std::string path)
{
	std::ifstream inFile(path);

	while (inFile.good())
	{
		std::string line;
		std::getline(inFile, line);
		shaderText.append(line + "\n");
	}

	codePtr = shaderText.c_str();
}


// Compile the shader program
void JN_Shader::Compile()
{
	switch (type)
	{
	case ShaderType::Vertex:
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;

	case ShaderType::Fragment:
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	default:
		break;
	}

	glShaderSource(shaderID, 1, &codePtr, NULL);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
}


GLuint JN_Shader::GetShaderID()
{
	return shaderID;
}