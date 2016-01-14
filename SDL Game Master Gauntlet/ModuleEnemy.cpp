
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleSideMenu.h"
#include "ModuleSceneSpace.h"
#include "ModuleFadeToBlack.h"

#include "ModuleEnemy.h"
#include <math.h> 

ModuleEnemy::ModuleEnemy(bool start_enabled) : Module(start_enabled)
{
	
	// explosionani.frames.push_back({ 100, 112, 16, 16 });
	explosionani.frames.push_back({ 118, 112, 16, 16 });
	explosionani.frames.push_back({ 136, 112, 16, 16 });
	explosionani.frames.push_back({ 154, 112, 16, 16 });
	explosionani.frames.push_back({ 172, 112, 16, 16 });
	explosionani.frames.push_back({ 190, 112, 16, 16 });
	explosionani.loop = true;
	explosionani.speed = 0.3f;

}


ModuleEnemy::~ModuleEnemy()
{
}

bool ModuleEnemy::Start()
{
	LOG("Loading player");

	ghostimage = App->textures->Load("Gauntlet/g.png");

	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(ghostimage);

	for (list<Ghost*>::iterator it = ghostlist.begin(); it != ghostlist.end(); ++it)
	{
		(*it)->collider->to_delete = true;
		RELEASE(*it);
		
	}ghostlist.clear();

	

	return true;
}

void ModuleEnemy::AddGhost(int x, int y){

	Ghost* g = new Ghost();
	g->position.x = x;
	g->position.y = y;
	g->oldposition.x = x;
	g->oldposition.y = y;
	//g->timer.Start();
	g->graphicsghost = ghostimage;
	g->collider = App->collision->AddCollider({ g->position.x, g->position.y, 0, 0 }, COLLIDER_ENEMY, this);
	ghostlist.push_back(g);
}



update_status ModuleEnemy::PreUpdate(){
	
	

	return UPDATE_CONTINUE;
}

update_status ModuleEnemy::Update(){
		
		for (list<Ghost*>::iterator it = ghostlist.begin(); it != ghostlist.end(); ++it)
		{
			if ((*it)->Update() == true){}
			App->renderer->Blit(ghostimage, (*it)->position.x, (*it)->position.y, &((*it)->actualanimation->GetCurrentFrame()));
		}
		
	return UPDATE_CONTINUE;
}

