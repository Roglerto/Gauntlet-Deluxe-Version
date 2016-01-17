#ifndef __MODULESIDEMENU_H__
#define __MODULESIDEMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "SDL2_ttf-2.0.13/include/SDL_ttf.h"
#pragma comment( lib, "SDL2_ttf-2.0.13/lib/x86/SDL2_ttf.lib" )

struct SDL_Texture;
struct SDL_Surface;


class ModuleSideMenu : public Module
{
public:
	ModuleSideMenu(bool start_enabled = true);
	~ModuleSideMenu();


	SDL_Rect  keymenu;

	SDL_Rect  potion1;
	SDL_Rect  potion2;
	SDL_Rect  potion3;

	SDL_Texture* number;
	SDL_Texture* number2;
	SDL_Texture* pj;
	SDL_Texture* lvl;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Animation title;
	Animation gauntlet;
	Animation* background;
	Animation number0;
	
	uint fx = 0;

	void draw(int x,int pos);
	void displaynumber(int x);

	bool Init();
	bool Start();
	update_status PostUpdate();
	update_status Update();
	bool CleanUp();

	iPoint positionmenu;
	iPoint positiontitle;

	SDL_Surface *message = NULL;
	SDL_Surface *message2 = NULL;
	SDL_Surface *message3 = NULL;
	SDL_Surface *message4 = NULL;

	//The font that's going to be used
	TTF_Font *font = NULL;
	TTF_Font *font2 = NULL;
	char buffer[33];
	//The color of the font
	SDL_Color textColor ;
	SDL_Color textColorlvl;
	SDL_Color textColorpj;
	
};

#endif 