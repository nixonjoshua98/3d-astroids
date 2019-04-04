#pragma once

#include "JN_Model.h"
#include "JN_GameObject.h"
#include "JN_Texture.h"

class JN_Bubble : public JN_GameObject
{
public:
	JN_Bubble(glm::vec3&, glm::vec3&, glm::mat4&, glm::mat4&, JN_Model&, JN_Texture&);
	~JN_Bubble();

	const float BUBBLE_SPEED = 1.5f;

	void Update() override;
	void Render() override;

private:
	JN_Model& model;
	JN_Texture& texture;

	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	glm::vec3 rotateDir;

	void SetUniforms();
};

