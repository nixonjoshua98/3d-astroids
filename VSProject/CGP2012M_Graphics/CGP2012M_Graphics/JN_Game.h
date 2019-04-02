#pragma once

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <memory>

#include "JN_Background.h"
#include "JN_Camera.h"
#include "JN_Bubble.h"
#include "JN_ScreenBoundaries.h"
#include "JN_Application.h"
#include "JN_Player.h"


class JN_Game
{
public:
	JN_Game();
	JN_Game(std::shared_ptr<JN_Application>);
	~JN_Game();

	void Run();

private:
	bool isRunning = true;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 lightCol;
	glm::vec3 lightPos;

	JN_ScreenBoundaries screenBoundaries;

	std::shared_ptr<JN_Application> app;

	std::unique_ptr<JN_Background> bg;
	std::unique_ptr<JN_Camera> camera;
	std::unique_ptr<JN_Bubble> bubble;
	std::unique_ptr<JN_Player> player;

	void Input();
	void Update();
	void LateUpdate();
	void Render();
};

