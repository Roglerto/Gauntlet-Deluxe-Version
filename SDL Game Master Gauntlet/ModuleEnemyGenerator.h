#ifndef __MODULEENEMYGENERATOR_H__
#define __MODULEENEMYGENERATOR_H__

#include "Module.h"
#include "Animation.h"
#include <list>
#include "Point.h"
#include "Timer.h"
#include <string>
struct SDL_Texture;
struct Collider;

using namespace std;
struct ghostgenerator{

	SDL_Texture* graphicsgenerator = nullptr;

	iPoint position;
	Timer timer;

	uint32 life = 1;
	bool generateEnemy;

	bool colisionN = false;
	bool colisionS = false;
	bool colisionE = false;
	bool colisionW = false;

	Collider* collider = nullptr;

	Collider* colliderN = nullptr;
	Collider* colliderS = nullptr;
	Collider* colliderE = nullptr;
	Collider* colliderW = nullptr;
	Animation generator;
	bool wall = false;

	ghostgenerator();
	~ghostgenerator();
};

class ModuleEnemyGenerator : public Module
{
public:
	ModuleEnemyGenerator(bool start_enabled = true);
	~ModuleEnemyGenerator();

	void AddGenerator(int x, int y);
	void OnCollision(Collider* c1, Collider* c2);
	void addenemy(int x, int y);

	bool Start();
	bool CleanUp();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	list<ghostgenerator *> generatorlist;
	SDL_Texture* ghostimage;

	Timer timeexplosion;
	Timer generatingN;
	Timer generatingS;
	Timer generatingW;
	Timer generatingE;
	int life = 2;
	bool explo = false;

	bool borrar = false;
	bool borrarN=false;
	bool borrarS = false;
	bool borrarE = false;
	bool borrarW = false;

	bool start = false;

	iPoint posexplosion;
	Animation explosionani;
};

#endif