#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "Point.h"
#include "Timer.h"
#include <string>
struct Collider;
struct SDL_Texture;
enum COLLIDER_TYPE;

struct Particle
{
	SDL_Texture* graphics = nullptr;
	Animation anim;

	Animation explosion;

	unsigned int fx = 0;
	iPoint position = {0, 0};
	iPoint speed = {0, 0};
	Timer timer;
	uint32 delay;
	uint32 born = 0;
	uint32 life = 0;
	bool fx_played = false;
	Collider* collider = nullptr;

	~Particle();
	bool Update();
	

	string orientation;
	iPoint oldposition = { 0, 0 };

	Timer timerdeath;
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	update_status PostUpdate();
	bool CleanUp();

	void OnCollision(Collider*, Collider*);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE, string orientation, Uint32 delay = 0);

	SDL_Rect destructible_door();
	SDL_Rect aux;
	int tam = 0;



	std::list<Particle*> active;

};

#endif // __MODULEPARTICLES_H__