
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"

#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleGoLevel2.h"

ModuleGoLevel2::ModuleGoLevel2(bool start_enabled) : Module(start_enabled)
{
	background.x = 1234;
	background.y = 15;
	background.w = 384;
	background.h = 256;
}


ModuleGoLevel2::~ModuleGoLevel2()
{
}
bool ModuleGoLevel2::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	start = true;
	graphics = App->textures->Load("Gauntlet/intros.png");
	App->audio->PlayMusic("intro.ogg", 1.0f);
	time.Start();
	App->scene_space->CleanUp();
	App->scene_space->Disable();
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleGoLevel2::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleGoLevel2::PreUpdate()
{


	if (start == true){

		start = false;

	}

	return UPDATE_CONTINUE;
}
update_status ModuleGoLevel2::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, &(background));


	return UPDATE_CONTINUE;
}

update_status ModuleGoLevel2::PostUpdate()
{


	if (time.Read()>5000)
	{
		time.Stop();

		App->fade->FadeToBlack(App->scene_level2, this, 0.0f);
	}

	return UPDATE_CONTINUE;
}