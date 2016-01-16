#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision() : Module()
{
	debug = false;

	// Matrix is game specific, change it to adapt to your own needs
	// ... think of moving this outside ModuleCollision
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;

	
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXIT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXIT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_EXIT] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXIT3] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXIT3] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_EXIT3] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXIT6] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXIT6] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_EXIT6] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXIT4] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXIT4] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_EXIT4] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_EXIT5] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_EXIT5] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_EXIT5] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_CORNER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CORNER] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_GENERATOR] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_TREASURE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POTION] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POTION2] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_POTION3] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_KEY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_KEY2] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FOOD] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_CORNER] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_TREASURE] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_POTION] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_POTION2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_POTION3] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_KEY] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_KEY2] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_FOOD] = true;
	

	matrix[COLLIDER_PLAYER][COLLIDER_DOOR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DOOR2] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_GENERATOR] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_DOOR] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_DOOR2] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_DESTRUCTIBLE_DOOR] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DESTRUCTIBLE_DOOR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DESTRUCTIBLE_DOOR] = true;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_GENERATOR] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DOOR] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DOOR2] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_GENERATOR_N] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_GENERATOR_S] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_GENERATOR_E] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_GENERATOR_W] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_GENERATOR_N] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_GENERATOR_S] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_GENERATOR_E] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_GENERATOR_W] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_GENERATOR_N] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_GENERATOR_S] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_GENERATOR_E] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_GENERATOR_W] = true;

	matrix[COLLIDER_WALL][COLLIDER_ENEMY_GENERATOR_N] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_GENERATOR_S] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_GENERATOR_E] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_GENERATOR_W] = true;

	matrix[COLLIDER_WALL][COLLIDER_ENEMY_GENERATOR_W] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_GENERATOR_W] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_GENERATOR_W] = true;

	/*matrix[COLLIDER_ENEMY_GENERATOR_N][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_GENERATOR_S][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_GENERATOR_E] [COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_GENERATOR_W][COLLIDER_WALL] = true;*/

}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for(list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		c1 = *it;

		for(list<Collider*>::iterator it2 = ++it; it2 != colliders.end(); ++it2)
		{
			c2 = *it2;

			if (SDL_HasIntersection(&c1->rect, &c2->rect))  //c1->CheckCollision(c2->rect)   SDL_HasIntersection( &c1->rect,&c2->rect)
			{
				if(matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if(matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
			else{
				//if (matrix[c1->type][c2->type] && c1->callback)
					//c1->callback->OnNotCollision(c1, c2);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
	{
		for(list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		{
			Collider* col = *it;
			Uint8 alpha = 100;
			switch(col->type)
			{
				case COLLIDER_NONE:
				App->renderer->DrawQuad(col->rect, 255, 255, 255, alpha);
				break;
				case COLLIDER_WALL:
				App->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
				break;
				case COLLIDER_PLAYER:
				App->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
				break;
				case COLLIDER_ENEMY:
				App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
				break;
				case COLLIDER_PLAYER_SHOT:
				App->renderer->DrawQuad(col->rect, 255, 255, 0, alpha);
				break;
				case COLLIDER_ENEMY_SHOT:
				App->renderer->DrawQuad(col->rect, 0, 255, 255, alpha);
				break;
				case COLLIDER_ENEMY_GENERATOR:
				App->renderer->DrawQuad(col->rect, 150, 255, 255, alpha);
				break;
				case COLLIDER_ENEMY_GENERATOR_N:
				App->renderer->DrawQuad(col->rect, 100, 255, 255, alpha);
				break;
				case COLLIDER_ENEMY_GENERATOR_S:
				App->renderer->DrawQuad(col->rect, 120, 255, 255, alpha);
				break;
				case COLLIDER_ENEMY_GENERATOR_E:
				App->renderer->DrawQuad(col->rect, 0, 200, 255, alpha);
				break;
				case COLLIDER_ENEMY_GENERATOR_W:
				App->renderer->DrawQuad(col->rect, 150, 0, 255, alpha);
				break;
				case COLLIDER_TREASURE:
				App->renderer->DrawQuad(col->rect, 150, 10, 255, alpha);
				break;
				case COLLIDER_FOOD:
				App->renderer->DrawQuad(col->rect, 50, 255, 55, alpha);
				break;
				case COLLIDER_KEY:
				App->renderer->DrawQuad(col->rect, 255, 160, 24, alpha);
				break;
				case COLLIDER_POTION:
				App->renderer->DrawQuad(col->rect, 209, 178, 255, alpha);
				break;
				case COLLIDER_POTION2:
				App->renderer->DrawQuad(col->rect, 25, 76, 45, alpha);
				break;
				case COLLIDER_POTION3:
				App->renderer->DrawQuad(col->rect, 255, 10, 35, alpha);
				break;
				case COLLIDER_CORNER:
				App->renderer->DrawQuad(col->rect, 230, 170, 255, alpha);
				break;
				case COLLIDER_DOOR:
				App->renderer->DrawQuad(col->rect, 255, 10, 255, alpha);
				break;
				case COLLIDER_DESTRUCTIBLE_DOOR:
				App->renderer->DrawQuad(col->rect, 5, 10, 5, alpha);
				break;
				case COLLIDER_EXIT:
				App->renderer->DrawQuad(col->rect, 5, 255, 5, alpha);
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(list<Collider*>::reverse_iterator it = colliders.rbegin(); it != colliders.rend(); ++it)
		RELEASE(*it);

	colliders.clear();
	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.push_back(ret);
	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(SDL_Rect r) const  //SLDHASINTERSECT
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}