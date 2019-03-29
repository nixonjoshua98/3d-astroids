
#include "JN_Transform.h"


void JN_Transform::Translate(glm::vec3 v)
{
	translate = glm::translate(translate, v);
}


void JN_Transform::Scale(glm::vec3 v)
{
	scale = glm::scale(scale, v);
}


float JN_Transform::DistanceBetween(glm::vec3 v)
{
	auto pos = GetPosition();

	return sqrtf(pow(pos.x - v.x, 2) + pow(pos.y - v.y, 2));
}


glm::mat4 JN_Transform::Multiply()
{
	return translate * rotate * scale;
}


glm::mat4 JN_Transform::MultiplyNoRotate()
{
	return translate * scale;
}


void JN_Transform::SetScale(glm::mat4 s)
{
	scale = s;
}


void JN_Transform::MoveForward2D(float m)
{
	Translate(glm::vec3((float)cos(angle) * m, (float)sin(angle) * m, 0.0f));
}


void JN_Transform::MultiplyDirection(int x, int y)
{
	direction.x *= x;
	direction.y *= y;
}


void JN_Transform::UpdateAngle(float a)
{
	angle += a;
}


void JN_Transform::Rotate(float a, glm::vec3 dir)
{
	rotate = glm::rotate(rotate, a, dir);
}


float JN_Transform::GetMagnitude()
{
	auto pos = GetPosition();

	return sqrtf((float)pow(pos.x, 2) + (float)pow(pos.y, 2));
}