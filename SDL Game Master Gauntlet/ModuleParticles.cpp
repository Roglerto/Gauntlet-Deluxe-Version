#include <math.h>
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

using namespace std;

ModuleParticles::ModuleParticles() : Module()
{
}

ModuleParticles::~ModuleParticles()
{}

bool ModuleParticles::CleanUp(){

	if (active.size() != 0){
		for (list<Particle*>::iterator it = active.begin(); it != active.end();)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		active.clear();
	}
	return true;
}
// Update: draw background
update_status ModuleParticles::PostUpdate()
{
	for(list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;
		
		if(p->Update() == false)
		{
			
				App->renderer->Blit(p->graphics, p->position.x, p->position.y, &(p->explosion.GetCurrentFrame()));
			
				
					RELEASE(p);
					it = active.erase(it);
					
					break;
				
			
		} 
		else if(p->timer.Read() > p->delay)
		{
			App->renderer->Blit(p->graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}
		++it;
	}

	return UPDATE_CONTINUE;
}

SDL_Rect ModuleParticles::destructible_door()
{
	return aux;
}

// Always destroy particles that collide
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
	{

		if((*it)->collider == c1)
		{
			
			//App->renderer->Blit((*it)->graphics, (*it)->position.x, (*it)->position.y, &((*it)->explosion.GetCurrentFrame()));
			if (c2->type==COLLIDER_DESTRUCTIBLE_DOOR)
				aux = (*it)->collider->rect;


			if ((c2->type == COLLIDER_CORNER) &&  ( ((*it)->orientation == "NE") || (*it)->orientation == "SE" || (*it)->orientation == "NW" || (*it)->orientation == "SW")){


			
				break;

			}


				if ((*it)->collider != nullptr)
					(*it)->collider->to_delete = true;

				RELEASE(*it);
				it = active.erase(it);
				break;

			
			
			
			/*if ((*it)->orientation=="S"){


				(*it)->speed.x = 0;
				(*it)->speed.y = -3;
				
				break;
			}
			else if((*it)->orientation == "W"){
				
				(*it)->speed.x = 0;
				(*it)->speed.y = 3;
				
				break;
			} 
			else if ((*it)->orientation == "A"){

				(*it)->speed.x = 3;
				(*it)->speed.y = 0;
				
				break;
			}
			else if ((*it)->orientation == "D"){
				(*it)->speed.x = -3;
				(*it)->speed.y = 0;
				
				break;
			}
			else{
				RELEASE(*it);
				it = active.erase(it);
				break; 
			}
			
			else if ((*it)->orientation == "NE"){
				(*it)->speed.x = 2;
				(*it)->speed.y = 2;
				(*it)->orientation = "X";
				it++;
				break;
			}
			else if ((*it)->orientation == "NW"){
				(*it)->speed.x = -2;
				(*it)->speed.y = 2;
				(*it)->orientation = "A";
				break;
			}
			else if ((*it)->orientation == "SE"){
				(*it)->speed.x = 2;
				(*it)->speed.y = -2;
				(*it)->orientation = "S";
				break;
			}
			else if ((*it)->orientation == "SW"){
				(*it)->speed.x = -2;
				(*it)->speed.y = -2;
				(*it)->orientation = "A";
				break;
			}
			else {
				RELEASE(*it);
				it = active.erase(it);
				break;
			}*/
		}
	}
}

void ModuleParticles::AddParticle( const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, string orientation, Uint32 delay)
{
	if (App->player->potion2efect == false){
		if ((active.size() == 0)){
			Particle* p = new Particle(particle);
			p->timer.Start();
			p->position.x = x;
			p->position.y = y;
			p->delay = delay;
			p->orientation = orientation;

			//p->explosion.frames.push_back({ 100, 112, 16, 16 });
			//p->explosion.frames.push_back({ 118, 112, 16, 16 });
			//p->explosion.frames.push_back({ 136, 112, 16, 16 });
			//p->explosion.frames.push_back({ 154, 112, 16, 16 });
			p->explosion.frames.push_back({ 172, 112, 16, 16 });
			//p->explosion.frames.push_back({ 190, 112, 16, 16 });
			p->explosion.loop = true;
			p->explosion.speed = 0.003f;
			//p->timerdeath.Start();
			//p->animexplosion = particleexplosion;

			if (collider_type != COLLIDER_NONE)
			{
				p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
			}

			active.push_back(p);
		}
	}
	else if (App->player->potion2efect == true){
		if ((active.size() <10)){
			Particle* p = new Particle(particle);
			p->timer.Start();
			p->position.x = x;
			p->position.y = y;
			p->delay = delay;
			p->orientation = orientation;

			//p->explosion.frames.push_back({ 100, 112, 16, 16 });
			//p->explosion.frames.push_back({ 118, 112, 16, 16 });
			//p->explosion.frames.push_back({ 136, 112, 16, 16 });
			//p->explosion.frames.push_back({ 154, 112, 16, 16 });
			p->explosion.frames.push_back({ 172, 112, 16, 16 });
			//p->explosion.frames.push_back({ 190, 112, 16, 16 });
			p->explosion.loop = true;
			p->explosion.speed = 0.003f;
			//p->timerdeath.Start();
			//p->animexplosion = particleexplosion;

			if (collider_type != COLLIDER_NONE)
			{
				p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
			}

			active.push_back(p);
		}
	}
	
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete=true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if(timer.Read() > delay + life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	oldposition.x = position.x;
	oldposition.y = position.y;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x, position.y, r.w, r.h};
	}

	return ret;
}