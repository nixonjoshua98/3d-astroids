#ifndef JN_BACKGROUND_H
#define JN_BACKGROUND_H

#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "JN_Square.h"
#include "JN_GameObject.h"

class JN_Background: public JN_GameObject
{
public:
	JN_Background(glm::mat4&, glm::mat4&);
	~JN_Background();

	void Update() override;
	void Render() override;

private:
	JN_Square square;
	JN_Square border;

	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	glm::vec3 lightCol = glm::vec3(1.0f, 1.0f, 0.98f);

	float ambientIntensity = 1.0f;
};

#endif // !JN_BACKGROUND_H
