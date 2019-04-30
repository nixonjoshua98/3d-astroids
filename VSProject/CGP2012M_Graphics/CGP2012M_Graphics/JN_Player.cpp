#include "JN_Player.h"
#include "JN_Time.h"



JN_Player::JN_Player(glm::vec3& lCol, glm::vec3& lPos, glm::vec3& lCol2, glm::vec3& lPos2, glm::mat4& vMatrix, glm::mat4& pMatrix): 
	lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix), lightCol2(lCol2), lightPos2(lPos2)
{
	transform.Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f));

	projectiles = std::make_unique<JN_ProjectileManager>(lightCol, lightPos, viewMatrix, projectionMatrix);

	model = JN_Model();

	for (int i = 0; i < livesRemaining; i++)
		hearts.emplace_back(-0.2f + (i * 0.2f), projectionMatrix);

	model.Load("..//..//Assets//Models//Cube.obj");

	SetShaders("..//..//Assets//Shaders//MultiLights.vert", "..//..//Assets//Shaders//MultiLights.frag");

	model.SetBuffers();

	texture.Load("..//..//Assets//Textures//White.png");
}


JN_Player::~JN_Player()
{
	hearts.clear();
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
			if (!isHoldingSpace)
				Shoot();
			isHoldingSpace = true;
			break;

		case SDLK_h:
			speedMultiplier = 1.5f;
			break;

		case SDLK_j:
			if (teleportCooldown <= 0.0f)
				isReadyToTeleport = true;
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			isMovingForward = false;
			break;

		case SDLK_SPACE:
			isHoldingSpace = false;
			break;

		case SDLK_h:
			speedMultiplier = 1.0f;
			break;
		}
		break;
	}
}


void JN_Player::Update()
{
	// L/R 5.7
	// T/B 4.4

	teleportCooldown -= JN_Time::deltaTime;

	for (int i = 0; i < livesRemaining; i++)
		hearts[i].Update();

	projectiles->Update();

	if (isMovingForward)
	{
		if (isReadyToTeleport)
		{
			teleportCooldown = 2.0f;
			transform.MoveForward2D(PLAYER_SPEED * speedMultiplier);
		}

		transform.MoveForward2D(PLAYER_SPEED * speedMultiplier * JN_Time::deltaTime);

		auto pos = transform.GetPosition();

		// Ugly but this works and is readable
		if (pos.x >= 5.7 || pos.x <= -5.7)
		{
			if (pos.x >= 5.7)
				transform.SetX(5.69);
			else
				transform.SetX(-5.69);
		}
		
		if (pos.y >= 4.4 || pos.y <= -4.4)
		{
			if (pos.y >= 4.4)
				transform.SetY(4.39);
			else
				transform.SetY(-4.39);
		}
	}

	isReadyToTeleport = false;

	SetUniforms();
}


void JN_Player::Render()
{
	for (int i = 0; i < livesRemaining; i++)
		hearts[i].Render();

	projectiles->Render();

	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture());

	model.Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}


void JN_Player::DeductLives(int i)
{
	livesRemaining = (int)fmax(livesRemaining - i, 0);
}


std::vector<glm::vec3> JN_Player::GetAllProjectilePositions()
{
	return projectiles->GetAllPositions();
}


void JN_Player::SetUniforms()
{
	glUseProgram(shaderProgram);

	auto lightPositionLocation = glGetUniformLocation(shaderProgram, "lightPos1");
	auto lightPositionLocation2 = glGetUniformLocation(shaderProgram, "lightPos2");

	auto lightColLocation = glGetUniformLocation(shaderProgram, "lightCol1");
	auto lightColLocation2 = glGetUniformLocation(shaderProgram, "lightCol2");

	auto normalMatrixLocation = glGetUniformLocation(shaderProgram, "uNormalMatrix");
	auto importModelLocation = glGetUniformLocation(shaderProgram, "uModel");
	auto importProjectionLocation = glGetUniformLocation(shaderProgram, "uProjection");
	auto importViewLocation = glGetUniformLocation(shaderProgram, "uView");

	glUniform3fv(lightColLocation, 1, glm::value_ptr(lightCol));
	glUniform3fv(lightPositionLocation, 1, glm::value_ptr(lightPos));

	glUniform3fv(lightColLocation2, 1, glm::value_ptr(lightCol2));
	glUniform3fv(lightPositionLocation2, 1, glm::value_ptr(lightPos2));

	glUniformMatrix4fv(importModelLocation, 1, GL_FALSE, glm::value_ptr(transform.Multiply()));
	glUniformMatrix4fv(importViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(importProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::mat4 normalMatrix = glm::transpose(glm::inverse(transform.Multiply() * viewMatrix));

	glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glUseProgram(0);
}


void JN_Player::Shoot()
{
	std::cout << "Shoot!\n";

	projectiles->Shoot(transform, 1.0f);
}
