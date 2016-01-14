
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleLevel5.h"
#include "ModuleLevel4.h"
#include "ModuleGoLevel5.h"


ModuleGoLevel5::ModuleGoLevel5(bool start_enabled) : Module(start_enabled)
{
	background.x = 1256;
	background.y = 574;
	background.w = 384;
	background.h = 256;
}


ModuleGoLevel5::~ModuleGoLevel5()
{
}
bool ModuleGoLevel5::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	start = true;
	graphics = App->textures->Load("Gauntlet/intros.png");
	App->audio->PlayMusic("intro.ogg", 1.0f);
	time.Start();
	App->scene_level4->CleanUp();
	App->scene_level4->Disable();
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleGoLevel5::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleGoLevel5::PreUpdate()
{


	if (start == true){

		start = false;

	}

	return UPDATE_CONTINUE;
}
update_status ModuleGoLevel5::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, &(background));


	return UPDATE_CONTINUE;
}

update_status ModuleGoLevel5::PostUpdate()
{


	if (time.Read()>5000)
	{
		time.Stop();

		App->fade->FadeToBlack(App->scene_level5, this, 0.0f);
	}

	return UPDATE_CONTINUE;
}