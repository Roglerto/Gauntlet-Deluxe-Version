#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleSideMenu.h"
#include "ModuleSceneSpace.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy.h"
#include "ModuleEnemyGenerator.h"

#include "ModuleAudio.h"
#include "ModuleItems.h"


ModuleItems::ModuleItems(bool start_enabled) : Module(start_enabled)
{
	explosionani.frames.push_back({ 118, 112, 16, 16 });
	explosionani.frames.push_back({ 136, 112, 16, 16 });
	explosionani.frames.push_back({ 154, 112, 16, 16 });
	explosionani.frames.push_back({ 172, 112, 16, 16 });
	explosionani.frames.push_back({ 190, 112, 16, 16 });
	explosionani.loop = true;
	explosionani.speed = 0.3f;

	explosionkey.frames.push_back({ 208, 112, 16, 16 });
	explosionkey.frames.push_back({ 226, 112, 16, 16 });
	explosionkey.frames.push_back({ 244, 112, 16, 16 });
	explosionkey.frames.push_back({ 262, 112, 16, 16 });
	
	explosionkey.loop = true;
	explosionkey.speed = 0.3f;
}


ModuleItems::~ModuleItems()
{
}

bool ModuleItems::Start()
{
	LOG("Loading player");

	image = App->textures->Load("Gauntlet/g.png");
	fx = App->audio->LoadFx("bip.wav");

	return true;
}

bool ModuleItems::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(image);

	for (list<items*>::iterator it = itemlist.begin(); it != itemlist.end(); ++it)
	{
		(*it)->collider->to_delete = true;
		RELEASE(*it);

	}itemlist.clear();



	return true;
}

void ModuleItems::deletedoors(){

	for (list<items*>::iterator itt = itemlist.begin(); itt != itemlist.end(); )
	{
		items* d = *itt;
		if ((*itt)->type == DOOR){		
							
			door.push_back((*itt)->position);

			(*itt)->collider->to_delete = true;
			RELEASE(d);
			itt = itemlist.erase(itt);
							
		}
		else itt++;
	
		
		
	}
	explodoor = true;
}
void ModuleItems::deletedoors2(){

	for (list<items*>::iterator itt = itemlist.begin(); itt != itemlist.end();)
	{
		items* d = *itt;
		if ((*itt)->type == DOOR2){

			door2.push_back((*itt)->position);

			(*itt)->collider->to_delete = true;
			RELEASE(d);
			itt = itemlist.erase(itt);

		}
		else itt++;



	}
	explodoor2 = true;
}

void  ModuleItems::OnCollision(Collider* c1, Collider* c2){
	for (list<items*>::iterator it = itemlist.begin(); it != itemlist.end(); )
	{

		if ((c2->type == COLLIDER_PLAYER_SHOT)){
			if (((*it)->type == DESTRUCTIBLE_DOOR) && (c1->type == COLLIDER_DESTRUCTIBLE_DOOR) && (SDL_HasIntersection(&(*it)->collider->rect, &App->particles->destructible_door()))){


				explo = true;
				timeexplosion.Start();
				posexplosion.x = c1->rect.x;
				posexplosion.y = c1->rect.y;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else{
				explo = true;
				timeexplosion.Start();
				posexplosion.x = c2->rect.x;
				posexplosion.y = c2->rect.y;

			}

		}
		
		if ((c2->type == COLLIDER_PLAYER)){

			if (((*it)->type == TREASURE) && (c1->type == COLLIDER_TREASURE) && (SDL_HasIntersection(&(*it)->collider->rect,&App->player->collider->rect))){
				App->audio->PlayFx(fx);
				App->player->score += (*it)->score;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == FOOD) && (c1->type == COLLIDER_FOOD) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){
				App->player->life += (*it)->life;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == KEY) && (c1->type == COLLIDER_KEY) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){
				App->player->key = (*it)->key;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == KEY2) && (c1->type == COLLIDER_KEY2) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){
				App->player->key2 = (*it)->key2;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == POTION1) && (c1->type == COLLIDER_POTION) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){
				App->player->potion1 = (*it)->potion1;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == POTION2) && (c1->type == COLLIDER_POTION2) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){
				App->player->potion2 = (*it)->potion2;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == POTION3) && (c1->type == COLLIDER_POTION3) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){
				App->player->potion3 = (*it)->potion3;
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == EXIT) && (c1->type == COLLIDER_EXIT) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){
				
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == EXIT3) && (c1->type == COLLIDER_EXIT3) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){

				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == EXIT4) && (c1->type == COLLIDER_EXIT4) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){

				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == EXIT5) && (c1->type == COLLIDER_EXIT5) && (SDL_HasIntersection(&(*it)->collider->rect, &App->player->collider->rect))){

				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = itemlist.erase(it);
				break;
			}
			else if (((*it)->type == DOOR) && (c1->type == COLLIDER_DOOR)){
				if ((App->player->key == true)){
					
						if ((*it)->type == DOOR){
							timedor.Start();
							deletedoors();
							App->player->key = false;
							break;
						}
					
				}
			}
			
			else if (((*it)->type == DOOR2) && (c1->type == COLLIDER_DOOR2)){
				if ( (App->player->key2 == true)){

					if ((*it)->type == DOOR2){
						timedor.Start();
						deletedoors2();
						App->player->key2 = false;
						break;
					}

				}
			}

		}
		++it;
	}
	
}

