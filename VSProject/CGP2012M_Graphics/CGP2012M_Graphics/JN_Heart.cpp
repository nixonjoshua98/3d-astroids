#include "JN_Heart.h"



JN_Heart::JN_Heart(float xPos, glm::mat4& _projectionMatrix) : projectionMatrix(_projectionMatrix)
{
	SetShaders("..//..//Assets//Shaders//Heart2D.vert", "..//..//Assets//Shaders//Heart2D.frag");

	square.Init("..//..//Assets//Textures//Heart.png");

	transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));

	transform.Translate(glm::vec3(xPos, 1.75f, -2.0f));
}


JN_Heart::~JN_Heart()
{

}


void JN_Heart::Update()
{
	glUseProgram(shaderProgram);

	auto uLightColourLoc = glGetUniformLocation(shaderProgram, "uLightColour");
	auto uAmbientIntensityLoc = glGetUniformLocation(shaderProgram, "uAmbientIntensity");
	auto uModelLoc = glGetUniformLocation(shaderProgram, "uModel");
	auto uViewLoc = glGetUniformLocation(shaderProgram, "uView");
	auto uProjectionLoc = glGetUniformLocation(shaderProgram, "uProjection");

	glProgramUniform3fv(shaderProgram, uLightColourLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
	glProgramUniform1f(shaderProgram, uAmbientIntensityLoc, 1.0f);

	glUniformMatrix4fv(uModelLoc, 1, GL_FALSE, glm::value_ptr(transform.MultiplyNoRotate()));
	glUniformMatrix4fv(uViewLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	glUniformMatrix4fv(uProjectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUseProgram(0);
}


void JN_Heart::Render()
{
	glUseProgram(shaderProgram);

	square.Render();

	glUseProgram(0);
}
