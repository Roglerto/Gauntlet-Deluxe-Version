#ifndef __MODULEGOLEVEL5_H__
#define __MODULEGOLEVEL5_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Timer.h"
struct SDL_Texture;
class ModuleGoLevel5 :public Module
{
public:
	ModuleGoLevel5(bool start_enabled = true);
	~ModuleGoLevel5();

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
