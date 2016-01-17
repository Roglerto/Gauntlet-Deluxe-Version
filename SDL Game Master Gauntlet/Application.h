#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleParticles;
class ModuleCollision;
class ModuleSceneIntro;
class ModuleSceneSpace;
class ModuleSideMenu;
class ModuleEnemy;
class ModuleEnemyGenerator;
class ModuleItems;
class ModuleScore;
class ModuleLevel1;
class ModuleLevel2;
class ModuleGoLevel2;
class ModuleLevel3;
class ModuleGoLevel3;
class ModuleLevel4;
class ModuleGoLevel4;
class ModuleLevel5;
class ModuleGoLevel5;
class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	int playerscore = 0;
	bool potion1 = false;
	bool potion2 = false;
	bool potion3 = false;
	bool pause = false;
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleCollision* collision;

	// Game logic --
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModuleSceneSpace* scene_space;

	ModuleSideMenu* scene_menu;
	ModuleEnemy* scene_ghost;
	ModuleEnemyGenerator* scene_ghost_generator;
	ModuleItems* scene_items;
	ModuleScore* scene_score;
	ModuleLevel1* scene_lvl1;

	ModuleLevel2* scene_level2;
	ModuleGoLevel2* scene_level2go;

	ModuleLevel3* scene_level3;
	ModuleGoLevel3* scene_level3go;

	ModuleLevel4* scene_level4;
	ModuleGoLevel4* scene_level4go;

	ModuleLevel5* scene_level5;
	ModuleGoLevel5* scene_level5go;

	bool lvl1 = true;
	bool lvl2 = false;
	bool lvl3 = false;
	bool lvl4 = false;
	bool lvl5 = false;

private:

	std::list<Module*> modules;
	Module* first_scene = nullptr;
};

extern Application* App;

#endif // __APPLICATION_CPP__