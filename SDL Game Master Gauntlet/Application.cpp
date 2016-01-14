#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneSpace.h"
#include "ModulePlayer.h"
#include "ModuleSideMenu.h"
#include "ModuleEnemy.h"
#include "ModuleEnemyGenerator.h"
#include "ModuleItems.h"
#include "ModuleScore.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleGoLevel2.h"
#include "ModuleLevel3.h"
#include "ModuleGoLevel3.h"
#include "ModuleLevel4.h"
#include "ModuleGoLevel4.h"
#include "ModuleLevel5.h"
#include "ModuleGoLevel5.h"
using namespace std;

Application::Application()
{
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());

	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());
	modules.push_back(particles = new ModuleParticles());
	modules.push_back(collision = new ModuleCollision());
	modules.push_back(fade = new ModuleFadeToBlack());

	// Game Modules
	modules.push_back(scene_score = new ModuleScore(false));
	modules.push_back(scene_intro = new ModuleSceneIntro(false));
	modules.push_back(scene_lvl1 = new ModuleLevel1(false));
	
	modules.push_back(scene_space = new ModuleSceneSpace(false));
	modules.push_back(scene_level2 = new ModuleLevel2(false));
	modules.push_back(scene_level3 = new ModuleLevel3(false));
	modules.push_back(scene_level4 = new ModuleLevel4(false));
	modules.push_back(scene_level5 = new ModuleLevel5(false));
	modules.push_back(scene_level2go = new ModuleGoLevel2(false));
	modules.push_back(scene_level3go = new ModuleGoLevel3(false));
	modules.push_back(scene_level4go = new ModuleGoLevel4(false));
	modules.push_back(scene_level5go = new ModuleGoLevel5(false));
	modules.push_back(scene_ghost_generator = new ModuleEnemyGenerator(false));
	modules.push_back(scene_ghost = new ModuleEnemy(false)); // 
	modules.push_back(scene_items = new ModuleItems(false)); // 
	

	modules.push_back(player = new ModulePlayer(false)); // player needs to be after scene
	

	modules.push_back(scene_menu = new ModuleSideMenu(false));
	

	modules.push_back(renderer = new ModuleRender());

	// set first scene for the game
	first_scene = scene_intro;
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	// Start the first scene --
	if(first_scene != nullptr)
		fade->FadeToBlack(first_scene, nullptr, 3.0f);

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

