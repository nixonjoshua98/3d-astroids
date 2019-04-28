#pragma once

#include "JN_Model.h"
#include "JN_GameObject.h"
#include "JN_Texture.h"
#include "JN_Heart.h"
#include "JN_ProjectileManager.h"

#include <memory>

class JN_Player : public JN_GameObject
{
public:
	JN_Player(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::mat4&, glm::mat4&);
	~JN_Player();

	const float PLAYER_SPEED = 2.0f;

	void Input(SDL_Event e);
	void Update() override;
	void Render() override;

	void DeductLives(int i);
	bool IsDead() { return livesRemaining == 0; }

	std::vector<glm::vec3> GetAllProjectilePositions();

private:
	JN_Model model;
	JN_Texture texture;

	std::unique_ptr<JN_ProjectileManager> projectiles;

	float speedMultiplier = 1.0f;

	float teleportCooldown = 0.0f;

	std::vector<JN_Heart> hearts;

	int livesRemaining = 3;

	bool isHoldingSpace = false;
	bool isMovingForward = false;
	bool isShooting = false;
	bool isReadyToTeleport = false;

	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::vec3& lightCol2;
	glm::vec3& lightPos2;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	void SetUniforms();
	void Shoot();
};

