#pragma once

#include "JN_GameObject.h"
#include "JN_Model.h"
#include "JN_Time.h"
#include "JN_Texture.h"


class JN_Projectile : public JN_GameObject
{
public:
	JN_Projectile(glm::vec3&, glm::vec3&, glm::mat4&, glm::mat4&, JN_Transform transform, float lifetime);
	~JN_Projectile();

	float speed = 4.0f;

	void Render() override;
	void Update() override;
	void SetUniforms();

	bool IsDead() { return timer <= 0.0f; }

private:
	JN_Model model;
	JN_Texture texture;

	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	float timer;
};

