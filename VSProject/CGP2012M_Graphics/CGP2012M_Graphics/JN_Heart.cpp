#include "JN_Heart.h"
#include "JN_Time.h"

#include "ModelLoaderClass.h"


JN_Heart::JN_Heart(std::string tex, glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix):
	lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix)
{
	// Transforms
	float angle = glm::radians((float)(rand() % 360));

	transform.Scale(glm::vec3(0.02f, 0.02f, 0.02f));
	transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f));
	transform.Translate(glm::vec3(-3.8f, 2.8f, 0.0f));
	transform.Rotate(1.0f, glm::vec3(-1.0f, 0.0f, 0.0f));

	model = JN_Model();

	LoadModelObj();

	SetShaders("..//..//Assets//Shaders//Heart.vert", "..//..//Assets//Shaders//Heart.frag");

	model.SetBuffers();

	texture.Load(tex);
}


JN_Heart::~JN_Heart()
{

}


void JN_Heart::Update()
{
	transform.Rotate(1.0f * JN_Time::deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));

	auto pos = transform.GetPosition();

	//std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

	SetUniforms();
}


void JN_Heart::Render()
{
	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
	model.Render();
	glBindTexture(GL_TEXTURE_2D, 0);
}


void JN_Heart::LoadModelObj()
{
	ModelImport modelLoader;
	modelLoader.LoadOBJ2("..//..//Assets//Models//Heart.obj", model.vertices, model.texCoords, model.normals, model.indices);
}

void JN_Heart::SetUniforms()
{
	glUseProgram(shaderProgram);

	auto lightColLocation = glGetUniformLocation(shaderProgram, "lightCol");
	auto normalMatrixLocation = glGetUniformLocation(shaderProgram, "uNormalMatrix");
	auto importViewLocation = glGetUniformLocation(shaderProgram, "uView");
	auto lightPositionLocation = glGetUniformLocation(shaderProgram, "lightPos");
	auto importModelLocation = glGetUniformLocation(shaderProgram, "uModel");
	auto importProjectionLocation = glGetUniformLocation(shaderProgram, "uProjection");

	glUniform3fv(lightColLocation, 1, glm::value_ptr(lightCol));
	glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPos));

	glUniformMatrix4fv(importModelLocation, 1, GL_FALSE, glm::value_ptr(transform.Multiply()));
	glUniformMatrix4fv(importViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(importProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(transform.Multiply() * viewMatrix));

	glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glUseProgram(0);

}
