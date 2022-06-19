#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
#include <sstream>

GameObject** player1 = new GameObject * [GameObject::army_size];
GameObject** player2 = new GameObject * [GameObject::army_size];
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Rect src, dest;
SDL_Texture* victoryscreen;

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window created..." << std::endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255);
			std::cout << "Renderer created..." << std::endl;
		}

		isRunning = true;
	}
	else
		isRunning = false;

	int x = Map::map_size / 2;

	player1[0] = new GameObject("assets/crown1.png", 1, 1, 12, 2, 1, 2, x, 2);
	player1[1] = new GameObject("assets/bow1.png", 2, 3, 8, 3, 4, 2, x-1, 2);
	player1[2] = new GameObject("assets/bow1.png", 3, 3, 8, 3, 4, 2, x+1, 2);
	player1[3] = new GameObject("assets/sword1.png", 4, 2, 10, 3, 1, 3, x-1, 3);
	player1[4] = new GameObject("assets/sword1.png", 5, 2, 10, 3, 1, 3, x, 3);
	player1[5] = new GameObject("assets/sword1.png", 6, 2, 10, 3, 1, 3, x+1, 3);
	player1[6] = new GameObject("assets/juan1.png", 7, 4, 9, 4, 1, 4, x, 4);

	player2[0] = new GameObject("assets/crown2.png", 8, 1, 12, 2, 1, 2, x, x*2-2);
	player2[1] = new GameObject("assets/bow2.png", 9, 3, 8, 3, 4, 2, x-1, x*2-2);
	player2[2] = new GameObject("assets/bow2.png", 10, 3, 8, 3, 4, 2, x+1, x*2-2);
	player2[3] = new GameObject("assets/sword2.png", 11, 2, 10, 3, 1, 3, x-1, x*2-3);
	player2[4] = new GameObject("assets/sword2.png", 12, 2, 10, 3, 1, 3, x, x*2-3);
	player2[5] = new GameObject("assets/sword2.png", 13, 2, 10, 3, 1, 3, x+1, x*2-3);
	player2[6] = new GameObject("assets/juan2.png", 14, 4, 9, 4, 1, 4, x, x*2-4);

	map = new Map();

	for (int i = 0; i < GameObject::army_size; i++) {
		map->unitmap[player1[i]->GetX()][player1[i]->GetY()] = player1[i]->GetID(); ///Pozitii unitati player1
		map->unitmap[player2[i]->GetX()][player2[i]->GetY()] = player2[i]->GetID(); ///Pozitii unitati player2
	}

	for (int i = 0; i < Map::map_size; i++) {
		for (int j = 0; j < Map::map_size; j++)
			std::cout << map->unitmap[j][i] << ' ';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int Game::handleEventsP1() {
	SDL_Event event;
	SDL_PollEvent(&event);
	int id = -1, pozp2 = -1;

	map->changeplayer(1);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEMOTION:
		{
			int xposm = event.motion.x/32;
			int yposm = event.motion.y/32;
			std::stringstream ss;
			ss << "X: " << xposm << " Y: " << yposm;
			SDL_SetWindowTitle(window, ss.str().c_str());
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			int xposm = event.motion.x/32;
			int yposm = event.motion.y/32;
			for (int i = 0; i < GameObject::army_size; i++) {
				if (xposm == player1[i]->GetX() && yposm == player1[i]->GetY())
					if (event.button.button == SDL_BUTTON_LEFT && player1[i]->GetHighlight() == false && player1[i]->GetID() != 0)
					{
						player1[i]->ChangeTexture();
						for (int i = 0; i < Map::map_size; i++)
							for (int j = 0; j < Map::map_size; j++)
								map->highlightmap[i][j] = 0;
						for (int j = 0; j < GameObject::army_size; j++)
							if(i!=j)
								player1[j]->DefaultTextureP1();
						for (int k = player1[i]->GetX() - player1[i]->GetMov(); k <= player1[i]->GetX() + player1[i]->GetMov(); k++)
							for (int u = player1[i]->GetY() - player1[i]->GetMov(); u <= player1[i]->GetY() + player1[i]->GetMov(); u++)
								map->highlightmap[u][k] = 1;
					}
			}
			for (int i = 0; i < GameObject::army_size; i++)
				if (event.button.button == SDL_BUTTON_RIGHT && player1[i]->GetHighlight() == true && map->tilemap[xposm][yposm] != 1) {
					if (map->unitmap[xposm][yposm] == 0)
						if (xposm <= player1[i]->GetX() + player1[i]->GetMov() && xposm >= player1[i]->GetX() - player1[i]->GetMov() && yposm <= player1[i]->GetY() + player1[i]->GetMov() && yposm >= player1[i]->GetY() - player1[i]->GetMov())
						{
							map->unitmap[player1[i]->GetX()][player1[i]->GetY()] = 0;
							player1[i]->MoveTo(xposm, yposm);
							map->unitmap[player1[i]->GetX()][player1[i]->GetY()] = player1[i]->GetID();
							for (int i = 0; i < Map::map_size; i++)
								for (int j = 0; j < Map::map_size; j++)
									map->highlightmap[i][j] = 0;
						}
					id = map->unitmap[xposm][yposm];
					if (id >= player2[0]->GetID() && player1[i]->GetAtkRange() >= abs(player1[i]->GetX() - xposm) && player1[i]->GetAtkRange() >= abs(player1[i]->GetY() - yposm) && player1[i]->GetAtkMov())
					{
						for (int j = 0; j < GameObject::army_size; j++)
							if (id == player2[j]->GetID())
								pozp2 = j;
						player2[pozp2]->Dmg(player1[i]->GetAtk());
						player2[pozp2]->afisare();
						if (player1[i]->GetUType() != 3)
							player1[i]->Dmg(player2[pozp2]->GetAtk() / 2);
						if(player2[pozp2]->GetHP() <= 0) {
							map->unitmap[xposm][yposm] = 0;
							player2[pozp2]->Delet();
						}
						if (player1[i]->GetHP() <= 0) {
							map->unitmap[player1[i]->GetX()][player1[i]->GetY()] = 0;
							player1[i]->Delet();
						}
						player1[i]->SetAtkMovNull();
					}
				}
			if (event.button.button == SDL_BUTTON_LEFT && xposm == Map::map_size - 1 && yposm == Map::map_size - 1) {
				for (int i = 0; i < GameObject::army_size; i++)
					player1[i]->DefaultTextureP1();
				for (int i = 0; i < Map::map_size; i++)
					for (int j = 0; j < Map::map_size; j++)
						map->highlightmap[i][j] = 0;
				for (int i = 0; i < GameObject::army_size; i++)
					player1[i]->ResetMov();
				return 2;
			}
			if (player1[0]->GetHP() <= 0) {
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
				Game::isRunning = false;
				Game::victorycon = true;

				src.x = src.y = 0;
				src.w = dest.w = 608;
				src.h = dest.h = 352;
				dest.x = (Map::map_size / 2 - 9)*32;
				dest.y = (Map::map_size / 2 - 5)*32;

				victoryscreen = TextureManager::LoadTexture("assets/player2victory.png");
				SDL_RenderCopy(Game::renderer, victoryscreen, &src, &dest);
				SDL_RenderPresent(renderer);

				return 3;
			}
			if (player2[0]->GetHP() <= 0) {
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
				Game::isRunning = false;
				Game::victorycon = true;

				src.x = src.y = 0;
				src.w = dest.w = 608;
				src.h = dest.h = 352;
				dest.x = (Map::map_size / 2 - 9) * 32;
				dest.y = (Map::map_size / 2 - 5) * 32;

				victoryscreen = TextureManager::LoadTexture("assets/player1victory.png");
				SDL_RenderCopy(Game::renderer, victoryscreen, &src, &dest);
				SDL_RenderPresent(renderer);

				return 4;
				
			}
		}
		default:
			break;
	}
	return 1;
}



