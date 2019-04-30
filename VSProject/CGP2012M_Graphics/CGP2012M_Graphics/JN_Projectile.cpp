#include "JN_Projectile.h"





JN_Projectile::JN_Projectile(glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix, JN_Transform trans, float lifetime):
	lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix)
{
	transform = trans;
	timer = lifetime;

	transform.Scale(glm::vec3(0.5f, 0.5f, 0.5f));

	model = JN_Model();

	model.Load("..//..//Assets//Models//Cube.obj");

	SetShaders("..//..//Assets//Shaders//Projectile.vert", "..//..//Assets//Shaders//Projectile.frag");

	model.SetBuffers();

	texture.Load("..//..//Assets//Textures//Red.png");

}

JN_Projectile::~JN_Projectile()
{

}


void JN_Projectile::Render()
{
	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());

	model.Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}


void JN_Projectile::Update()
{
	timer -= JN_Time::deltaTime;

	transform.MoveForward2D(speed * JN_Time::deltaTime);

	auto pos = transform.GetPosition();

	//std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

	SetUniforms();
}

void JN_Projectile::SetUniforms()
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
