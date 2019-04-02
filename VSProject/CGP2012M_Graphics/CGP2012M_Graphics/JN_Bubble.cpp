#include "JN_Bubble.h"


JN_Bubble::JN_Bubble(std::string tex, glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix): lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix)
{
	// Transforms
	float angle = glm::radians((float)(rand() % 360));

	transform.Scale(glm::vec3(0.7f, 0.7f, 0.7f));
	transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f));
	transform.SetDirection(cos(angle), sin(angle), 0.0f);

	model = JN_Model();

	rotateDir = glm::vec3(0.0f, 1.0f, 0.0f);

	model.Load("..//..//Assets//Models//Sphere.obj");

	SetShaders("..//..//Assets//Shaders//Bubble.vert", "..//..//Assets//Shaders//Bubble.frag");

	model.SetBuffers();

	texture.Load(tex);
}


JN_Bubble::~JN_Bubble()
{

}


void JN_Bubble::Update()
{
	transform.Rotate(0.005f, rotateDir);

	auto pos = transform.GetPosition();

	//std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

	bool collideRight = pos.x > 3.4f;
	bool collideLeft = pos.x < -3.4f;
	bool collideTop = pos.y < -2.6f;
	bool collideBtm = pos.y > 2.6f;

	if (collideLeft || collideRight)
		transform.MultiplyDirection(-1, 1);
	else if (collideTop || collideBtm)
		transform.MultiplyDirection(1, -1);
	
	transform.Translate(transform.GetDirection() * BUBBLE_SPEED);

	SetUniforms();
}


void JN_Bubble::Render()
{
	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());

	model.Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}


void JN_Bubble::SetUniforms()
{
	glUseProgram(shaderProgram);

	auto lightColLocation = glGetUniformLocation(shaderProgram, "lightCol");
	auto normalMatrixLocation = glGetUniformLocation(shaderProgram, "uNormalMatrix");
	auto importViewLocation = glGetUniformLocation(shaderProgram, "uView");
	auto lightPositionLocation = glGetUniformLocation(shaderProgram, "lightPos");
	auto importModelLocation = glGetUniformLocation(shaderProgram, "uModel");
	auto importProjectionLocation = glGetUniformLocation(shaderProgram, "uProjection");

	auto timeLocation = glGetUniformLocation(shaderProgram, "time");

	glUniform3fv(lightColLocation, 1, glm::value_ptr(lightCol));
	glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPos));

	glUniform1f(timeLocation, GetTime());

	glUniformMatrix4fv(importModelLocation, 1, GL_FALSE, glm::value_ptr(transform.Multiply()));
	glUniformMatrix4fv(importViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(importProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(transform.Multiply() * viewMatrix));

	glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glUseProgram(0);
}
