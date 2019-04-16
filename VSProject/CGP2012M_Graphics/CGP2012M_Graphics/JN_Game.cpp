#include "JN_Game.h"
#include "JN_FrameLock.h"
#include "JN_Time.h"

JN_Game::JN_Game()
{

}


JN_Game::JN_Game(std::shared_ptr<JN_Application> app)
{
	this->app = app;

	screenBoundaries = JN_ScreenBoundaries({ 2.0f, -2.0f, 1.0f, -1.0f, 0.0f, 0.0f });
	light = JN_Light{ glm::vec3(-2.0f, 0.0f, -1.0f), glm::vec3(0.4f, 1.0f, 1.0f) };
	light2 = JN_Light{ glm::vec3(2.0f, 0.0f, -1.0f), glm::vec3(0.4f, 1.0f, 1.0f) };

	camera = std::make_unique<JN_Camera>();
	skybox = std::make_unique<JN_Skybox>(viewMatrix, projectionMatrix);
	player = std::make_unique<JN_Player>(light.col, light.pos, light2.col, light2.pos, viewMatrix, projectionMatrix);
	bg = std::make_unique<JN_Background>(viewMatrix, projectionMatrix);
	bubbles = std::make_unique<JN_BubbleManager>(light2.col, light2.pos, viewMatrix, projectionMatrix);

	projectionMatrix = glm::perspective(glm::radians(90.0f), app->aspectRatio, 0.1f, 100.0f);
}


JN_Game::~JN_Game()
{

}


void JN_Game::Run()
{
	while (isRunning)
	{
		{
			JN_FrameLock lock = JN_FrameLock(60, JN_Time::deltaTime);

			Input();
			Update();
			LateUpdate();
			Render();
		}

		spawnTimer += JN_Time::deltaTime;
	}
}


void JN_Game::Input()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			// * * * * SDL_QUIT
		case SDL_QUIT:
			isRunning = false;
			break;
			
			// * * * * SDL_WINDOWEVENT
		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{
				// * * * * SDL_WINDOWEVENT_RESIZED
			case SDL_WINDOWEVENT_RESIZED:
				app->WindowResized();
				break;
			}
			break;

			// * * * * SDL_KEYDOWN
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				// * * * * F10
			case SDLK_F10:
				app->ToggleFullScreen();
				break;

			default:
				player->Input(e);
				break;
			}

			// * * * * SDL_KEYUP
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			default:
				player->Input(e);
				break;
			}
		}
	}
}


void JN_Game::Update()
{
	// End the game loop once the player dies
	if (player->IsDead()) { isRunning = false; }

	glm::vec3 plrPos = player->GetTransform().GetPosition();

	// Point the camera towards the player
	camera->newTarget = plrPos;

	// Check collision with player - get collision total
	int hits = bubbles->CollideWithPlayer(plrPos);

	// Destroy bubbles which are hit by projectiles
	bubbles->CollideWithProjectiles(player->GetAllProjectilePositions());

	// Update internal camera stuff
	camera->Update();

	// Update the view matrix
	viewMatrix = glm::lookAt(camera->GetCurrentPos(), camera->GetCurrentTarget(), camera->UP);

	Spawn();	// Check if a new bubble needs to be spawned

	// Take health away from the player
	player->DeductLives(hits);

	// Update objects - and uniforms
	skybox->Update();
	bg->Update();
	player->Update();
	bubbles->Update();
}


void JN_Game::LateUpdate()
{

}


void JN_Game::Render()
{
	app->ClearContext();

	skybox->Render();
	//bg->Render();
	player->Render();
	bubbles->Render();

	SDL_GL_SwapWindow(app->GetWindow());
}


void JN_Game::Spawn()
{
	if (spawnTimer >= 4.0f)
	{
		spawnTimer = 0.0f;

		bubbles->SpawnBubble();
	}
}