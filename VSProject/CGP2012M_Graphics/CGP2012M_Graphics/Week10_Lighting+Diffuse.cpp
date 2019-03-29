
#include <iostream>

#include <GL/glew.h>
#include "windows.h"

#include "SDL.h"
#include "SDL_image.h"

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SDL_Event event;
SDL_Window *win;
bool windowOpen = true;
bool isFullScreen = false;
float radius;
//screen boundaries for collision tests
float bX_r = 2.0f;
float bX_l = -2.0f;
float bY_t = 1.0f;
float bY_b = -1.0f;
//screen centre
float centreX = 0.0f;
float centreY = 0.0f;
//window aspect/width/height
int left;
int newwidth;
int newheight;

//transform matrices
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::vec3 lightCol;
glm::vec3 lightPosition;


void handleInput();

//***********************
#include "JN_Background.h"
#include "JN_Application.h"
#include "JN_Camera.h"
#include "JN_Sphere.h"

#include <memory>

std::unique_ptr<JN_Background> bg;
std::unique_ptr<JN_Camera> camera;
std::unique_ptr<JN_Application> app;

int main(int argc, char *argv[]) {
	app = std::make_unique<JN_Application>();

	app->Init();

	camera = std::make_unique<JN_Camera>();
	bg = std::make_unique<JN_Background>(viewMatrix, projectionMatrix);

	GLuint currentTime = 0;
	GLuint lastTime = 0;
	GLuint elapsedTime = 0;
	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 0.98f);
	lightPosition = glm::vec3(1.0f, 0.0f, 0.5f);

	JN_Sphere model = JN_Sphere("..//..//Assets//Textures//deathstar.png", lightColour, lightPosition, viewMatrix, projectionMatrix);

	lightCol = glm::vec3(1.0f, 1.0f, 0.98f);

	projectionMatrix = glm::perspective(glm::radians(45.0f), app->aspectRatio, 0.1f, 100.0f);
	viewMatrix = glm::mat4(1.0f);

	while (windowOpen)
	{
		app->ClearContext();
		
		//process inputs
		handleInput();
		camera->Update();

		//time
		currentTime = SDL_GetTicks();
		elapsedTime = currentTime - lastTime;
		lastTime = currentTime;

		viewMatrix = glm::lookAt(camera->GetCurrentPos(), camera->GetCurrentTarget(), camera->UP);

		bg->Update();
		bg->Render();

		model.Update();
		model.Render();

		SDL_GL_SwapWindow(app->GetWindow());

	}
	return 0;
}

void handleInput()
{
	//*****************************
		//SDL handled input
		//Any input to the program is done here

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			windowOpen = false;
		}
		if (event.type == SDL_WINDOWEVENT)
		{
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				app->WindowResized();
				break;
				

			default:
				break;
			}
		}
		
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			
			case SDLK_UP:
				//translate = glm::translate(translate, glm::vec3((float)cos(angle)*0.02f, (float)sin(angle)*0.02f, 0.0f));
				break;
			case SDLK_a:
				//angle += glm::radians(10.0f);
				//rotate = glm::rotate(rotate,glm::radians(10.0f), glm::vec3(0, 0, 1));
				break;
			case SDLK_d:
				//angle -= glm::radians(10.0f);
				//rotate = glm::rotate(rotate, glm::radians(-10.0f) , glm::vec3(0, 0, 1));
				break;
			case SDLK_p:
				//move camera 'forward' in the -ve z direction
				camera->newPos.z -= camera->speed;
				break;
			case SDLK_l:
				//move camera 'backwards' in +ve z direction
				camera->newPos.z += camera->speed;
				break;
			case SDLK_z:
				//move camera left
				//move camera target with position
				camera->newTarget.x -= camera->speed;
				camera->newPos.x -= camera->speed;
				break;
			case SDLK_x:
				//move camera right
				//move camera target with position
				camera->newPos.x += camera->speed;
				camera->newTarget.x += camera->speed;
				break;

			case SDLK_m:
				//move camera up

				camera->newPos.y += camera->speed;
				camera->newTarget.y += camera->speed;
				break;
			case SDLK_k:
				//move camera down

				camera->newPos.y -= camera->speed;
				camera->newTarget.y -= camera->speed;
				break;
			case SDLK_v:
				lightPosition.x -= 0.1f;
				break;
			case SDLK_b:
				lightPosition.x += 0.1f;
				break;
			
			}
		}
	}
}