int Game::handleEventsP2() {
	SDL_Event event;
	SDL_PollEvent(&event);
	int id = -1, pozp1 = -1;

	map->changeplayer(2);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEMOTION:
	{
		int xposm = event.motion.x / 32;
		int yposm = event.motion.y / 32;
		std::stringstream ss;
		ss << "X: " << xposm << " Y: " << yposm;
		SDL_SetWindowTitle(window, ss.str().c_str());
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{	
		int xposm = event.motion.x / 32;
		int yposm = event.motion.y / 32;
		for (int i = 0; i < GameObject::army_size; i++) {
			if (xposm == player2[i]->GetX() && yposm == player2[i]->GetY())
				if (event.button.button == SDL_BUTTON_LEFT && player2[i]->GetHighlight() == false && player2[i]->GetID() != 0)
				{
					player2[i]->ChangeTexture();
					for (int i = 0; i < Map::map_size; i++)
						for (int j = 0; j < Map::map_size; j++)
							map->highlightmap[i][j] = 0;
					for (int j = 0; j < GameObject::army_size; j++)
						if (i != j)
							player2[j]->DefaultTextureP2();
					for (int k = player2[i]->GetX() - player2[i]->GetMov(); k <= player2[i]->GetX() + player2[i]->GetMov(); k++)
						for (int u = player2[i]->GetY() - player2[i]->GetMov(); u <= player2[i]->GetY() + player2[i]->GetMov(); u++)
							map->highlightmap[u][k] = 1;
				}
		}
		for (int i = 0; i < GameObject::army_size; i++)
			if (event.button.button == SDL_BUTTON_RIGHT && player2[i]->GetHighlight() == true && map->tilemap[xposm][yposm] != 1) {
				if (map->unitmap[xposm][yposm] == 0)
					if (xposm <= player2[i]->GetX() + player2[i]->GetMov() && xposm >= player2[i]->GetX() - player2[i]->GetMov() && yposm <= player2[i]->GetY() + player2[i]->GetMov() && yposm >= player2[i]->GetY() - player2[i]->GetMov())
					{
						map->unitmap[player2[i]->GetX()][player2[i]->GetY()] = 0;
						player2[i]->MoveTo(xposm, yposm);
						map->unitmap[player2[i]->GetX()][player2[i]->GetY()] = player2[i]->GetID();
						for (int i = 0; i < Map::map_size; i++)
							for (int j = 0; j < Map::map_size; j++)
								map->highlightmap[i][j] = 0;
					}
				id = map->unitmap[xposm][yposm];
				if (id < player2[0]->GetID() && id > 0 && player2[i]->GetAtkRange() >= abs(player2[i]->GetX() - xposm) && player2[i]->GetAtkRange() >= abs(player2[i]->GetY() - yposm) && player2[i]->GetAtkMov())
				{
					for (int j = 0; j < GameObject::army_size; j++)
						if (id == player1[j]->GetID())
							pozp1 = j;
					player1[pozp1]->Dmg(player2[i]->GetAtk());
					player1[pozp1]->afisare();
					if (player2[i]->GetUType() != 3)
						player2[i]->Dmg(player1[pozp1]->GetAtk() / 2);
					if (player1[pozp1]->GetHP() <= 0) {
						map->unitmap[xposm][yposm] = 0;
						player1[pozp1]->Delet();
					}
					if (player2[i]->GetHP() <= 0) {
						map->unitmap[player2[i]->GetX()][player2[i]->GetY()] = 0;
						player2[i]->Delet();
					}
					player2[i]->SetAtkMovNull();
				}
			}
		if (event.button.button == SDL_BUTTON_LEFT && xposm == Map::map_size - 1 && yposm == Map::map_size - 1) {
			for (int i = 0; i < GameObject::army_size; i++)
				player2[i]->DefaultTextureP2();
			for (int i = 0; i < Map::map_size; i++)
				for (int j = 0; j < Map::map_size; j++)
					map->highlightmap[i][j] = 0;
			for (int i = 0; i < GameObject::army_size; i++)
				player2[i]->ResetMov();
			return 1;
		}
		if (player1[0]->GetHP() <= 0) {
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			Game::isRunning = false;
			Game::victorycon = true;

			src.x = src.y = 0;
			src.w = dest.w = 608;
			src.h = dest.h = 352;
			dest.x = (Map::map_size / 2 - 9) * 32;
			dest.y = (Map::map_size / 2 - 5) * 32;

			victoryscreen = TextureManager::LoadTexture("assets/player2victory.png");
			SDL_RenderCopy(Game::renderer, victoryscreen, &src, &dest);
			SDL_RenderPresent(renderer);

			return 3;
		}
		if (player2[0]->GetHP() <= 0) {
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			Game::isRunning = false;
			Game::victorycon = true;

			src.x = src.y = 0;
			src.w = dest.w = 608;
			src.h = dest.h = 352;
			dest.x = (Map::map_size / 2 - 9) * 32;
			dest.y = (Map::map_size / 2 - 5) * 32;

			victoryscreen = TextureManager::LoadTexture("assets/player1victory.png");
			SDL_RenderCopy(Game::renderer, victoryscreen, &src, &dest);
			SDL_RenderPresent(renderer);

			return 4;
		}
	}
	default:
		break;
	}

	return 2;
}

void Game::update() {
	for (int i = 0; i < GameObject::army_size; i++) {
		player1[i]->Update();
		player2[i]->Update();
	}
}

void Game::render(int x) {
	if (x < 3) {
		SDL_RenderClear(renderer);
		map->DrawMap();
		for (int i = 0; i < GameObject::army_size; i++)
			if (player1[i]->GetID() != 0)
				player1[i]->Render();

		for (int i = 0; i < GameObject::army_size; i++)
			if (player2[i]->GetID() != 0)
				player2[i]->Render();
		SDL_RenderPresent(renderer);
	}
	else {
		if (x == 3) {
			SDL_RenderClear(renderer);
			
		}
		if (x == 4) {
			SDL_RenderClear(renderer);
			
		}
	}
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::setvictoryfalse() {
	this->victorycon = false;
}

bool Game::running(){
	return this->isRunning; 
}
bool Game::victory() {
	return this->victorycon; 
}