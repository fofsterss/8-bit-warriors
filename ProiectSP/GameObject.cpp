#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
using namespace std;

GameObject::GameObject(const char* texturesheet, int id, int utype, int hp, int atk, int atkrange, int mov, int xpos, int ypos, bool atkmov) {
	objTexture = TextureManager::LoadTexture(texturesheet);
	this->id = id;
	this->utype = utype;
	this->hp = hp;
	switch (this->hp)
	{
	case 1:
		hpTexture = TextureManager::LoadTexture("assets/hp1.png");
		break;
	case 2:
		hpTexture = TextureManager::LoadTexture("assets/hp2.png");
		break;
	case 3:
		hpTexture = TextureManager::LoadTexture("assets/hp3.png");
		break;
	case 4:
		hpTexture = TextureManager::LoadTexture("assets/hp4.png");
		break;
	case 5:
		hpTexture = TextureManager::LoadTexture("assets/hp5.png");
		break;
	case 6:
		hpTexture = TextureManager::LoadTexture("assets/hp6.png");
		break;
	case 7:
		hpTexture = TextureManager::LoadTexture("assets/hp7.png");
		break;
	case 8:
		hpTexture = TextureManager::LoadTexture("assets/hp8.png");
		break;
	case 9:
		hpTexture = TextureManager::LoadTexture("assets/hp9.png");
		break;
	case 10:
		hpTexture = TextureManager::LoadTexture("assets/hp10.png");
		break;
	case 11:
		hpTexture = TextureManager::LoadTexture("assets/hp11.png");
		break;
	case 12:
		hpTexture = TextureManager::LoadTexture("assets/hp12.png");
		break;
	default:
		break;
	}
	this->atk = atk;
	this->atkrange = atkrange;
	this->mov = mov;
	this->atkmov = atkmov;
	this->xpos = xpos*32;
	this->ypos = ypos*32;
	this->highlighted = false;
	this->afisare();
}

GameObject::~GameObject() {}

void GameObject::afisare() {
	cout << "ID: " << this->id << " UTYPE: " << this->utype << " HP: " << this->hp << " ATK: " << this->atk << " ATKRANGE: " << this->atkrange << " MOV: " << this->mov << " ATKMOV: " << this->atkmov << " POZ: " << this->xpos / 32 << ", " << this->ypos / 32 << endl << endl;
}

void GameObject::Update() {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	switch (this->hp)
	{
	case 1:
		hpTexture = TextureManager::LoadTexture("assets/hp1.png");
		break;
	case 2:
		hpTexture = TextureManager::LoadTexture("assets/hp2.png");
		break;
	case 3:
		hpTexture = TextureManager::LoadTexture("assets/hp3.png");
		break;
	case 4:
		hpTexture = TextureManager::LoadTexture("assets/hp4.png");
		break;
	case 5:
		hpTexture = TextureManager::LoadTexture("assets/hp5.png");
		break;
	case 6:
		hpTexture = TextureManager::LoadTexture("assets/hp6.png");
		break;
	case 7:
		hpTexture = TextureManager::LoadTexture("assets/hp7.png");
		break;
	case 8:
		hpTexture = TextureManager::LoadTexture("assets/hp8.png");
		break;
	case 9:
		hpTexture = TextureManager::LoadTexture("assets/hp9.png");
		break;
	case 10:
		hpTexture = TextureManager::LoadTexture("assets/hp10.png");
		break;
	case 11:
		hpTexture = TextureManager::LoadTexture("assets/hp11.png");
		break;
	case 12:
		hpTexture = TextureManager::LoadTexture("assets/hp12.png");
		break;
	default:
		break;
	}
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	SDL_RenderCopy(Game::renderer, hpTexture, &srcRect, &destRect);
}

int GameObject::GetX() {
	return this->xpos/32;
}

int GameObject::GetY() {
	return this->ypos/32;
}

int GameObject::GetID() {
	return this->id;
}

void GameObject::Delet() {
	this->id = 0;
}

int GameObject::GetUType() {
	return this->utype;
}

int GameObject::GetHP() {
	return this->hp;
}

int GameObject::GetMov() {
	return this->mov;
}

int GameObject::GetAtk() {
	return this->atk;
}

int GameObject::GetAtkRange() {
	return this->atkrange;
}

bool GameObject::GetAtkMov() {
	return this->atkmov;
}

bool GameObject::GetHighlight() {
	return this->highlighted;
}

void GameObject::ChangeTexture() {
	switch (this->utype) {
	case 1:
		this->objTexture = TextureManager::LoadTexture("assets/crownh.png");
		this->highlighted = true;
		break;
	case 2:
		this->objTexture = TextureManager::LoadTexture("assets/swordh.png");
		this->highlighted = true;
		break;
	case 3:
		this->objTexture = TextureManager::LoadTexture("assets/bowh.png");
		this->highlighted = true;
		break;
	case 4:
		this->objTexture = TextureManager::LoadTexture("assets/juanh.png");
		this->highlighted = true;
		break;
	default:
		break;
	}
}

void GameObject::DefaultTextureP1() {
	switch (this->utype) {
	case 1:
		this->objTexture = TextureManager::LoadTexture("assets/crown1.png");
		this->highlighted = false;
		break;
	case 2:
		this->objTexture = TextureManager::LoadTexture("assets/sword1.png");
		this->highlighted = false;
		break;
	case 3:
		this->objTexture = TextureManager::LoadTexture("assets/bow1.png");
		this->highlighted = false;
		break;
	case 4:
		this->objTexture = TextureManager::LoadTexture("assets/juan1.png");
		this->highlighted = false;
		break;
	default:
		break;
	}
}

void GameObject::DefaultTextureP2() {
	switch (this->utype) {
	case 1:
		this->objTexture = TextureManager::LoadTexture("assets/crown2.png");
		this->highlighted = false;
		break;
	case 2:
		this->objTexture = TextureManager::LoadTexture("assets/sword2.png");
		this->highlighted = false;
		break;
	case 3:
		this->objTexture = TextureManager::LoadTexture("assets/bow2.png");
		this->highlighted = false;
		break;
	case 4:
		this->objTexture = TextureManager::LoadTexture("assets/juan2.png");
		this->highlighted = false;
		break;
	default:
		break;
	}
}

void GameObject::MoveTo(int x, int y) {
	this->xpos = x*32;
	this->ypos = y*32;
	this->mov = 0;
}

void GameObject::Dmg(int dmg) {
	this->hp = this->hp - dmg;
}

void GameObject::SetAtkMovNull() {
	this->atkmov = 0;
}

void GameObject::ResetMov() {
	this->atkmov = 1;
	switch (this->utype) {
	case 1:
		this->mov = 2;
		break;
	case 2:
		this->mov = 3;
		break;
	case 3:
		this->mov = 2;
		break;
	case 4:
		this->mov = 4;
		break;
	default:
		break;
	}
}