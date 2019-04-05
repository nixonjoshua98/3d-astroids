#pragma once

#include "JN_Model.h"
#include "JN_GameObject.h"
#include "JN_Texture.h"
#include "JN_Heart.h"

#include <memory>

class JN_Player : public JN_GameObject
{
public:
	JN_Player(glm::vec3&, glm::vec3&, glm::mat4&, glm::mat4&);
	~JN_Player();

	const float PLAYER_SPEED = 2.0f;

	void Input(SDL_Event e);
	void Update() override;
	void Render() override;

	bool IsDead() { return livesRemaining == 0; }

private:
	JN_Model model;
	JN_Texture texture;

	std::vector<JN_Heart> hearts;

	int livesRemaining = 3;

	bool isMovingForward = false;

	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	void SetUniforms();
};

