#include "JN_Camera.h"

#include <iostream>

#define PRINT(x) std::cout << "Log: " << x << std::endl;


JN_Camera::JN_Camera()
{
	newPos = glm::vec3(0.0f, 0.0f, 4.0f);
	newTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	speed = 0.2f;

	viewMatrix = glm::lookAt(currentPos, glm::normalize(currentPos - currentTarget), UP);

	Update();
}


JN_Camera::~JN_Camera()
{

}


void JN_Camera::Update()
{
	currentPos = newPos;
	currentTarget = newTarget;
}
