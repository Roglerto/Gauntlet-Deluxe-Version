#ifndef __MODULELEVEL1_H__
#define __MODULELEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Timer.h"
struct SDL_Texture;
class ModuleLevel1 :public Module
{
public:
	ModuleLevel1(bool start_enabled = true);
	~ModuleLevel1();

	bool Start();
	update_status Update();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	bool start = false;
	Timer time;
	SDL_Texture* graphics = nullptr;
	Animation title;
	SDL_Rect background;
};

#endif