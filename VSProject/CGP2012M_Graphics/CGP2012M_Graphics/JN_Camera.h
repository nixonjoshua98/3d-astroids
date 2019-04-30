#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "JN_ScreenBoundaries.h"

class JN_Camera
{
public:
	JN_Camera();
	~JN_Camera();

	glm::vec3 UP = glm::vec3(0, 1, 0);

	JN_ScreenBoundaries boundaries = JN_ScreenBoundaries({ 2.0f, -2.0f, 1.0f, -1.0f, 0.0f, 0.0f });

	glm::vec3 newPos;
	glm::vec3 newTarget;

	glm::vec3 offset = glm::vec3(0.0f);

	float speed;

	void Update();

	glm::vec3 GetCurrentPos() { return currentPos; }
	glm::vec3 GetCurrentTarget() { return currentTarget; }

	glm::mat4 GetViewMatrix() { return viewMatrix; }

private:
	glm::vec3 currentPos;
	glm::vec3 currentTarget;

	glm::mat4 viewMatrix;
};

