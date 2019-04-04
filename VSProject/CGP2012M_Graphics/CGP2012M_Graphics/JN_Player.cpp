#include "JN_Player.h"
#include "JN_Time.h"



JN_Player::JN_Player(glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix): lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix)
{
	transform.Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f));

	model = JN_Model();

	heart = std::make_unique<JN_Heart>("..//..//Assets//Textures//Red.png", lightCol, lightPos, viewMatrix, projectionMatrix);

	model.Load("..//..//Assets//Models//Cube.obj");

	SetShaders("..//..//Assets//Shaders//Player.vert", "..//..//Assets//Shaders//Player.frag");

	model.SetBuffers();

	texture.Load("..//..//Assets//Textures//Red.png");
}


JN_Player::~JN_Player()
{

}


void JN_Player::Input(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			isMovingForward = true;
			break;

		case SDLK_a:
			transform.UpdateAngle(glm::radians(5.0f));
			transform.Rotate(glm::radians(5.0f), glm::vec3(0, 0, 1));
			break;

		case SDLK_d:
			transform.UpdateAngle(glm::radians(-5.0f));
			transform.Rotate(glm::radians(-5.0f), glm::vec3(0, 0, 1));
			break;

		case SDLK_SPACE:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			isMovingForward = false;
			break;
		}
		break;
	}
}


void JN_Player::Update()
{
	heart->Update();

	if (isMovingForward)
	{
		float angle = transform.GetAngle();

		auto pos = transform.GetPosition();

		transform.Translate(glm::vec3((float)cos(angle) * PLAYER_SPEED * JN_Time::deltaTime, (float)sin(angle) * PLAYER_SPEED * JN_Time::deltaTime, 0.0f));
	}

	SetUniforms();
}


void JN_Player::Render()
{
	heart->Render();

	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());

	model.Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}


void JN_Player::SetUniforms()
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
