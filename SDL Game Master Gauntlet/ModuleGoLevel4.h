#ifndef __MODULEGOLEVEL4_H__
#define __MODULEGOLEVEL4_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Timer.h"
struct SDL_Texture;
class ModuleGoLevel4 :public Module
{
public:
	ModuleGoLevel4(bool start_enabled = true);
	~ModuleGoLevel4();

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
