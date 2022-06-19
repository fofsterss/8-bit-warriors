#include "Map.h"
#include "TextureManager.h"
#include <iostream>
#include <time.h>

int rand_lim(int l) {
	int div = RAND_MAX / (l + 1), r;
	do {
		r = rand() / div;
	}     while (r > l);
	return r;
}

Map::Map() {
	playericon = TextureManager::LoadTexture("assets/player1.png");
	mountains = TextureManager::LoadTexture("assets/mountains.png");
	plains = TextureManager::LoadTexture("assets/plains.png");
	water = TextureManager::LoadTexture("assets/water.png");
	forest = TextureManager::LoadTexture("assets/forest.png");
	nextButton = TextureManager::LoadTexture("assets/nextButton.png");
	highlight = TextureManager::LoadTexture("assets/highlight.png");

	time_t t;
	srand((unsigned)time(&t));
	rand_lim(1); ///rand() is big bruh
	int i;

	for (int row = 0; row < map_size; row++) {
		for (int column = 0; column < map_size; column++) {
			i = rand_lim(map_size);
			tilemap[row][column] = 3;
			if (row == i || column == i)
				tilemap[row][column] = 4;
			if (row == map_size/2)
				tilemap[row][column] = 2;
			if (row == 0 || column == 0 || row == map_size - 1 || column == map_size - 1)
				tilemap[row][column] = 1;
			if (row == map_size - 1 && column == map_size - 1)
				tilemap[row][column] = 5;
			if (row == 0 && column == map_size - 1)
				tilemap[row][column] = 6;
		}
	}

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;
	dest.x = dest.y = 0;
}

Map::~Map()	{}

void Map::DrawMap() {
	int type = 0, isHighlighted = 0;

	for (int row = 0; row < map_size; row++) {
		for (int column = 0; column < map_size; column++) {
			type = tilemap[row][column];
			isHighlighted = highlightmap[row][column];

			dest.x = column * 32;
			dest.y = row * 32;

			switch (type) {
			case 1:
				TextureManager::Draw(mountains, src, dest);
				break;
			case 2:
				TextureManager::Draw(water, src, dest);
				if (isHighlighted)
					TextureManager::Draw(highlight, src, dest);
				break;
			case 3:
				TextureManager::Draw(plains, src, dest);
				if (isHighlighted)
					TextureManager::Draw(highlight, src, dest);
				break;
			case 4:
				TextureManager::Draw(forest, src, dest);
				if (isHighlighted)
					TextureManager::Draw(highlight, src, dest);
				break;
			case 5:
				TextureManager::Draw(nextButton, src, dest);
				break;
			case 6:
				TextureManager::Draw(playericon, src, dest);
				break;

			default:
				break;
			}
		}
	}
}

void Map::changeplayer(int x) {
	if(x == 1)
		playericon = TextureManager::LoadTexture("assets/player1.png");
	else
		playericon = TextureManager::LoadTexture("assets/player2.png");
}