update_status ModuleEnemy::PostUpdate(){

	if (explo == true){
		App->renderer->Blit(ghostimage, posexplosion.x, posexplosion.y, &(explosionani.GetCurrentFrame()));
	}
	if (timeexplosion.Read()>400){
		explo = false;
		timeexplosion.Stop();
	}
	return UPDATE_CONTINUE;

}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	for (list<Ghost*>::iterator it = ghostlist.begin(); it != ghostlist.end(); ++it)
	{
		
		
		if (c2->type == COLLIDER_PLAYER_SHOT){
			if (((*it)->collider == c1))
			{
				explo = true;
				timeexplosion.Start();
				posexplosion.x = c1->rect.x;
				posexplosion.y = c1->rect.y;

				App->player->score += 2;

				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = ghostlist.erase(it);
				break;
			}
		}
		else if (c2->type == COLLIDER_PLAYER){
			if (((*it)->collider == c1))
			{
				(*it)->collider->to_delete = true;
				RELEASE(*it);
				it = ghostlist.erase(it);


				break;

				
			}
		}
		else if ((c2->type == COLLIDER_WALL) || (c2->type == COLLIDER_FOOD) || (c2->type == COLLIDER_TREASURE) || (c2->type == COLLIDER_KEY2) || (c2->type == COLLIDER_KEY) || (c2->type == COLLIDER_POTION) || (c2->type == COLLIDER_POTION2) || (c2->type == COLLIDER_POTION3) || (c2->type == COLLIDER_ENEMY_GENERATOR) || (c2->type == COLLIDER_CORNER) || (c2->type == COLLIDER_DOOR) || (c2->type == COLLIDER_DOOR2) || (c2->type == COLLIDER_DESTRUCTIBLE_DOOR)){
			if (((*it)->collider == c1))
			{
				if ((*it)->orientation == "N"){
					(*it)->colisionN = true;

					
					(*it)->colisionS = false;
					(*it)->colisionW = false;
					(*it)->colisionE = false;

					(*it)->colisionNE = false;
					(*it)->colisionNW = false;
					(*it)->colisionSE = false;
					(*it)->colisionSW = false;
				}
				if ((*it)->orientation == "S"){
					(*it)->colisionS = true;

					(*it)->colisionN = false;
					(*it)->colisionW = false;
					(*it)->colisionE = false;

					(*it)->colisionNE = false;
					(*it)->colisionNW = false;
					(*it)->colisionSE = false;
					(*it)->colisionSW = false;
				}
				if ((*it)->orientation == "W"){
					(*it)->colisionW = true;

					(*it)->colisionS = false;
					(*it)->colisionN = false;
					(*it)->colisionE = false;

					(*it)->colisionNE = false;
					(*it)->colisionNW = false;
					(*it)->colisionSE = false;
					(*it)->colisionSW = false;
				}
				if ((*it)->orientation == "E"){
					(*it)->colisionE = true;

					(*it)->colisionS = false;
					(*it)->colisionW = false;
					(*it)->colisionN = false;

					(*it)->colisionNE = false;
					(*it)->colisionNW = false;
					(*it)->colisionSE = false;
					(*it)->colisionSW = false;

				}
				if ((*it)->orientation == "NE"){
					(*it)->colisionNE = true;

					(*it)->colisionS = false;
					(*it)->colisionW = false;
					(*it)->colisionE = false;

					(*it)->colisionN = false;
					(*it)->colisionNW = false;
					(*it)->colisionSE = false;
					(*it)->colisionSW = false;
				}
				if ((*it)->orientation == "NW"){
					(*it)->colisionNW = true;

					(*it)->colisionS = false;
					(*it)->colisionW = false;
					(*it)->colisionE = false;

					(*it)->colisionNE = false;
					(*it)->colisionN = false;
					(*it)->colisionSE = false;
					(*it)->colisionSW = false;
				}
				if ((*it)->orientation == "SE"){
					(*it)->colisionSE = true;

					(*it)->colisionS = false;
					(*it)->colisionW = false;
					(*it)->colisionE = false;

					(*it)->colisionNE = false;
					(*it)->colisionNW = false;
					(*it)->colisionN = false;
					(*it)->colisionSW = false;
				}
				if ((*it)->orientation == "SW"){
					(*it)->colisionSW = true;

					(*it)->colisionS = false;
					(*it)->colisionW = false;
					(*it)->colisionE = false;

					(*it)->colisionNE = false;
					(*it)->colisionNW = false;
					(*it)->colisionSE = false;
					(*it)->colisionN = false;
				}


			}
		}
		else if (c2->type == COLLIDER_ENEMY){
			if (((*it)->collider == c1))
			{
				if ((*it)->orientationenemy == "N"){
					(*it)->colisionN = true;
	
				}
				if ((*it)->orientationenemy == "S"){
					(*it)->colisionS = true;

			
				}
				if ((*it)->orientationenemy == "W"){
					(*it)->colisionW = true;

					
				}
				if ((*it)->orientationenemy == "E"){
					(*it)->colisionE = true;



				}
				if ((*it)->orientationenemy == "NE"){
					(*it)->colisionNE = true;


				}
				if ((*it)->orientationenemy == "NW"){
					(*it)->colisionNW = true;

	
				}
				if ((*it)->orientationenemy == "SE"){
					(*it)->colisionSE = true;


				}
				if ((*it)->orientationenemy == "SW"){
					(*it)->colisionSW = true;

		
				
				}
			}

		}
	}
}

