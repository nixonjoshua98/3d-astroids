#pragma once

#include "JN_GameObject.h"
#include "JN_Square.h"

class JN_Heart: public JN_GameObject
{
public:
	JN_Heart(float, glm::mat4& _projectionMatrix);
	~JN_Heart();

	void Update() override;
	void Render() override;

private:
	glm::mat4& projectionMatrix;

	JN_Square square;
};

