#include "Game.h"

class GameObject {
private:
	SDL_Texture* objTexture, * hpTexture;
	SDL_Rect srcRect, destRect;
	int id, utype, hp, atk, atkrange, mov, xpos, ypos;
	bool atkmov, highlighted;

public:
	GameObject(const char* texturesheet, int id, int utype, int hp, int atk, int atkrange, int mov, int xpos, int ypos, bool atkmov = true);
	~GameObject();
	static const int army_size = 7; ///Constanta responsabila pentru Army Size (duh)
	void afisare();
	void Update();
	void Render();

	int GetX();
	int GetY();
	int GetID();
	void Delet();
	int GetUType();
	int GetHP();
	int GetMov();
	int GetAtk();
	int GetAtkRange();
	bool GetAtkMov();
	bool GetHighlight();
	void ChangeTexture();
	void DefaultTextureP1();
	void DefaultTextureP2();
	void MoveTo(int, int);
	void Dmg(int);
	void SetAtkMovNull();
	void ResetMov();
};