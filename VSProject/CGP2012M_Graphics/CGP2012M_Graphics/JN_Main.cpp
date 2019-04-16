
#include "JN_Application.h"
#include "JN_Game.h"

#include <memory>
#include <ctime>

/*
	3D Geometry: (25%)
		Pass:	Geometry for bubbles & player						DONE
		2:2:	Visible world boundaries							DONE
		2:1:	Skybox												DONE
		1st:	.obj files with textures							DONE
		1st+:	Normal data is also loaded							DONE

	Playable Game: (5%)
		Pass:	Player can move/rotate and bubbles move				DONE
		2:2:	Bubbles stay in world boundaries					DONE
		2:1:	Bubbles destroyed on hit							DONE
		1st:	Lives/score shown on 2D HUD							DONE
		1st+:	Gameplay modifying feature

	Lighting & Textures: (30%)
		Pass:	Geometry is textured								DONE
		2:2:	Lighting from one source							DONE
		2:1:	Multiple light sources
		1st:	Dynamic lighting (eg player has a light source)
		1st+:	Different lighting models can be selected

	Shaders (25%)
		Pass:	Shaders in own file									DONE
		2:2:	Pass variable data									DONE
		2:1:	Random colouring of the bubble is created			DONE
		1st:	Textures/geometry changed by shaders				
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