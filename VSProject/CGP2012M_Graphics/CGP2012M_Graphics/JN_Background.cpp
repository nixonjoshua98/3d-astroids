#include "JN_Background.h"
#include "JN_Shader.h"

JN_Background::JN_Background(glm::mat4& _viewMatrix, glm::mat4& _projectionMatrix): viewMatrix(_viewMatrix), projectionMatrix(_projectionMatrix)
{
	SetShaders("..//..//Assets//Shaders//Background.vert", "..//..//Assets//Shaders//Background.frag");

	square.Init("..//..//Assets//Textures//Background.jpg");
	border.Init("..//..//Assets//Textures//Border.png");

	transform.Scale(glm::vec3(60.0f, 50.0f, 1.0f));
	transform.Translate(glm::vec3(0.0f, 0.0f, -2.0f));
}



JN_Background::~JN_Background()
{

}


void JN_Background::Render()
{
	glUseProgram(shaderProgram);
	square.Render();
	border.Render();
	glUseProgram(0);
}


void JN_Background::Update()
{
	glUseProgram(shaderProgram);

	auto uLightColourLoc = glGetUniformLocation(shaderProgram, "uLightColour");
	auto uAmbientIntensityLoc = glGetUniformLocation(shaderProgram, "uAmbientIntensity");
	auto uModelLoc = glGetUniformLocation(shaderProgram, "uModel");
	auto uViewLoc = glGetUniformLocation(shaderProgram, "uView");
	auto uProjectionLoc = glGetUniformLocation(shaderProgram, "uProjection");

	glProgramUniform3fv(shaderProgram, uLightColourLoc, 1, glm::value_ptr(lightCol));
	glProgramUniform1f(shaderProgram, uAmbientIntensityLoc, ambientIntensity);

	glUniformMatrix4fv(uModelLoc, 1, GL_FALSE, glm::value_ptr(transform.MultiplyNoRotate()));
	glUniformMatrix4fv(uViewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uProjectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}