update_status ModuleItems::Update(){
	for (list<items*>::iterator it = itemlist.begin(); it != itemlist.end(); ++it)
	{
		App->renderer->Blit(image, (*it)->position.x, (*it)->position.y, &((*it)->animation.GetCurrentFrame()));
	}

	if (explo == true){
		App->renderer->Blit(image, posexplosion.x, posexplosion.y, &(explosionani.GetCurrentFrame()));
	}
	if (timeexplosion.Read()>400){
		explo = false;
		timeexplosion.Stop();
	}

	if (explodoor == true){
		for (int i = 0; i < door.size();i++)
			App->renderer->Blit(image, door[i].x, door[i].y, &(explosionkey.GetCurrentFrame()));
	}
	if (timedor.Read()>400){
		explodoor = false;
		timedor.Stop();
	}
	if (explodoor2 == true){
		for (int i = 0; i < door2.size(); i++)
			App->renderer->Blit(image, door2[i].x, door2[i].y, &(explosionkey.GetCurrentFrame()));
	}
	if (timedor.Read()>400){
		explodoor2 = false;
		timedor.Stop();
	}

	return UPDATE_CONTINUE;
}

void ModuleItems::additems(item_type type, int x, int y){

	if (type == TREASURE){
		Treasure* t = new Treasure();
		t->position.x = x;
		t->position.y = y;
		t->type = type;

		t->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_TREASURE, this);
		itemlist.push_back(t);
	}
	else if (type == FOOD){
		Food* f = new Food();
		f->position.x = x;
		f->position.y = y;
		f->type = type;
		f->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_FOOD, this);
		itemlist.push_back(f);
	}
	else if(type == KEY){
		Key* k = new Key();
		k->position.x = x;
		k->position.y = y;
		k->type = type;
		k->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_KEY, this);
		itemlist.push_back(k);
	}
	else if (type == KEY2){
		Key2* k2 = new Key2();
		k2->position.x = x;
		k2->position.y = y;
		k2->type = type;
		k2->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_KEY2, this);
		itemlist.push_back(k2);
	}
	else if(type == POTION1){
		Potion1* p = new Potion1();
		p->position.x = x;
		p->position.y = y;
		p->type = type;
		p->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_POTION, this);
		itemlist.push_back(p);
	}
	else if (type == POTION2){
		Potion2* p2 = new Potion2();
		p2->position.x = x;
		p2->position.y = y;
		p2->type = type;
		p2->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_POTION2, this);
		itemlist.push_back(p2);
	}
	else if (type == POTION3){
		Potion3* p3 = new Potion3();
		p3->position.x = x;
		p3->position.y = y;
		p3->type = type;
		p3->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_POTION3, this);
		itemlist.push_back(p3);
	}
	else if (type == DOOR){
		Door* d = new Door();
		d->position.x = x;
		d->position.y = y;
		d->type = type;
		d->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_DOOR, this);
		itemlist.push_back(d);
	}
	else if (type == EXIT){
		Exit* e = new Exit();
		e->position.x = x;
		e->position.y = y;
		e->type = type;
		e->collider = App->collision->AddCollider({ x, y, 8, 8 }, COLLIDER_EXIT, this);
		itemlist.push_back(e);
	}
	else if (type == EXIT3){
		Exit3* e3 = new Exit3();
		e3->position.x = x;
		e3->position.y = y;
		e3->type = type;
		e3->collider = App->collision->AddCollider({ x, y, 8, 8 }, COLLIDER_EXIT3, this);
		itemlist.push_back(e3);
	}
	else if (type == EXIT4){
		Exit4* e4 = new Exit4();
		e4->position.x = x;
		e4->position.y = y;
		e4->type = type;
		e4->collider = App->collision->AddCollider({ x, y, 8, 8 }, COLLIDER_EXIT4, this);
		itemlist.push_back(e4);
	}
	else if (type == EXIT5){
		Exit5* e5 = new Exit5();
		e5->position.x = x;
		e5->position.y = y;
		e5->type = type;
		e5->collider = App->collision->AddCollider({ x, y, 8, 8 }, COLLIDER_EXIT5, this);
		itemlist.push_back(e5);
	}
	else if (type == EXIT6){
		Exit6* e6 = new Exit6();
		e6->position.x = x;
		e6->position.y = y;
		e6->type = type;
		e6->collider = App->collision->AddCollider({ x, y, 8, 8 }, COLLIDER_EXIT6, this);
		itemlist.push_back(e6);
	}
	else if (type == DOOR2){
		Door2* d2 = new Door2();
		d2->position.x = x;
		d2->position.y = y;
		d2->type = type;
		d2->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_DOOR2, this);
		itemlist.push_back(d2);
	}
	else if (type == DESTRUCTIBLE_DOOR){
		Destructible_Door* ds = new Destructible_Door();
		ds->position.x = x;
		ds->position.y = y;
		ds->type = type;
		ds->collider = App->collision->AddCollider({ x, y, 16, 16 }, COLLIDER_DESTRUCTIBLE_DOOR, this);
		itemlist.push_back(ds);
	}
	

}

