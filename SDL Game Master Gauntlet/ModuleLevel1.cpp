#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"

#include "ModuleLevel1.h"


ModuleLevel1::ModuleLevel1(bool start_enabled) : Module(start_enabled)
{
	background.x = 838;
	background.y = 15;
	background.w = 384;
	background.h = 256;
}


ModuleLevel1::~ModuleLevel1()
{
}
bool ModuleLevel1::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	start = true;
	graphics = App->textures->Load("Gauntlet/intros.png");
	App->audio->PlayMusic("intro.ogg", 1.0f);
	time.Start();
	
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleLevel1::PreUpdate()
{
	
	
	if (start == true){
		
		start = false;
		
	}
	
	return UPDATE_CONTINUE;
}
update_status ModuleLevel1::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, &(background));
		

	return UPDATE_CONTINUE;
}

update_status ModuleLevel1::PostUpdate()
{


	if (time.Read()>5000)
	{
		time.Stop();
		
		App->fade->FadeToBlack(App->scene_space, this, 0.0f);
	}

	return UPDATE_CONTINUE;
}