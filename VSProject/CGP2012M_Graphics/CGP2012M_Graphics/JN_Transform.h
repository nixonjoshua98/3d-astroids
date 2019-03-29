#ifndef JN_TRANSFORM_H
#define JN_TRANSFORM_H

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <math.h>

class JN_Transform
{
public:
	float angle = 0.0f;

	glm::vec3 direction;

	glm::mat4 translate = glm::mat4(1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);


	/* - - - - GETS - - - - */
	glm::vec3 GetDirection() { return direction; }
	//glm::vec3 GetPosition() { return glm::vec3(translate[3][0] * ((float)800 / 600), translate[3][1], translate[3][2]); }
	glm::vec3 GetPosition() { return glm::vec3(translate[3][0], translate[3][1], translate[3][2]); }
	float GetMagnitude();
	float GetAngle() { return angle; }
	glm::mat4 GetScale() { return scale; }


	/* - - - - TRANSFORMS - - - - */
	void Translate(glm::vec3 v);
	void Scale(glm::vec3 v);
	void MoveForward2D(float m);
	void MultiplyDirection(int x, int y);
	void UpdateAngle(float a);
	void Rotate(float a, glm::vec3 dir);


	/* - - - - HELPER - - - - */
	float DistanceBetween(glm::vec3 collider);
	glm::mat4 Multiply();
	glm::mat4 MultiplyNoRotate();


	/* - - - - SETS - - - - */
	void SetScale(glm::mat4 s);
	void SetDirection(float x, float y, float z) { direction = glm::vec3(x, y, z); }
};

#endif // !JN_TRANSFORM_HW
