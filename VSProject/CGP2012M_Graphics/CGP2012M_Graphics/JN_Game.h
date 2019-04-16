#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <memory>

#include "JN_Background.h"
#include "JN_Camera.h"
#include "JN_ScreenBoundaries.h"
#include "JN_Application.h"
#include "JN_Light.h"
#include "JN_Player.h"
#include "JN_BubbleManager.h"
#include "JN_Skybox.h"


class JN_Game
{
public:
	JN_Game();
	JN_Game(std::shared_ptr<JN_Application>);
	~JN_Game();

	void Run();

private:
	bool isRunning = true;

	float spawnTimer = 0.0f;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	JN_Light light;
	JN_Light light2;

	JN_ScreenBoundaries screenBoundaries;

	std::shared_ptr<JN_Application> app;

	std::unique_ptr<JN_Background> bg;
	std::unique_ptr<JN_Camera> camera;
	std::unique_ptr<JN_Player> player;
	std::unique_ptr<JN_BubbleManager> bubbles;
	std::unique_ptr<JN_Skybox> skybox;

	void Input();
	void Update();
	void LateUpdate();
	void Render();

	void Spawn();
};

