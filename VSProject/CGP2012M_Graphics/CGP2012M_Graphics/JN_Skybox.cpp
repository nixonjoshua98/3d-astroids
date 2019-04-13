#include "JN_Skybox.h"

#include <iostream>



JN_Skybox::JN_Skybox(glm::mat4& view, glm::mat4& pro): viewMatrix(view), projectionMatrix(pro)
{
	std::vector<std::string> faces
	{
		"..//..//Assets//Textures//Skybox//Space_Front.png",
		"..//..//Assets//Textures//Skybox//Space_Back.png",
		"..//..//Assets//Textures//Skybox//Space_Top.png",
		"..//..//Assets//Textures//Skybox//Space_Bottom.png",
		"..//..//Assets//Textures//Skybox//Space_Right.png",
		"..//..//Assets//Textures//Skybox//Space_Left.png"
	};

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	SDL_Surface* data;
	for (int i = 0; i < faces.size(); i++)
	{
		data = IMG_Load(faces[i].c_str());

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, data->w, data->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->pixels);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
		}

		SDL_FreeSurface(data);
		data = NULL;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	SetShaders("..//..//Assets//Shaders//Skybox.vert", "..//..//Assets//Shaders//Skybox.frag");

	SetBuffers();
}



JN_Skybox::~JN_Skybox()
{

}


void JN_Skybox::Update()
{
	glUseProgram(shaderProgram);
	
	auto uView = glGetUniformLocation(shaderProgram, "uView");
	auto uProjection = glGetUniformLocation(shaderProgram, "uProjection");

	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(glm::mat4(glm::mat3(viewMatrix))));
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glUseProgram(0);
}


void JN_Skybox::Render()
{
	glDepthMask(GL_FALSE);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDepthMask(GL_TRUE);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void JN_Skybox::SetBuffers()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
