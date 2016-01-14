#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleSceneSpace.h"
#include "ModuleSideMenu.h"
#include "ModuleEnemy.h"
#include "ModuleEnemyGenerator.h"
#include "ModuleItems.h"
#include <sstream>
#include <iomanip>
#include "ModuleSceneIntro.h"
#include "ModuleGoLevel3.h"
#include "ModuleLevel2.h"
#include "ModuleLevel3.h"
ModuleLevel3::ModuleLevel3(bool start_enabled) : Module(start_enabled)
{
	background = NULL;
	stars = NULL;

	sideswall.x = 748;
	sideswall.y = 130;
	sideswall.w = 16;
	sideswall.h = 16;



	downwall.x = 730;
	downwall.y = 130;
	downwall.w = 16;
	downwall.h = 16;



	floor.x = 250;
	floor.y = 274;
	floor.w = 16;
	floor.h = 16;

	door.x = 316;
	door.y = 202;
	door.w = 16;
	door.h = 16;


	uprightcorner.x = 28;
	uprightcorner.y = 148;
	uprightcorner.w = 16;
	uprightcorner.h = 16;

	botrightcorner.x = 766;
	botrightcorner.y = 130;
	botrightcorner.w = 16;
	botrightcorner.h = 16;

	upleftcorner.x = 136;
	upleftcorner.y = 148;
	upleftcorner.w = 16;
	upleftcorner.h = 16;

	botleftcorner.x = 82;
	botleftcorner.y = 148;
	botleftcorner.w = 16;
	botleftcorner.h = 16;

	posmapelement.x = 0;
	posmapelement.y = 0;

	explosion.anim.frames.push_back({ 100, 112, 16, 16 });
	explosion.anim.frames.push_back({ 118, 112, 16, 16 });
	explosion.anim.frames.push_back({ 136, 112, 16, 16 });
	explosion.anim.frames.push_back({ 154, 112, 16, 16 });
	explosion.anim.frames.push_back({ 172, 112, 16, 16 });
	explosion.anim.frames.push_back({ 190, 112, 16, 16 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	// explosionani.frames.push_back({ 100, 112, 16, 16 });
	explosionani.frames.push_back({ 118, 112, 16, 16 });
	explosionani.frames.push_back({ 136, 112, 16, 16 });
	explosionani.frames.push_back({ 154, 112, 16, 16 });
	explosionani.frames.push_back({ 172, 112, 16, 16 });
	explosionani.frames.push_back({ 190, 112, 16, 16 });
	explosionani.loop = true;
	explosionani.speed = 0.3f;
}

ModuleLevel3::~ModuleLevel3()
{}

bool ModuleLevel3::readmap(){
	string size;
	string number;
	int i = 0;
	stringstream ss;
	string s;
	ostringstream convert;


	myfilemap.open("Gauntlet/lvl3.txt", std::fstream::in);





	getline(myfilemap, size);
	COL = atoi(size.c_str());

	App->player->camlimitx = ((COL * 16) - 117) / 2;

	getline(myfilemap, size);
	FIL = atoi(size.c_str());

	App->player->camlimity = (FIL * 16) / 2;

	typedef std::istreambuf_iterator<char> buf_iter;
	for (buf_iter i(myfilemap), e; i != e; ++i){
		char c = *i;
		map.push_back(c);
	}
	//checking the file was read correctly
	myfilemap.close();


	return true;
}
// Load assets
bool ModuleLevel3::Start()
{
	LOG("Loading space scene");

	background = App->textures->Load("Gauntlet/g.png");

	addcolider = true;
	App->scene_intro->Disable();
	App->scene_level3go->Disable();
	App->scene_level2->Disable();
	App->collision->Enable(); // enable before player
	App->player->Enable();
	App->scene_menu->Enable();
	App->scene_ghost_generator->Enable();
	App->scene_ghost->Enable();
	App->scene_items->Enable();


	App->audio->PlayMusic("stage1.ogg", 1.0f);
	SDL_Texture* particles = App->textures->Load("Gauntlet/g.png");
	explosion.graphics = particles;

	//App->renderer->camera.x = App->renderer->camera.y = 0;

	//App->collision->AddCollider({0, 224, 3000, 16}, COLLIDER_WALL);

	//App->collision->AddCollider({1376, 0, 112, 95}, COLLIDER_WALL);
	//App->collision->AddCollider({1376, 144, 112, 95}, COLLIDER_WALL);

	map.clear();
	readmap();

	return true;
}

// UnLoad assets
bool ModuleLevel3::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();

	map.clear();

	return true;
}

update_status ModuleLevel3::PreUpdate(){



	return UPDATE_CONTINUE;
}


// Update: draw background
update_status ModuleLevel3::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;


	//App->player->position.x += 1;
	//App->renderer->camera.x -= 3;

	// Draw everything --------------------------------------	
	for (int x = 0; x < map.size(); x++){

		if (posx > 28){
			posmapelement.y = posmapelement.y + 16;
			posmapelement.x = 0;
			posx = 0;
		}

		if (map[x] == '1'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(uprightcorner));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_WALL, this);
			posmapelement.x = posmapelement.x + 16;

		}
		else if (map[x] == '9'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(sideswall));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_WALL, this);
			posmapelement.x = posmapelement.x + 16;
		}
		else if (map[x] == '8'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(upleftcorner));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_WALL, this);
			posmapelement.x = posmapelement.x + 16;

		}
		else if (map[x] == '7'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(downwall));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_WALL, this);
			posmapelement.x = posmapelement.x + 16;
		}
		else if (map[x] == '5'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(botrightcorner));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_WALL, this);
			posmapelement.x = posmapelement.x + 16;
		}
		else if (map[x] == '6'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(botleftcorner));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_WALL, this);
			posmapelement.x = posmapelement.x + 16;
		}
		else if (map[x] == '-'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(sideswall));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_CORNER, this);
			posmapelement.x = posmapelement.x + 16;
		}
		else if (map[x] == 'u'){
			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(downwall));
			if (addcolider)
				App->collision->AddCollider({ posmapelement.x, posmapelement.y, 16, 16 }, COLLIDER_CORNER, this);
			posmapelement.x = posmapelement.x + 16;
		}
		else if (map[x] == ('\n')){
		}
		else  {
			if (map[x] == 'g') {
				map[x] = 0;
				App->scene_ghost->AddGhost(posmapelement.x, posmapelement.y);
				//posmapelement.x = posmapelement.x + 16;
			}
			else if (map[x] == 'p') {
				map[x] = 0;
				App->player->position.x = posmapelement.x;
				App->player->position.y = posmapelement.y;
				//posmapelement.x = posmapelement.x + 16;
			}
			else if (map[x] == '@'){

				map[x] = 0;
				App->scene_ghost_generator->AddGenerator(posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 't'){

				map[x] = 0;
				App->scene_items->additems(TREASURE, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'f'){

				map[x] = 0;
				App->scene_items->additems(FOOD, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'k'){

				map[x] = 0;
				App->scene_items->additems(KEY, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'c'){

				map[x] = 0;
				App->scene_items->additems(POTION1, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'w'){

				map[x] = 0;
				App->scene_items->additems(DOOR, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'q'){

				map[x] = 0;
				App->scene_items->additems(DOOR2, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'j'){

				map[x] = 0;
				App->scene_items->additems(POTION2, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'l'){

				map[x] = 0;
				App->scene_items->additems(POTION3, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'x'){

				map[x] = 0;
				App->scene_items->additems(DESTRUCTIBLE_DOOR, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'b'){

				map[x] = 0;
				App->scene_items->additems(EXIT, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'y'){

				map[x] = 0;
				App->scene_items->additems(EXIT3, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'v'){

				map[x] = 0;
				App->scene_items->additems(EXIT4, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'n'){

				map[x] = 0;
				App->scene_items->additems(EXIT5, posmapelement.x, posmapelement.y);
			}
			else if (map[x] == 'i'){

				map[x] = 0;
				App->scene_items->additems(KEY2, posmapelement.x, posmapelement.y);
			}

			App->renderer->Blit(background, posmapelement.x, posmapelement.y, &(floor));
			posmapelement.x = posmapelement.x + 16;
		}


		posx++;
	}



	posmapelement.x = 0;
	posmapelement.y = 0;
	posx = 0;
	addcolider = false;
	//App->renderer->Blit(background, 0, 0, NULL);



	return UPDATE_CONTINUE;
}

update_status ModuleLevel3::PostUpdate(){

	if (explo == true){
		App->renderer->Blit(background, posexplosion.x, posexplosion.y, &(explosionani.GetCurrentFrame()));
	}
	if (timeexplosion.Read()>400){
		explo = false;
		timeexplosion.Stop();
	}
	return UPDATE_CONTINUE;

}

void ModuleLevel3::OnCollision(Collider* c1, Collider* c2)
{

	if ((c1->type == COLLIDER_PLAYER_SHOT) && (c2->type != COLLIDER_CORNER))
	{
		explo = true;
		posexplosion.x = c1->rect.x;
		posexplosion.y = c1->rect.y;
		//App->particles->AddParticle(explosion, c1->rect.x, c1->rect.y, COLLIDER_NONE, "w");
		//App->renderer->Blit(background, c1->rect.x, c1->rect.y, &(explosionani.GetCurrentFrame()));
	}
	else if ((c2->type == COLLIDER_PLAYER_SHOT) && (c1->type != COLLIDER_CORNER)){
		explo = true;
		timeexplosion.Start();
		posexplosion.x = c2->rect.x;
		posexplosion.y = c2->rect.y;
		//App->particles->AddParticle(explosion, c2->rect.x, c2->rect.y, COLLIDER_NONE, "w");
		//App->renderer->Blit(background, c2->rect.x, c2->rect.y, &(explosionani.GetCurrentFrame()));
	}

}