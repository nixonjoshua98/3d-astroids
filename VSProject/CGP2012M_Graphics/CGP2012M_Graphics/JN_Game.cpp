#include "JN_Game.h"



JN_Game::JN_Game()
{

}


JN_Game::JN_Game(std::shared_ptr<JN_Application> app)
{
	this->app = app;

	screenBoundaries = JN_ScreenBoundaries({2.0f, -2.0f, 1.0f, -1.0f, 0.0f, 0.0f});

	camera = std::make_unique<JN_Camera>();
	bg = std::make_unique<JN_Background>(viewMatrix, projectionMatrix);

	lightCol = glm::vec3(1.0f, 1.0f, 0.98f);
	lightPos = glm::vec3(1.0f, 0.0f, 0.5f);

	sphere = std::make_unique<JN_Sphere>("..//..//Assets//Textures//deathstar.png", lightCol, lightPos, viewMatrix, projectionMatrix);

	projectionMatrix = glm::perspective(glm::radians(45.0f), app->aspectRatio, 0.1f, 100.0f);
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
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				app->WindowResized();
				break;
			}
			break;

		case SDL_KEYDOWN:
			break;

		case SDL_KEYUP:
			break;
		}
	}
}


void JN_Game::Update()
{
	camera->Update();

	viewMatrix = glm::lookAt(camera->GetCurrentPos(), camera->GetCurrentTarget(), camera->UP);

	bg->Update();
	sphere->Update();
}


void JN_Game::LateUpdate()
{

}


void JN_Game::Render()
{
	app->ClearContext();

	bg->Render();
	sphere->Render();

	SDL_GL_SwapWindow(app->GetWindow());
}