//----------------------------------------
Treasure::Treasure(){
	animation.frames.push_back({ 388, 130, 16, 16 });
	animation.frames.push_back({ 406, 130, 16, 16 });
	animation.frames.push_back({ 424, 130, 16, 16 });
	animation.loop = true;
	animation.speed = 0.2f;

	 score = 10;

	
}
Treasure::~Treasure(){

}

Exit::Exit(){
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 556, 292, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.loop = true;
	animation.speed = 0.2f;
}
Exit::~Exit(){

}
Exit3::Exit3(){
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 556, 292, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.loop = true;
	animation.speed = 0.2f;
}
Exit3::~Exit3(){

}
Exit4::Exit4(){
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 556, 292, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.loop = true;
	animation.speed = 0.2f;
}
Exit4::~Exit4(){

}
Exit5::Exit5(){
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 556, 292, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.loop = true;
	animation.speed = 0.2f;
}
Exit5::~Exit5(){

}
Exit6::Exit6(){
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 556, 292, 16, 16 });
	animation.frames.push_back({ 640, 238, 16, 16 });
	animation.frames.push_back({ 622, 238, 16, 16 });
	animation.frames.push_back({ 604, 238, 16, 16 });
	animation.frames.push_back({ 586, 238, 16, 16 });
	animation.loop = true;
	animation.speed = 0.2f;
}
Exit6::~Exit6(){

}
Food::Food(){
	animation.frames.push_back({ 298, 130, 16, 16 });
	
	animation.loop = true;
	animation.speed = 0.2f;

	life = 10;
}

Food::~Food(){

}

Key::Key(){
	animation.frames.push_back({ 352, 130, 16, 16 });

	animation.loop = true;
	animation.speed = 0.2f;
	key = true;
	
}

Key::~Key(){

}
Key2::Key2(){
	animation.frames.push_back({ 352, 130, 16, 16 });

	animation.loop = true;
	animation.speed = 0.2f;
	key2 = true;

}

Key2::~Key2(){

}
Door::Door(){
	animation.frames.push_back({ 316, 202, 16, 16 });

	animation.loop = true;
	animation.speed = 0.2f;
	

}

Door::~Door(){

}

Door2::Door2(){
	animation.frames.push_back({ 316, 202, 16, 16 });

	animation.loop = true;
	animation.speed = 0.2f;


}

Door2::~Door2(){

}
Destructible_Door::Destructible_Door(){
	animation.frames.push_back({ 226, 130, 16, 16 });
	animation.frames.push_back({ 244, 148, 16, 16 });
	animation.frames.push_back({ 262, 148, 16, 16 });
	animation.loop = true;
	animation.speed = 0.2f;


}

Destructible_Door::~Destructible_Door(){

}

Potion1::Potion1(){
	animation.frames.push_back({ 262, 130, 16, 16 });

	animation.loop = true;
	animation.speed = 0.2f;

	
	 potion1 = true;
}
Potion1::~Potion1(){

}

Potion2::Potion2(){
	animation.frames.push_back({ 496, 130, 16, 16 });

	animation.loop = true;
	animation.speed = 0.2f;


	potion2 = true;
}
Potion2::~Potion2(){

}
Potion3::Potion3(){
	animation.frames.push_back({ 478, 130, 16, 16 });

	animation.loop = true;
	animation.speed = 0.2f;


	potion3 = true;
}
Potion3::~Potion3(){

}

items::items(){
	 score = 0;
	 life = 0;
	 key2 = false;
	 key = false;
	 potion1 = false;
	 potion2 = false;
	 potion3 = false;
}

items::~items(){

}