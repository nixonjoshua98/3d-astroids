#ifndef JN_SHADER_H
#define JN_SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>

class JN_Shader
{
public:
	enum class ShaderType { Fragment, Vertex };

	JN_Shader();									// Default constructor
	JN_Shader(ShaderType type, std::string path);	// Load the shader code from a text file
	~JN_Shader();									// Deconstructor

	/* - - - - GETS - - - -*/
	GLuint GetShaderID();

	const GLchar* codePtr;
	std::string shaderText;

private:
	GLuint shaderID;
	ShaderType type;

	void Load(std::string path);
	void Compile();
};

#endif // !JN_SHADER_H