//-----------------------------------------
Ghost::Ghost(){

	//north
	animghostnorth.frames.push_back({ 82, 40, 16, 16 });
	animghostnorth.frames.push_back({ 226, 40, 16, 16 });
	animghostnorth.frames.push_back({ 370, 40, 16, 16 });
	
	animghostnorth.speed = 0.2f;

	anim1.frames.push_back({ 82, 40, 16, 16 });

	//south
	animghostsouth.frames.push_back({ 154, 40, 16, 16 });
	animghostsouth.frames.push_back({ 298, 40, 16, 16 });
	animghostsouth.frames.push_back({ 442, 40, 16, 16 });
	animghostsouth.loop = true;
	animghostsouth.speed = 0.2f;

	anim2.frames.push_back({ 154, 40, 16, 16 });

	//east
	animghosteast.frames.push_back({ 118, 40, 16, 16 });
	animghosteast.frames.push_back({ 262, 40, 16, 16 });
	animghosteast.frames.push_back({ 406, 40, 16, 16 });
	animghosteast.loop = true;
	animghosteast.speed = 0.2f;

	anim3.frames.push_back({ 118, 40, 16, 16 });

	//west
	animghostwest.frames.push_back({ 190, 40, 16, 16 });
	animghostwest.frames.push_back({ 334, 40, 16, 16 });
	animghostwest.frames.push_back({ 478, 40, 16, 16 });
	animghostwest.loop = true;
	animghostwest.speed = 0.2f;

	anim4.frames.push_back({ 190, 40, 16, 16 });

	//northeast
	animghostnortheast.frames.push_back({ 100, 40, 16, 16 });
	animghostnortheast.frames.push_back({ 244, 40, 16, 16 });
	animghostnortheast.frames.push_back({ 388, 40, 16, 16 });
	animghostnortheast.loop = true;
	animghostnortheast.speed = 0.2f;

	anim5.frames.push_back({ 100, 40, 16, 16 });

	//northwest
	animghostnorthwest.frames.push_back({ 208, 40, 16, 16 });
	animghostnorthwest.frames.push_back({ 352, 40, 16, 16 });
	animghostnorthwest.frames.push_back({ 496, 40, 16, 16 });
	animghostnorthwest.loop = true;
	animghostnorthwest.speed = 0.2f;

	anim6.frames.push_back({ 208, 40, 16, 16 });

	//southeast
	animghostsoutheast.frames.push_back({ 136, 40, 16, 16 });
	animghostsoutheast.frames.push_back({ 280, 40, 16, 16 });
	animghostsoutheast.frames.push_back({ 424, 40, 16, 16 });
	animghostsoutheast.loop = true;
	animghostsoutheast.speed = 0.2f;

	anim7.frames.push_back({ 136, 40, 16, 16 });

	//southwest
	animghostsouthwest.frames.push_back({ 172, 40, 16, 16 });
	animghostsouthwest.frames.push_back({ 316, 40, 16, 16 });
	animghostsouthwest.frames.push_back({ 460, 40, 16, 16 });
	animghostsouthwest.loop = true;
	animghostsouthwest.speed = 0.2f;

	anim8.frames.push_back({ 172, 40, 16, 16 });

	speed.x = 0;
	speed.y = 0;
	life = 1;
	
	actualanimation = &animghostnorth;

	orientation = "N";


}

Ghost::~Ghost(){
	
}

