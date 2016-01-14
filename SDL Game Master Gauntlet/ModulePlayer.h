#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "Point.h"
#include <fstream>
#include <vector>

struct SDL_Texture;
struct Collider;
struct Particle;



class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);
	void OnNotCollision(Collider* c1, Collider* c2);

public:
	fstream myfilemap;
	vector<int> scores;
	int position1;
	int position2;
	int position3;
	int tm;
	bool notpause = false;
	Animation pause;
	uint fx = 0;
	uint fxe = 0;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Collider* collider = nullptr;
	Animation* current_animation = nullptr;
	Animation idlenorth;
	Animation idlesouth;
	Animation idlewest;
	Animation idleeast;

	Animation idlenortheast;
	Animation idlenorthwest;
	Animation idlesoutheast;
	Animation idlesouthwest;

	Animation north;
	Animation south;
	Animation east;
	Animation west;
	Animation northeast;
	Animation northwest;
	Animation southeast;
	Animation southwest;

	Animation idlenorthfaster;
	Animation idlesouthfaster;
	Animation idlewestfaster;
	Animation idleeastfaster;

	Animation idlenortheastfaster;
	Animation idlenorthwestfaster;
	Animation idlesoutheastfaster;
	Animation idlesouthwestfaster;

	Animation northfaster;
	Animation southfaster;
	Animation eastfaster;
	Animation westfaster;
	Animation northeastfaster;
	Animation northwestfaster;
	Animation southeastfaster;
	Animation southwestfaster;

	Animation idlenorthpower;
	Animation idlesouthpower;
	Animation idlewestpower;
	Animation idleeastpower;

	Animation idlenortheastpower;
	Animation idlenorthwestpower;
	Animation idlesoutheastpower;
	Animation idlesouthwestpower;

	Animation northpower;
	Animation southpower;
	Animation eastpower;
	Animation westpower;
	Animation northeastpower;
	Animation northwestpower;
	Animation southeastpower;
	Animation southwestpower;

	Animation idlenorthguard;
	Animation idlesouthguard;
	Animation idlewestguard;
	Animation idleeastguard;

	Animation idlenortheastguard;
	Animation idlenorthwestguard;
	Animation idlesoutheastguard;
	Animation idlesouthwestguard;

	Animation northguard;
	Animation southguard;
	Animation eastguard;
	Animation westguard;
	Animation northeastguard;
	Animation northwestguard;
	Animation southeastguard;
	Animation southwestguard;


	Animation explosionlaser;
	Animation transformation;
	bool transformation1 = false;
	bool transformation2 = false;
	bool transformation3 = false;
	Timer transformationt;
	Timer destran;
	bool destransformation = false;
	Particle explosion;   //PLAYER
	Particle laser;
	bool finished = false;
	iPoint position;

	//KeyState	keyboard;

	bool colisionfinish = false;

	bool colisionNORTH = false;
	bool colisionSOUTH = false;
	bool colisionEAST = false;
	bool colisionWEST = false;

	bool colisionNORTHEAST = false;
	bool colisionSOUTHWEST = false;
	bool colisionNORTHWEST = false;
	bool colisionSOUTHEAST = false;

	iPoint positioncolision;
	string colisionorientation;

	int camlimitx;
	int camlimity;

	bool stopandshot = false;
	
	Timer potion;
	int speed;
	int speed2;
	int life ;
	int score ;
	bool key = false;
	bool key2 = false;
	bool potion1 = false;
	bool potion2 = false;
	bool potion3 = false;
	bool activepotion = false;
	bool food = false;

	bool potion1efect = false;
	bool potion3efect = false;
	bool potion2efect = false;
};

#endif // __MODULEPLAYER_H__