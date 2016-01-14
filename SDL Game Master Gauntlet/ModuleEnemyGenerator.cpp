#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleSideMenu.h"
#include "ModuleSceneSpace.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy.h"

#include "ModuleEnemyGenerator.h"


ModuleEnemyGenerator::ModuleEnemyGenerator(bool start_enabled) : Module(start_enabled)
{
	explosionani.frames.push_back({ 118, 112, 16, 16 });
	explosionani.frames.push_back({ 136, 112, 16, 16 });
	explosionani.frames.push_back({ 154, 112, 16, 16 });
	explosionani.frames.push_back({ 172, 112, 16, 16 });
	explosionani.frames.push_back({ 190, 112, 16, 16 });
	explosionani.loop = true;
	explosionani.speed = 0.3f;
}


ModuleEnemyGenerator::~ModuleEnemyGenerator()
{
}

bool ModuleEnemyGenerator::Start()
{
	LOG("Loading player");

	ghostimage = App->textures->Load("Gauntlet/g.png");
	
	return true;
}

update_status ModuleEnemyGenerator::PreUpdate(){

	for (list<ghostgenerator*>::iterator it = generatorlist.begin(); it != generatorlist.end(); ++it)
	{

		(*it)->generateEnemy = true;
		
		(*it)->colisionN = false;
		(*it)->colisionS = false;
		(*it)->colisionE = false;
		(*it)->colisionW = false;
		//(*it)->wall = false;
	}
	
	return UPDATE_CONTINUE;
}

update_status ModuleEnemyGenerator::Update(){

	
	for (list<ghostgenerator*>::iterator it = generatorlist.begin(); it != generatorlist.end(); ++it)
	{
		App->renderer->Blit(ghostimage, (*it)->position.x, (*it)->position.y, &((*it)->generator.GetCurrentFrame()));
	}
	
	return UPDATE_CONTINUE;
}

void ModuleEnemyGenerator::addenemy(int x, int y){
	
		
		App->scene_ghost->AddGhost(x, y);
		
	
}

update_status ModuleEnemyGenerator::PostUpdate(){
	
	
	for (list<ghostgenerator*>::iterator it = generatorlist.begin(); it != generatorlist.end(); ++it)
	{
		if (start==true){

			if (((*it)->colisionN == false)){
				if (borrarN == false){
					borrarN = true;
					generatingN.Start();
					addenemy((*it)->position.x, (*it)->position.y - 16);
				}
				else if (generatingN.Read() > 2000){
					borrarN = false;
				}

			}
			if (((*it)->colisionS == false)){
				if (borrarS == false){
					borrarS = true;
					generatingS.Start();
					addenemy((*it)->position.x, (*it)->position.y + 16);

				}
				else if (generatingS.Read() > 2000){
					borrarS = false;
				}
			}
			if (((*it)->colisionW == false)){
				if (borrarW == false){
					borrarW = true;
					generatingW.Start();
					addenemy((*it)->position.x - 16, (*it)->position.y);
				}
				else if (generatingW.Read() > 2000){
					borrarW = false;
				}
			}
			if (((*it)->colisionE == false)){
				if (borrarE == false){
					borrarE = true;
					generatingE.Start();
					addenemy((*it)->position.x + 16, (*it)->position.y);
				}
				else if (generatingE.Read() > 2000){
					borrarE = false;
				}
			}
		}
		else if ((*it)->timer.Read() > 500){
			start = true;
			(*it)->timer.Stop();
		}
	}

	if (explo == true){
		App->renderer->Blit(ghostimage, posexplosion.x, posexplosion.y, &(explosionani.GetCurrentFrame()));
	}
	if (timeexplosion.Read()>400){
		explo = false;
		timeexplosion.Stop();
	}
	
	
	return UPDATE_CONTINUE;
}

