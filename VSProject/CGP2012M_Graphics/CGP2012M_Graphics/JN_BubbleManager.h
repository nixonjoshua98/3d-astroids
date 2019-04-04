#pragma once

#include <vector>

#include "JN_Bubble.h"

class JN_BubbleManager
{
public:
	JN_BubbleManager(glm::vec3 & lCol, glm::vec3 & lPos, glm::mat4 & vMatrix, glm::mat4 & pMatrix);
	~JN_BubbleManager();

	void SpawnBubble(int i = 1);

	void Update();
	void Render();

private:
	JN_Model model;
	JN_Texture texture;

	glm::vec3& lightCol;
	glm::vec3& lightPos;
	glm::mat4& viewMatrix;
	glm::mat4& projectionMatrix;

	std::vector<JN_Bubble*> bubbles;
};