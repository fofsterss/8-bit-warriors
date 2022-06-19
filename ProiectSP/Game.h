#pragma once
#include "SDL.h"

class Game {
private:
	int cnt = 0;
	bool isRunning, victorycon;
	SDL_Window* window;
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	int handleEventsP1();
	int handleEventsP2();
	void update();
	void render(int);
	void clean();
	void setvictoryfalse();

	static SDL_Renderer* renderer;

	bool running();
	bool victory();
};