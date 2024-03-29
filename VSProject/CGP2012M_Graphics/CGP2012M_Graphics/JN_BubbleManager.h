#pragma once

#include <vector>

#include "JN_Bubble.h"

class JN_BubbleManager
{
public:
	JN_BubbleManager(glm::vec3 & lCol, glm::vec3 & lPos, glm::vec3 &, glm::vec3 &, glm::mat4 & vMatrix, glm::mat4 & pMatrix);
	~JN_BubbleManager();

	void SpawnBubble(int i = 1);

	void Update();
	void Render();

	int CollideWithPlayer(glm::vec3 plr);

	void CollideWithProjectiles(std::vector<glm::vec3> projectiles);

private:
	JN_Model model;
	JN_Texture texture;

	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::vec3& lightCol2;
	glm::vec3& lightPos2;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	std::vector<JN_Bubble*> bubbles;
};