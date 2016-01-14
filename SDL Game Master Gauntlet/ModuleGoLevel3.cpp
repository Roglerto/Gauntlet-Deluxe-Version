
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleLevel3.h"
#include "ModuleLevel2.h"
#include "ModuleGoLevel3.h"


ModuleGoLevel3::ModuleGoLevel3(bool start_enabled) : Module(start_enabled)
{
	background.x = 846;
	background.y = 307;
	background.w = 384;
	background.h = 256;
}


ModuleGoLevel3::~ModuleGoLevel3()
{
}
bool ModuleGoLevel3::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	start = true;
	graphics = App->textures->Load("Gauntlet/intros.png");
	App->audio->PlayMusic("intro.ogg", 1.0f);
	time.Start();
	App->scene_level2->CleanUp();
	App->scene_level2->Disable();
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleGoLevel3::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleGoLevel3::PreUpdate()
{


	if (start == true){

		start = false;

	}

	return UPDATE_CONTINUE;
}
update_status ModuleGoLevel3::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, &(background));


	return UPDATE_CONTINUE;
}

update_status ModuleGoLevel3::PostUpdate()
{


	if (time.Read()>5000)
	{
		time.Stop();

		App->fade->FadeToBlack(App->scene_level3, this, 0.0f);
	}

	return UPDATE_CONTINUE;
}