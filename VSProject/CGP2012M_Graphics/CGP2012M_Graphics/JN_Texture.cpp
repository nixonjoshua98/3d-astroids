

#include "JN_Texture.h"

#include <SDL_image.h>
#include <iostream>


JN_Texture::~JN_Texture()
{

}



void JN_Texture::Load(std::string file)
{
	if (textureLoaded) return;

	surface = IMG_Load(file.c_str());

	if (surface)
	{
		textureLoaded = true;
		SetBuffers();
	}
}


void JN_Texture::SetBuffers()
{
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture parameters on currently bound texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (surface->format->BytesPerPixel == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(surface);
}

GLuint JN_Texture::GetTexture()
{
	return texture;
}