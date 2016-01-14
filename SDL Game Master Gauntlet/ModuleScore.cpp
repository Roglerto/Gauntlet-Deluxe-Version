
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModulePlayer.h"
#include <fstream>
#include "ModuleSceneSpace.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel2.h"
#include "ModuleLevel4.h"
#include "ModuleLevel3.h"
#include "ModuleLevel5.h"
#include "ModuleScore.h"


ModuleScore::ModuleScore(bool start_enabled) : Module(start_enabled)
{
	textColorscore = { 255, 255, 0 };
	textColortxt = { 150, 55, 200 };
	textColornumber = { 205, 25, 100 };

	gauntlet.frames.push_back({ 59, 38, 101, 29 });
	gauntlet.frames.push_back({ 57, 109, 102, 29 });
	gauntlet.frames.push_back({ 57, 74, 102, 29 });
	gauntlet.frames.push_back({ 59, 38, 101, 29 });
	gauntlet.frames.push_back({ 56, 146, 102, 29 });
	gauntlet.frames.push_back({ 59, 6, 102, 29 });
	gauntlet.speed = 0.01f;

	background.x = 447;
	background.y = 307;
	background.w = 383;
	background.h = 256;
}


ModuleScore::~ModuleScore()
{
	TTF_Quit();
}

bool ModuleScore::Init()
{
	if (TTF_Init() != 0){
		LOG("TTF_Init error");
		SDL_Quit();
		return 1;
	}
	return true;
}

bool ModuleScore::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	string size;
	graphics2 = App->textures->Load("Gauntlet/intros.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;
	App->audio->PlayMusic("intro.ogg", 0.0f);
	fx = App->audio->LoadFx("starting.wav");
	App->scene_level5->Disable();
	App->scene_level4->Disable();
	App->scene_level3->Disable();
	App->scene_level2->Disable();
	App->scene_space->Disable();
	App->player->Disable();
	App->playerscore = 0;
	
	
	font = TTF_OpenFont("Gauntlet/leters.ttf", 32);
	font2 = TTF_OpenFont("Gauntlet/leters.ttf", 22);

	myfilemap.open("Gauntlet/score.txt", std::fstream::in);

	while (getline(myfilemap, size)){

		int num = atoi(size.c_str());
		scores.push_back(num);
	}
	myfilemap.close();
	return ret;
}

bool ModuleScore::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics2);

	TTF_CloseFont(font);
	TTF_CloseFont(font2);


	return true;
}

update_status ModuleScore::Update()
{
	
	// Draw everything --------------------------------------	
	
	//App->renderer->Blit(graphics2, 100, 200, &(gauntlet.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics2, 0, 0, &(background));

	message = TTF_RenderText_Solid(font, " SCORES ", textColorscore);
	message2 = TTF_RenderText_Solid(font2, itoa(scores[0], buffer, 10), textColornumber);
	message3 = TTF_RenderText_Solid(font2, itoa(scores[1], buffer, 10), textColornumber);
	message4 = TTF_RenderText_Solid(font2, itoa(scores[2], buffer, 10), textColornumber);

	position1 = TTF_RenderText_Solid(font2, " BEST POSITION ->", textColortxt);
	position2 = TTF_RenderText_Solid(font2, " SECOND POSITION -> ", textColortxt);
	position3 = TTF_RenderText_Solid(font2, " THIRD POSITION -> ", textColortxt);

	number1 = SDL_CreateTextureFromSurface(App->renderer->renderer,
		message2);
	number2 = SDL_CreateTextureFromSurface(App->renderer->renderer,
		message3);
	number3 = SDL_CreateTextureFromSurface(App->renderer->renderer,
		message4);
	score = SDL_CreateTextureFromSurface(App->renderer->renderer,
		message);

	p1 = SDL_CreateTextureFromSurface(App->renderer->renderer,
		position1);
	p2 = SDL_CreateTextureFromSurface(App->renderer->renderer,
		position2);
	p3 = SDL_CreateTextureFromSurface(App->renderer->renderer,
		position3);

	

	App->renderer->Blit(score, 120, 20, NULL, 0.0f);

	App->renderer->Blit(p1, 70, 70, NULL, 0.0f);
	App->renderer->Blit(p2, 70, 100, NULL, 0.0f);
	App->renderer->Blit(p3, 70, 130, NULL, 0.0f);

	App->renderer->Blit(number1, 240, 70, NULL, 0.0f);
	App->renderer->Blit(number2, 240, 100, NULL, 0.0f);
	App->renderer->Blit(number3, 240, 130, NULL, 0.0f);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(App->scene_intro, this, 1.0f);
	}

	
	//apply_surface(0, 0, message, App->window->screen_surface),0,0;

	return UPDATE_CONTINUE;
}







