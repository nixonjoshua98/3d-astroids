#include "JN_Camera.h"
#include "JN_Time.h"

#include <iostream>

#define LOG_POS(p) std::cout << "> " << p.x << ", " << p.y << ", " << p.z << std::endl;


JN_Camera::JN_Camera()
{
	newPos = glm::vec3(0.0f, 0.0f, 4.0f);
	newTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	speed = 0.2f;

	currentTarget = glm::vec3(1.0f);

	viewMatrix = glm::lookAt(currentPos, glm::normalize(currentPos - currentTarget), UP);

	Update();
}


JN_Camera::~JN_Camera()
{

}


void JN_Camera::Update()
{
	currentPos = newPos + offset;

	currentTarget = newTarget;

	//LOG_POS(currentTarget);
}
