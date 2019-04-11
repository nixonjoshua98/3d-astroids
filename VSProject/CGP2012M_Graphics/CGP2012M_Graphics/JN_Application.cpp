

#include "JN_Application.h" 



// Default constructor
JN_Application::JN_Application()
{

}


// Deconstructor
JN_Application::~JN_Application()
{

	// Destroys the widgets
	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);

	// Removes nullptrs
	window, context = NULL, NULL;

	SDL_Quit();	// Closes all SDL sub systems
}


// Init the relevant sub-systems and create the initial widgets
bool JN_Application::Init()
{
	// SDL MUST be init first
	return InitSDL() && InitGL();
}


// Init SDl sub-systems
bool JN_Application::InitSDL()
{
	bool isSDL = SDL_Init(SDL_INIT_EVERYTHING) == 0;	// Init SDL

	if (isSDL)
	{
		window = SDL_CreateWindow(
			WINDOW_TITLE,		// Window title
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,				// Initial position of the window (x, y)
			750, 600,			// Width & height of the window
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE	// Window flags
		);

		if (window)
			SetWindowPosition();
	}

	return isSDL;
}


// Init OpenGL systems
bool JN_Application::InitGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//SDL_GL_SetSwapInterval(0);

	context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return glewInit() == GLEW_OK;
}


// Clears the context
void JN_Application::ClearContext()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void JN_Application::ToggleFullScreen()
{
	auto flag = isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP;
	SDL_SetWindowFullscreen(window, flag);
	isFullscreen = !isFullscreen;

	WindowResized();
}



void JN_Application::WindowResized()
{
	int w, h;

	SDL_GetWindowSize(window, &w, &h);

	int newWidth = h * aspectRatio;
	int newHeight = h;

	int offsetX = (w - newWidth) / 2;

	glViewport(offsetX, 0, newWidth, newHeight);
}


void JN_Application::SetWindowPosition()
{
	int w, h;

	SDL_GetWindowSize(window, &w, &h);

	aspectRatio = (float)w / (float)h;

	glViewport(0, 0, w, h);
};