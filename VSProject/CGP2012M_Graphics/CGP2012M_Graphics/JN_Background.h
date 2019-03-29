#ifndef JN_BACKGROUND_H
#define JN_BACKGROUND_H

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "JN_Square.h"
#include "JN_Transform.h"

class JN_Background
{
public:
	JN_Background();
	JN_Background(glm::mat4&, glm::mat4&);
	~JN_Background();

	void Update(glm::vec3);
	void Render();

private:
	JN_Transform transform;
	JN_Square square;

	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	float ambientIntensity = 1.0f;
};

#endif // !JN_BACKGROUND_H
