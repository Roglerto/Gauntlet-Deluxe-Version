
#ifndef __MODULEGOLEVEL2_H__
#define __MODULEGGOLEVEL2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Timer.h"
struct SDL_Texture;
class  ModuleGoLevel2 :public Module
{
public:
	
	
	ModuleGoLevel2(bool start_enabled = true);
	~ModuleGoLevel2();

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