#include "JN_Game.h"

JN_Game::JN_Game()
{

}


JN_Game::JN_Game(std::shared_ptr<JN_Application> app)
{
	this->app = app;

	screenBoundaries = JN_ScreenBoundaries({2.0f, -2.0f, 1.0f, -1.0f, 0.0f, 0.0f});

	camera = std::make_unique<JN_Camera>();
	player = std::make_unique<JN_Player>(lightCol, lightPos, viewMatrix, projectionMatrix);
	bg = std::make_unique<JN_Background>(viewMatrix, projectionMatrix);

	lightCol = glm::vec3(1.0f, 1.0f, 0.98f);
	lightPos = glm::vec3(1.0f, 0.0f, 0.5f);

	bubble = std::make_unique<JN_Bubble>("..//..//Assets//Textures//Circle.png", lightCol, lightPos, viewMatrix, projectionMatrix);

	projectionMatrix = glm::perspective(glm::radians(90.0f), app->aspectRatio, 0.1f, 100.0f);
}


JN_Game::~JN_Game()
{

}


void JN_Game::Run()
{
	while (isRunning)
	{
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
	camera->Update();

	viewMatrix = glm::lookAt(camera->GetCurrentPos(), camera->GetCurrentTarget(), camera->UP);

	bg->Update();
	player->Update();
	bubble->Update();
}


void JN_Game::LateUpdate()
{

}


void JN_Game::Render()
{
	app->ClearContext();

	bg->Render();
	player->Render();
	bubble->Render();

	SDL_GL_SwapWindow(app->GetWindow());
}
