
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModulePlayer.h"
#include "ModuleSideMenu.h"




ModuleSideMenu::ModuleSideMenu(bool start_enabled) : Module(start_enabled)
{
	title.frames.push_back({ 260, 1, 117, 120 });

	gauntlet.frames.push_back({ 59,38, 101, 29 });
	gauntlet.frames.push_back({ 57, 109, 102, 29 });
	gauntlet.frames.push_back({ 57, 74, 102, 29 });
	gauntlet.frames.push_back({ 59, 38, 101, 29 });
	gauntlet.frames.push_back({ 56, 146, 102, 29 });
	gauntlet.frames.push_back({ 59, 6, 102, 29 });
	gauntlet.speed = 0.01f;

	positionmenu.x =268 ;
	positionmenu.y = 0;

	positiontitle.x = 278;
	positiontitle.y =2 ;

	textColor = { 255, 255, 0 };
	textColorlvl = { 150, 55, 200 };
	textColorpj = {205, 25, 100 };
	
	number0.frames.push_back({ 33, 82, 7, 7 });
	
	keymenu.x = 62;
	keymenu.y = 31;
	keymenu.h = 15;
	keymenu.w = 26;

	potion1.x = 99;
	potion1.y = 28;
	potion1.h = 19;
	potion1.w = 20;

	potion2.x = 124;
	potion2.y = 28;
	potion2.h = 19;
	potion2.w = 20;

	potion3.x = 148;
	potion3.y = 28;
	potion3.h = 19;
	potion3.w = 20;

	background = &number0;

	
}


ModuleSideMenu::~ModuleSideMenu()
{
	TTF_Quit();
}

bool ModuleSideMenu::Init()
{
	if (TTF_Init() != 0){
		LOG("TTF_Init error");
		SDL_Quit();
		return 1;
	}
	return true;
}

// Load assets
bool ModuleSideMenu::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	graphics = App->textures->Load("Gauntlet/sm.png");
	graphics2 = App->textures->Load("Gauntlet/item.png");
	//App->audio->PlayMusic("intro.ogg", 0.0f);
	//fx = App->audio->LoadFx("starting.wav");
	//App->renderer->camera.x = App->renderer->camera.y = 0;
	//Open the font
	font = TTF_OpenFont("Gauntlet/leters.ttf", 12);
	font2 = TTF_OpenFont("Gauntlet/leters.ttf", 16);
	return ret;
}

bool ModuleSideMenu::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);

	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	

	return true;
}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface(source, clip, destination, &offset);
}




update_status ModuleSideMenu::Update()
{
	int i=App->player->life;
	
	int j = App->player->score;
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, positionmenu.x, positionmenu.y, &(title.GetCurrentFrame()),0.0f);
	App->renderer->Blit(graphics,positiontitle.x, positiontitle.y, &(gauntlet.GetCurrentFrame()),0.0f);
	
	if ((App->player->key == true) || (App->player->key2 == true))
		App->renderer->Blit(graphics2, 270,  98, &(keymenu), 0.0f);
	if (App->player->potion1 == true)
		App->renderer->Blit(graphics2, 315, 95, &(potion1), 0.0f);
	if (App->player->potion2 == true)
		App->renderer->Blit(graphics2, 340, 95, &(potion2), 0.0f);
	if (App->player->potion3 == true)
		App->renderer->Blit(graphics2, 360, 95, &(potion3), 0.0f);

	message = TTF_RenderText_Solid(font, itoa(i, buffer, 10), textColor);
	message2 = TTF_RenderText_Solid(font, itoa(j, buffer, 10), textColor);
	message3 = TTF_RenderText_Solid(font2, " MiMiCo ", textColorpj);
	if (App->lvl1==true)
		message4 = TTF_RenderText_Solid(font2,  " LEVEL 1 ", textColorlvl);
	else if (App->lvl2==true)
		message4 = TTF_RenderText_Solid(font2, " LEVEL 2 ", textColorlvl);
	else if (App->lvl3 == true)
		message4 = TTF_RenderText_Solid(font2, " LEVEL 3 ", textColorlvl);
	else if (App->lvl4 == true)
		message4 = TTF_RenderText_Solid(font2, " LEVEL 4 ", textColorlvl);
	else if (App->lvl5 == true)
		message4 = TTF_RenderText_Solid(font2, " LEVEL 5 ", textColorlvl);
	//apply_surface(0, 0, message, App->window->screen_surface),0,0;
	
	return UPDATE_CONTINUE;
}

update_status ModuleSideMenu::PostUpdate()
{
	
	number=SDL_CreateTextureFromSurface(App->renderer->renderer,
		message);
	number2 = SDL_CreateTextureFromSurface(App->renderer->renderer,
		message2);

	pj = SDL_CreateTextureFromSurface(App->renderer->renderer,
		message3);
	lvl = SDL_CreateTextureFromSurface(App->renderer->renderer,
		message4);

	App->renderer->Blit(number, 360, 70, NULL, 0.0f);
	App->renderer->Blit(number2, 290, 70, NULL, 0.0f);
	App->renderer->Blit(pj, 310, 40, NULL, 0.0f);
	App->renderer->Blit(lvl, 310, 25, NULL, 0.0f);

	

	return UPDATE_CONTINUE;
}