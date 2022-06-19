#include "Game.h"

class Map {
private:
	SDL_Rect src, dest;
	SDL_Texture* mountains;
	SDL_Texture* plains;
	SDL_Texture* water;
	SDL_Texture* forest;
	SDL_Texture* nextButton;
	SDL_Texture* highlight;
	SDL_Texture* playericon;

public:
	Map();
	~Map();
	static const int map_size = 21; ///Constanta responsabila pentru Map Size (duh)
	void DrawMap();
	int tilemap[100][100] = { 0 };
	int unitmap[100][100] = { 0 };
	int highlightmap[100][100] = { 0 };
	void changeplayer(int);
};