bool Ghost::Update(){
	
	//position.y += 1;
	//SDL_Rect r = animghostnorth.PeekCurrentFrame();  A(100,235) B(267,300) hayo el Vector AB(267-100,300-235) angulo = atan2(y-Oy,x -Ox); 
	int disx = abs(App->player->position.x - position.x);
	int disy = abs(App->player->position.y - position.y);

	if (App->pause == false){

		if ((disx < 70) || (disy < 70)){
			if ((App->player->position.x < position.x) && (App->player->position.y < position.y)){

				if (colisionNW == false){
					orientation = "NW";
					orientationenemy = "NW";

					oldposition.x = position.x;
					oldposition.y = position.y;

					if (colisionNWenemy == true){
						position.x -= speedd;
					}
					else{
						position.x -= speedd;
						position.y -= speedd;

					}

					colisionN = false;
					colisionS = false;
					colisionW = false;
					colisionE = false;
					colisionNE = false;
					colisionSE = false;
					colisionSW = false;

					colisionNEenemy = false;

					colisionSEenemy = false;
					colisionSWenemy = false;

					colisionNenemy = false;
					colisionSenemy = false;
					colisionEenemy = false;
					colisionWenemy = false;

					actualanimation = &animghostnorthwest;
				}
				else if (colisionNW == true){
					position.x = oldposition.x + 1;
					position.y = oldposition.y + 1;

					actualanimation = &anim6;
					//position.x += speedd;
					//position.y += speedd;
				}

			}
			else if ((App->player->position.x > position.x) && (App->player->position.y > position.y)){

				if (colisionSE == false){
					orientation = "SE";
					orientationenemy = "SE";

					oldposition.x = position.x;
					oldposition.y = position.y;

					if (colisionSEenemy == true){
						position.x += speedd;
					}
					else{
						position.x += speedd;
						position.y += speedd;

					}

					colisionN = false;
					colisionS = false;
					colisionW = false;
					colisionE = false;
					colisionNE = false;
					colisionNW = false;
					colisionSW = false;

					colisionNEenemy = false;
					colisionNWenemy = false;

					colisionSWenemy = false;

					colisionNenemy = false;
					colisionSenemy = false;
					colisionEenemy = false;
					colisionWenemy = false;

					actualanimation = &animghostsoutheast;
				}
				else if (colisionSE == true){

					position.x = oldposition.x - 1;
					position.y = oldposition.y - 1;
					actualanimation = &anim7;
					//position.x -= speedd;
					//position.y -= speedd;
				}

			}
			else if ((App->player->position.x < position.x) && (App->player->position.y > position.y)){

				if (colisionSW == false){
					orientation = "SW";
					orientationenemy = "SW";

					oldposition.x = position.x;
					oldposition.y = position.y;

					if (colisionSWenemy == true){
						position.x -= speedd;
						position.y += speedd;
					}
					else{
						position.x -= speedd;
						position.y += speedd;
					}

					colisionN = false;
					colisionS = false;
					colisionW = false;
					colisionE = false;
					colisionNE = false;
					colisionNW = false;
					colisionSE = false;

					colisionNEenemy = false;
					colisionNWenemy = false;
					colisionSEenemy = false;

					colisionNenemy = false;
					colisionSenemy = false;
					colisionEenemy = false;
					colisionWenemy = false;

					actualanimation = &animghostsouthwest;
				}
				else if (colisionSW == true){
					position.x = oldposition.x + 1;
					position.y = oldposition.y - 1;
					actualanimation = &anim8;
					//position.x += speedd;
					//position.y -= speedd;
				}

			}
			else if ((App->player->position.x > position.x) && (App->player->position.y < position.y)){

				if (colisionNE == false){
					orientation = "NE";
					orientationenemy = "NE";

					oldposition.x = position.x;
					oldposition.y = position.y;

					if (colisionNEenemy == true){
						position.x += speedd;
					}
					else{
						position.x += speedd;
						position.y -= speedd;
					}

					colisionN = false;
					colisionS = false;
					colisionW = false;
					colisionE = false;
					colisionNW = false;
					colisionSE = false;
					colisionSW = false;


					colisionNWenemy = false;
					colisionSEenemy = false;
					colisionSWenemy = false;

					colisionNenemy = false;
					colisionSenemy = false;
					colisionEenemy = false;
					colisionWenemy = false;

					actualanimation = &animghostnorthwest;
				}
				else if (colisionNE == true){
					position.x = oldposition.x - 1;
					position.y = oldposition.y + 1;
					actualanimation = &anim5;
					//position.x -= speedd;
					//	position.y += speedd;
				}

			}
			else if ((App->player->position.x == position.x) && (App->player->position.y < position.y)){

				if (colisionN == false){
					orientation = "N";
					orientationenemy = "N";
					//oldposition.x = position.x;
					oldposition.y = position.y;

					if (colisionNenemy == true){
						position.y += speedd;
					}
					else
						position.y -= speedd;


					colisionS = false;
					colisionW = false;
					colisionE = false;

					colisionNE = false;
					colisionNW = false;
					colisionSE = false;
					colisionSW = false;

					colisionNWenemy = false;
					colisionSEenemy = false;
					colisionSWenemy = false;

					colisionNEenemy = false;
					colisionSenemy = false;
					colisionEenemy = false;
					colisionWenemy = false;

					actualanimation = &animghostnorth;
				}
				else if (colisionN == true){
					position.y = oldposition.y + 1;
					if (App->player->position.x < position.x){
						position.x -= speedd;
					}
					else if (App->player->position.x > position.x){
						position.x += speedd;
					}
				}

			}
			else if ((App->player->position.x == position.x) && (App->player->position.y > position.y)){

				if (colisionS == false){
					orientation = "S";
					orientationenemy = "S";
					//oldposition.x = position.x;
					oldposition.y = position.y;

					if (colisionSenemy == true){
						position.y -= speedd;
					}
					else
						position.y += speedd;

					colisionN = false;

					colisionW = false;
					colisionE = false;

					colisionNE = false;
					colisionNW = false;
					colisionSE = false;
					colisionSW = false;

					colisionNWenemy = false;
					colisionSEenemy = false;
					colisionSWenemy = false;

					colisionNenemy = false;
					colisionNEenemy = false;
					colisionEenemy = false;
					colisionWenemy = false;

					actualanimation = &animghostsouth;
				}
				else if (colisionS == true){
					position.y = oldposition.y - 1;
					if (App->player->position.x < position.x){
						position.x -= speedd;
					}
					else if (App->player->position.x > position.x){
						position.x += speedd;
					}
				}

			}
			else if ((App->player->position.x > position.x) && (App->player->position.y == position.y)){

				if (colisionE == false){
					orientation = "E";
					orientationenemy = "E";
					oldposition.x = position.x;
					//oldposition.y = position.y;

					if (colisionEenemy == true){
						position.x -= speedd;
					}
					else
						position.x += speedd;

					colisionN = false;
					colisionS = false;
					colisionW = false;


					colisionNE = false;
					colisionNW = false;
					colisionSE = false;
					colisionSW = false;

					colisionNWenemy = false;
					colisionSEenemy = false;
					colisionSWenemy = false;

					colisionNenemy = false;
					colisionSenemy = false;
					colisionNEenemy = false;
					colisionWenemy = false;

					actualanimation = &animghosteast;
				}
				else if (colisionE == true){
					position.x = oldposition.x - 1;
					if (App->player->position.y < position.y){
						position.y -= speedd;
					}
					else if (App->player->position.y > position.y){
						position.y += speedd;
					}
				}

			}
			else if ((App->player->position.x < position.x) && (App->player->position.y == position.y)){

				if (colisionW == false){
					orientation = "W";
					orientationenemy = "W";
					oldposition.x = position.x;
					//oldposition.y = position.y;
					if (colisionWenemy == true){
						position.x += speedd;
					}
					else
						position.x -= speedd;

					colisionN = false;
					colisionS = false;

					colisionE = false;

					colisionNE = false;
					colisionNW = false;
					colisionSE = false;
					colisionSW = false;

					colisionNWenemy = false;
					colisionSEenemy = false;
					colisionSWenemy = false;

					colisionNenemy = false;
					colisionSenemy = false;
					colisionEenemy = false;
					colisionNEenemy = false;

					actualanimation = &animghostwest;
				}
				else if (colisionW == true){
					position.x = oldposition.x + 1;
					if (App->player->position.y < position.y){
						position.y -= speedd;
					}
					else if (App->player->position.y > position.y){
						position.y += speedd;
					}
				}

			}
		}


		if (collider != NULL)
		{
			SDL_Rect r = animghostnorth.PeekCurrentFrame();
			collider->rect = { position.x, position.y, r.w, r.h };
		}
	}
	return true;
}