bool ModuleEnemyGenerator::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(ghostimage);

	 borrarN = false;
	 borrarS = false;
	 borrarE = false;
	 borrarW = false;
	 start = false;

	for (list<ghostgenerator*>::iterator it = generatorlist.begin(); it != generatorlist.end(); ++it)
	{
		(*it)->collider->to_delete = true;

		(*it)->colliderN->to_delete = true;
		(*it)->colliderS->to_delete = true;
		(*it)->colliderW->to_delete = true;
		(*it)->colliderE->to_delete = true;
		RELEASE(*it);

	}generatorlist.clear();

	return true;
}

void ModuleEnemyGenerator::AddGenerator(int x, int y){

	ghostgenerator* gr = new ghostgenerator();
	gr->position.x = x;
	gr->position.y = y;

	gr->timer.Start();
	gr->graphicsgenerator = ghostimage;
	gr->collider = App->collision->AddCollider({ gr->position.x, gr->position.y, 16, 16 }, COLLIDER_ENEMY_GENERATOR, this);

	gr->colliderN = App->collision->AddCollider({ gr->position.x, gr->position.y - 16, 16, 16 }, COLLIDER_ENEMY_GENERATOR_N, this);
	gr->colliderS = App->collision->AddCollider({ gr->position.x, gr->position.y + 16, 16, 16 }, COLLIDER_ENEMY_GENERATOR_S, this);
	gr->colliderE = App->collision->AddCollider({ gr->position.x + 16, gr->position.y, 16, 16 }, COLLIDER_ENEMY_GENERATOR_E, this);
	gr->colliderW = App->collision->AddCollider({ gr->position.x - 16, gr->position.y, 16, 16 }, COLLIDER_ENEMY_GENERATOR_W, this);

	generatorlist.push_back(gr);
}

void ModuleEnemyGenerator::OnCollision(Collider* c1, Collider* c2){
	for (list<ghostgenerator*>::iterator it = generatorlist.begin(); it != generatorlist.end(); ++it)
	{

		if ((*it)->collider == c1)
		{
			if ((c2->type == COLLIDER_PLAYER_SHOT)){
				if (life > 0){
					explo = true;
					timeexplosion.Start();
					posexplosion.x = c1->rect.x;
					posexplosion.y = c1->rect.y;
					life = life - 1;
				}
				else{
					explo = true;
					timeexplosion.Start();
					posexplosion.x = c1->rect.x;
					posexplosion.y = c1->rect.y;

					(*it)->collider->to_delete = true;
					(*it)->colliderN->to_delete = true;
					(*it)->colliderS->to_delete = true;
					(*it)->colliderW->to_delete = true;
					(*it)->colliderE->to_delete = true;
					RELEASE(*it);
					it = generatorlist.erase(it);
					break;
				}

			}
		}
		if (((*it)->colliderW == c1) && ((c2->type == COLLIDER_ENEMY) || ((c2->type == COLLIDER_WALL))))
		{
			(*it)->colisionW = true;

		}

		if (((*it)->colliderN == c1) && ((c2->type == COLLIDER_ENEMY) || ((c2->type == COLLIDER_WALL))))
		{
			(*it)->colisionN = true;

		}
		if (((*it)->colliderS == c1) && ((c2->type == COLLIDER_ENEMY) || ((c2->type == COLLIDER_WALL))))
		{
			(*it)->colisionS = true;
		}
		if (((*it)->colliderE == c1) && ((c2->type == COLLIDER_ENEMY) || ((c2->type == COLLIDER_WALL))))
		{
			(*it)->colisionE = true;
		}
		

		
		
	}
}

//-------------------------------------------------

ghostgenerator::ghostgenerator(){
	generator.frames.push_back({ 154, 130, 16, 16 });
	generator.frames.push_back({ 172, 130, 16, 16 });
	generator.frames.push_back({ 190, 130, 16, 16 });

	generator.speed = 0.1f;
}

ghostgenerator::~ghostgenerator(){

}