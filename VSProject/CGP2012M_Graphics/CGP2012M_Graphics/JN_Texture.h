#ifndef JN_TEXTURE_H
#define JN_TEXTURE_H

#include <GL/glew.h>
#include <SDL.h>
#include <string>


class JN_Texture
{
public:
	~JN_Texture();

	void Load(std::string file);	// Loads the texture

	GLuint GetTexture();

protected:
	bool textureLoaded = false;

	SDL_Surface* surface;			// SDL surface - Temp storage for the texture
	GLuint texture;					// GL version of the texture

	void SetBuffers();
};


#endif // !JN_TEXTURE_H
