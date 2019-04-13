#include "JN_Game.h"
#include "JN_FrameLock.h"
#include "JN_Time.h"

JN_Game::JN_Game()
{

}


JN_Game::JN_Game(std::shared_ptr<JN_Application> app)
{
	this->app = app;

	camera = std::make_unique<JN_Camera>();
	skybox = std::make_unique<JN_Skybox>(viewMatrix, projectionMatrix);
	player = std::make_unique<JN_Player>(light.col, light.pos, viewMatrix, projectionMatrix);
	bg = std::make_unique<JN_Background>(viewMatrix, projectionMatrix);
	bubbles = std::make_unique<JN_BubbleManager>(light.col, light.pos, viewMatrix, projectionMatrix);

	screenBoundaries = JN_ScreenBoundaries({ 2.0f, -2.0f, 1.0f, -1.0f, 0.0f, 0.0f });
	light = JN_Light{ glm::vec3(1.0f, 0.0f, 0.5f), glm::vec3(1.0f, 1.0f, 0.98f) };

	projectionMatrix = glm::perspective(glm::radians(90.0f), app->aspectRatio, 0.1f, 100.0f);

	bubbles->SpawnBubble();
}


JN_Game::~JN_Game()
{

}


void JN_Game::Run()
{
	while (isRunning)
	{
		JN_FrameLock lock = JN_FrameLock(60, JN_Time::deltaTime);

		Input();
		Update();
		LateUpdate();
		Render();
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
	if (player->IsDead())
	{
		isRunning = false;
	}

	camera->newTarget = player->GetTransform().GetPosition();

	light.pos = camera->newPos;

	camera->Update();

	viewMatrix = glm::lookAt(camera->GetCurrentPos(), camera->GetCurrentTarget(), camera->UP);

	skybox->Update();
	bg->Update();
	player->Update();
	bubbles->Update();
}


void JN_Game::LateUpdate()
{
	//bubbles->SpawnBubble();
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
