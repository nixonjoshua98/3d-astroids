#include "JN_ProjectileManager.h"



JN_ProjectileManager::JN_ProjectileManager(glm::vec3& lCol, glm::vec3& lPos, glm::mat4& vMatrix, glm::mat4& pMatrix):
	lightCol(lCol), lightPos(lPos), viewMatrix(vMatrix), projectionMatrix(pMatrix)
{
}


JN_ProjectileManager::~JN_ProjectileManager()
{
	for (auto p : projectiles)
		delete p;
	projectiles.clear();
}


void JN_ProjectileManager::Render()
{
	for (auto p : projectiles)
		p->Render();
}


void JN_ProjectileManager::Update()
{
	for (int i = 0; i < projectiles.size(); )
	{
		if (projectiles[i]->IsDead())
		{
			delete projectiles[i];
			projectiles[i] = NULL;
			projectiles.erase(projectiles.begin() + i);
		}
		else
		{
			projectiles[i]->Update();
			i++;
		}
	}
}


void JN_ProjectileManager::Shoot(JN_Transform trans, float lifetime)
{
	projectiles.push_back(new JN_Projectile(lightCol, lightPos, viewMatrix, projectionMatrix, trans, lifetime));
}

std::vector<glm::vec3> JN_ProjectileManager::GetAllPositions()
{
	std::vector<glm::vec3> pos;

	for (auto p : projectiles)
		pos.push_back(p->GetTransform().GetPosition());
	return pos;
}
