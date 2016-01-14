#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include <fstream>
#include <vector>
#include <string>
#include "Point.h"
#include "ModuleParticles.h"
#include "Timer.h"


struct Collider;
struct Ghost;

class ModuleLevel3 : public Module
{
public:
	ModuleLevel3(bool start_enabled = true);
	~ModuleLevel3();

	bool readmap();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


public:

	SDL_Texture* background;
	SDL_Texture* stars;

	SDL_Rect sideswall;
	SDL_Rect floor;
	SDL_Rect uprightcorner;
	SDL_Rect upleftcorner;
	SDL_Rect botrightcorner;
	SDL_Rect botleftcorner;
	SDL_Rect downwall;

	SDL_Rect door;

	int FIL;
	int COL;
	fstream myfilemap, myfile;
	char* map1;
	vector<char> map;

	iPoint posmapelement;

	int posx = 0;
	bool addcolider = true;

	Animation explosionani;
	Particle explosion;
	void OnCollision(Collider* c1, Collider* c2);
	bool  explo = false;
	iPoint posexplosion;
	Timer timeexplosion;


};
