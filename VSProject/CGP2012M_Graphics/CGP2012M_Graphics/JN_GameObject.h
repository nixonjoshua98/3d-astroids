#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "JN_Transform.h"

float GetTime();

class JN_GameObject
{
public:
	JN_GameObject();
	~JN_GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;

	JN_Transform GetTransform() { return transform; }

protected:
	JN_Transform transform;

	GLuint shaderProgram;


	void SetShaders(std::string v, std::string f);
};

