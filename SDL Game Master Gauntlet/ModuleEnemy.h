#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"
#include "Animation.h"
#include <list>
#include "Point.h"
#include "Timer.h"
#include <string>
struct SDL_Texture;
struct Collider;

using namespace std;

struct Ghost{

	SDL_Texture* graphicsghost = nullptr;

	unsigned int fx = 0;
	iPoint position = { 0, 0 };
	iPoint speed = { 0, 0 };
	Timer timer;
	uint32 delay;
	uint32 born = 0;
	uint32 life = 1;
	bool fx_played = false;
	Collider* collider = nullptr;

	
	bool Update();

	string orientation;
	string orientationenemy;
	iPoint oldposition = { 0, 0 };

	bool colisionN=false;
	bool colisionS = false;
	bool colisionW = false;
	bool colisionE = false;

	bool colisionNE = false;
	bool colisionNW = false;
	bool colisionSE = false;
	bool colisionSW = false;

	bool colisionNenemy = false;
	bool colisionSenemy = false;
	bool colisionWenemy = false;
	bool colisionEenemy = false;

	bool colisionNEenemy = false;
	bool colisionNWenemy = false;
	bool colisionSEenemy = false;
	bool colisionSWenemy = false;

	Timer timerdeath;
	iPoint dir;

	double angulo,oldangulo;
	int speedd = 1;
	


	Ghost();
	~Ghost();
	Animation animghostnorth;
	Animation animghostsouth;
	Animation animghosteast;
	Animation animghostwest;

	Animation animghostnortheast;
	Animation animghostnorthwest;
	Animation animghostsoutheast;
	Animation animghostsouthwest;

	Animation anim1;
	Animation anim2;
	Animation anim3;
	Animation anim4;

	Animation anim5;
	Animation anim6;
	Animation anim7;
	Animation anim8;

	Animation* actualanimation = nullptr;;
};



class ModuleEnemy : public Module
{
public:
	ModuleEnemy(bool start_enabled = true);
	~ModuleEnemy();

	void AddGhost(int x, int y);
	
	//update_status PostUpdate();

	Timer timeexplosion;

	iPoint posexplosion;

	

	bool Start();
	bool CleanUp();
	update_status PreUpdate();
	
	update_status Update();
	update_status PostUpdate();

	void OnCollision(Collider* c1, Collider* c2);

	bool explo = false;
	SDL_Texture* ghostimage;
	Animation explosionani;
	list<Ghost *> ghostlist;
	
};

#endif