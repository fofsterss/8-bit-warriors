#include "Game.h"
#include "Map.h"
#include "GameObject.h"

Game *game = nullptr;
int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime, player = 1;

	game = new Game();
	game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Map::map_size*32, Map::map_size * 32, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		if (player == 1)
			player = game->handleEventsP1();
		else
			if(player == 2)
				player = game->handleEventsP2();
		game->update();
		game->render(player);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	while (game->victory() == true) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			game->setvictoryfalse();
			break;
		default:
			break;
		}
		game->render(player);
	}

	if(game->victory() == false)
		game->clean();

	return 0;
}