
#include "JN_Application.h"
#include "JN_Game.h"

#include <memory>

std::shared_ptr<JN_Application> app;
std::unique_ptr<JN_Game> game;

int main(int argc, char *argv[]) {
	app = std::make_unique<JN_Application>();

	app->Init();

	game = std::make_unique<JN_Game>(app);

	game->Run();

	return 0;
}