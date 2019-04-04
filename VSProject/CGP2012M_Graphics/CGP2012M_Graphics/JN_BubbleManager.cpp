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
