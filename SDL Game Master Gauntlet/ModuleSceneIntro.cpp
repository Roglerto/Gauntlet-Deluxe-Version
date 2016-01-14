#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleLevel1.h"
#include "ModuleSceneIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{

	title.frames.push_back({ 0, 0, 384, 74 });
	title.frames.push_back({ 2, 97, 384, 74 });
	title.frames.push_back({ 2, 191, 384, 74 });
	title.frames.push_back({ 4, 286, 384, 74 });
	title.frames.push_back({ 5, 394, 384, 74 });
	title.frames.push_back({ 7, 495, 384, 74 });
	title.speed = 0.01f;

	background.x=441;
	background.y=17;
	background.w=384;
	background.h=256;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	graphics = App->textures->Load("Gauntlet/intros.png");
	App->audio->PlayMusic("intro.ogg", 0.0f);
	fx = App->audio->LoadFx("starting.wav");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, &(background));
	App->renderer->Blit(graphics, 0, 180, &(title.GetCurrentFrame()));

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		
		App->audio->PlayFx(fx);
		
			App->fade->FadeToBlack(App->scene_lvl1, this, 1.0f);

		
	}

	return UPDATE_CONTINUE;
}