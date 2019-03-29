#ifndef JN_APPLICATION_H
#define JN_APPLICATION_H

#include <SDL.h>
#include <GL/glew.h>

class JN_Application
{
public:
	JN_Application();	// Constructor
	~JN_Application();	// Deconstructor

	bool Init();		// Inits the sub-systems and create the standard objects

	/* - - - -  CONSTANTS - - - - */
	const char* WINDOW_TITLE = "Joshua Nixon | 16632283 | CGP2012M Graphics | My 2D Game";
	const int GL_MAJOR = 4;
	const int GL_MINOR = 3;

	float aspectRatio;

	void SetWindowPosition();
	void ClearContext();
	void ToggleFullScreen();
	void WindowResized();


	/* - - - -  GETS - - - - */
	SDL_Window* GetWindow() { return window; }

private:
	SDL_Window* window = NULL;		// Window ptr
	SDL_GLContext context = NULL;	// OpenGL context

	bool isFullscreen = false;

	bool InitSDL();
	bool InitGL();
};

#endif