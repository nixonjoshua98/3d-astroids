#include "JN_BubbleManager.h"



JN_BubbleManager::JN_BubbleManager(glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix) : lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix)
{
	model = JN_Model();

	model.Load("..//..//Assets//Models//Sphere.obj");

	model.SetBuffers();

	texture.Load("..//..//Assets//Textures//Circle.png");
}


JN_BubbleManager::~JN_BubbleManager()
{
	for (auto b : bubbles)
		delete b;

	bubbles.clear();
}


void JN_BubbleManager::SpawnBubble(int i)
{
	for (int j = 0; j < i; j++)
	{
		bubbles.push_back(new JN_Bubble{lightCol, lightPos, viewMatrix, projectionMatrix, model, texture });
	}
}


void JN_BubbleManager::Update()
{
	for (auto b : bubbles)
		b->Update();
}


void JN_BubbleManager::Render()
{
	for (auto b : bubbles)
		b->Render();
}


int JN_BubbleManager::CollideWithPlayer(glm::vec3 plr)
{
	int hits = 0;
	for (int i = 0; i < bubbles.size();)
	{
		float distance = bubbles[i]->DistanceBetween(plr);

		if (distance < 0.5f)
		{
			delete bubbles[i];
			bubbles[i] = NULL;
			bubbles.erase(bubbles.begin() + i);
			hits++;

			continue;
		}

		i++;
	}

	return hits;
}

void JN_BubbleManager::CollideWithProjectiles(std::vector<glm::vec3> projectiles)
{
	for (int i = 0; i < bubbles.size();)
	{
		bool hit = false;
		for (glm::vec3 pos : projectiles)
		{
			float distance = bubbles[i]->DistanceBetween(pos);

			if (distance < 0.5f)
			{
				delete bubbles[i];
				bubbles[i] = NULL;
				bubbles.erase(bubbles.begin() + i);
				hit = true;

				break;
			}
		}
		if (!hit) i++;
	}
}
