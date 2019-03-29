//#include <cstdio>
//#include <cstdlib>
#include <iostream>
#include <vector>

//include shape, shader header files
#include "GLerror.h"
#include "SDL_Start.h"
#include "Triangle_T.h"
#include "Circle.h"
#include "CircleTexture.h"
#include "Camera.h"
#include "Cube.h"
#ifndef TEXTURECLASS_H
#define TEXTURECLASS_H
#ifndef SHADERCLASS_H
#define SHADERCLASS_H

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#ifndef GLEW_H
#define GLEW_H
//#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#ifndef SDL_H
#define SDL_H
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_mixer.h"
//#include "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//***************
//variables
SDL_Event event;
SDL_Window *win;
bool windowOpen = true;
bool isFullScreen = false;
float bubbleSpeed = -0.001f;
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
int w;
int h;
float aspect;
int left;
int newwidth;
int newheight;

//transform matrices
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;
glm::mat4 normalMatrix;

glm::mat4 translate;
glm::mat4 rotate;
glm::mat4 scale;

glm::mat4 modelRotate;
glm::mat4 modelScale;
glm::mat4 modelTranslate;
float angle = 0;

bool flag = true;

glm::vec3 lightCol;
glm::vec3 lightPosition;
glm::vec3 viewPosition;
float ambientIntensity;


void handleInput();

//***********************
#include "JN_Background.h"
#include "JN_Application.h"
#include "JN_Camera.h"
#include "JN_Sphere.h"

#include <memory>

std::unique_ptr<JN_Background> bg;
std::unique_ptr<JN_Camera> camera;

int main(int argc, char *argv[]) {
	//start and initialise SDL
	SDL_Start sdl;
	SDL_GLContext context = sdl.Init();
	win = sdl.win;

	SDL_GetWindowSize(win, &w, &h);
	glViewport(0, 0, w, h);
	aspect = (float)w / (float)h;

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	camera = std::make_unique<JN_Camera>();
	bg = std::make_unique<JN_Background>(viewMatrix, projectionMatrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLuint currentTime = 0;
	GLuint lastTime = 0;
	GLuint elapsedTime = 0;
	glm::vec3 lightColour = glm::vec3(1.0f, 1.0f, 0.98f);
	lightPosition = glm::vec3(1.0f, 0.0f, 0.5f);
	//light colour setting
	// Candle:  r:1.0 g:0.57 b:0.16
	// 100W bulb: r:1.0 g:0.84 b:0.66
	// direct sunlight: r:1.0 g:1.0 b:0.98

	JN_Sphere model = JN_Sphere("..//..//Assets//Textures//deathstar.png", lightColour, lightPosition, viewMatrix, projectionMatrix);


	ambientIntensity = 1.0f;
	lightCol = glm::vec3(1.0f, 1.0f, 0.98f);

	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);

	viewMatrix = glm::mat4(1.0f);
	modelScale = glm::mat4(1.0f);
	modelRotate = glm::mat4(1.0f);
	modelTranslate = glm::mat4(1.0f);

	modelScale = glm::scale(modelScale, glm::vec3(0.7f, 0.7f, 0.7f));
	modelTranslate = glm::translate(modelTranslate, glm::vec3(0.0f, 0.0f, -1.0f));

	while (windowOpen)
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
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

		SDL_GL_SwapWindow(sdl.win);

	}
	SDL_GL_DeleteContext(context);

	SDL_Quit();
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
				std::cout << "Window resized w:" << w << " h:" << h << std::endl;
				SDL_GetWindowSize(win, &w, &h);
				newwidth = h * aspect;
				left = (w - newwidth) / 2;
				glViewport(left, 0, newwidth, h);
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
#endif
#endif
#endif
#endif