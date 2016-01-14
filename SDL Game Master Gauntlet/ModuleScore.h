#ifndef __MODULESCORE_H__
#define __MODULESCORE_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include <fstream>
#include <vector>
#include "SDL2_ttf-2.0.13/include/SDL_ttf.h"
#pragma comment( lib, "SDL2_ttf-2.0.13/lib/x86/SDL2_ttf.lib" )

struct SDL_Texture;
struct SDL_Surface;

class ModuleScore : public Module
{
public:
	ModuleScore(bool start_enabled = true);
	~ModuleScore();

	fstream myfilemap;
	vector<int> scores;
	SDL_Rect background;
	update_status Update();
	bool CleanUp();
	bool Init();
	bool Start();
	
	SDL_Surface *message = NULL;
	SDL_Surface *message2 = NULL;
	SDL_Surface *message3 = NULL;
	SDL_Surface *message4 = NULL;

	SDL_Surface *position1 = NULL;
	SDL_Surface *position2 = NULL;
	SDL_Surface *position3 = NULL;

	uint fx = 0;
	//The font that's going to be used
	TTF_Font *font = NULL;
	TTF_Font *font2 = NULL;
	char buffer[33];
	//The color of the font
	SDL_Color textColorscore;
	SDL_Color textColortxt;
	SDL_Color textColornumber;
	SDL_Texture* graphics2 = nullptr;
	Animation gauntlet;

	SDL_Texture* score;
	SDL_Texture* number1;
	SDL_Texture* number2;
	SDL_Texture* number3;

	SDL_Texture* p1;
	SDL_Texture* p2;
	SDL_Texture* p3;
};

#endif