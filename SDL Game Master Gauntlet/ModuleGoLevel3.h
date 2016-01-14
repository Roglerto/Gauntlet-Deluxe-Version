#ifndef __MODULEGOLEVEL3_H__
#define __MODULEGOLEVEL3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Timer.h"
struct SDL_Texture;
class ModuleGoLevel3 :public Module
{
public:
	ModuleGoLevel3(bool start_enabled = true);
	~ModuleGoLevel3();

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

