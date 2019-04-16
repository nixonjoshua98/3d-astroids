#include "JN_Bubble.h"
#include "JN_Time.h"


JN_Bubble::JN_Bubble(glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix, JN_Model& _model, JN_Texture& tex): 
	lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix), model(_model), texture(tex)
{
	// Transforms
	float angle =  glm::radians((float)(rand() % 360));

	transform.Scale(glm::vec3(0.3f, 0.3f, 0.3f));
	transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f));
	transform.SetDirection(cos(angle), sin(angle), 0.0f);

	rotateDir = glm::vec3(0.0f, 1.0f, 0.0f);

	SetShaders("..//..//Assets//Shaders//Bubble.vert", "..//..//Assets//Shaders//Bubble.frag");
}


JN_Bubble::~JN_Bubble()
{

}


void JN_Bubble::Update()
{
	transform.Rotate(1.0f * JN_Time::deltaTime, rotateDir);

	auto pos = transform.GetPosition();

	bool collideRight = pos.x > 5.8f;
	bool collideLeft = pos.x < -5.8f;
	bool collideBtm = pos.y < -4.5f;
	bool collideTop = pos.y > 4.5f;

	if (collideLeft || collideRight)
	{
		transform.MultiplyDirection(-1, 1);

	}
	else if (collideTop || collideBtm)
	{
		transform.MultiplyDirection(1, -1);
		//std::cout << pos.x << ", " << pos.y << "\n";
	}
	
	transform.Translate(transform.GetDirection() * BUBBLE_SPEED * JN_Time::deltaTime);

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
