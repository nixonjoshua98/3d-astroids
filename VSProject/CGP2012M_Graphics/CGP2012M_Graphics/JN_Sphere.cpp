#include "JN_Sphere.h"

#include "ModelLoaderClass.h"



JN_Sphere::JN_Sphere(std::string tex, glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix):
	lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix)
{
	transform.Scale(glm::vec3(0.7f, 0.7f, 0.7f));
	transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f));

	model = JN_Model();

	LoadModelObj();

	SetShaders("..//..//Assets//Shaders//shader_projection_lighting_AD.vert", "..//..//Assets//Shaders//shader_projection_lighting_AD.frag");

	model.SetBuffers();

	texture.Load(tex);
}


JN_Sphere::~JN_Sphere()
{

}


void JN_Sphere::Update()
{
	SetUniforms();
}


void JN_Sphere::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
	model.Render();
	glBindTexture(GL_TEXTURE_2D, 0);
}


void JN_Sphere::LoadModelObj()
{
	ModelImport modelLoader;
	modelLoader.LoadOBJ2("..//..//Assets//Models//blenderSphere.obj", model.vertices, model.texCoords, model.normals, model.indices);
}

void JN_Sphere::SetUniforms()
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

	transform.Rotate(0.0005f, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(importModelLocation, 1, GL_FALSE, glm::value_ptr(transform.Multiply()));
	glUniformMatrix4fv(importViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(importProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(transform.Multiply() * viewMatrix));

	glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

}
