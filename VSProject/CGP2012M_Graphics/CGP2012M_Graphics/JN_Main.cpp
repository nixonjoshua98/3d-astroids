
#include "JN_Application.h"
#include "JN_Game.h"

#include <memory>
#include <ctime>

/*
	3D Geometry:
		Pass:	Geometry for bubbles & player
		2:2:	Visible world boundaries							DONE
		2:1:	Skybox
		1st:	.obj files with textures							DONE
		1st+:	Normal data is also loaded

	Playable Game:
		Pass:	Player can move/rotate and bubbles move
		2:2:	Bubbles stay in world boundaries					DONE
		2:1:	Bubbles destroyed on hit
		1st:	Lives/score shown on 2D HUD
		1st+:	Gameplay modifying feature

	Lighting & Textures:
		Pass:	Geometry is textured								DONE
		2:2:	Lighting from one source							DONE
		2:1:	Multiple light sources
		1st:	Dynamic lighting (eg player has a light source)
		1st+:	Different lighting models can be selected

	Shaders
		Pass:	Shaders in own file									DONE
		2:2:	Pass variable data									DONE
		2:1:	Random colouring of the bubble is created			DONE
		1st:	Textures/geometry changed by shaders				DONE
		1st+:	Animation via shader

*/

int main(int argc, char *argv[]) {
	std::shared_ptr<JN_Application> app;
	std::unique_ptr<JN_Game> game;

	srand(time(NULL));

	app = std::make_unique<JN_Application>();

	app->Init();

	game = std::make_unique<JN_Game>(app);

	game->Run();

	return 0;
}