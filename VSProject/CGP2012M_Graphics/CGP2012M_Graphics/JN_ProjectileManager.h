#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "JN_Projectile.h"
#include "JN_Transform.h"

class JN_ProjectileManager
{
public:
	JN_ProjectileManager(glm::vec3 & lCol, glm::vec3 & lPos, glm::mat4 & vMatrix, glm::mat4 & pMatrix);
	~JN_ProjectileManager();

	void Render();
	void Update();

	void Shoot(JN_Transform trans, float lifetime);

	std::vector<glm::vec3> GetAllPositions();

private:
	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	std::vector<JN_Projectile*> projectiles;
};

