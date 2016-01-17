#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "ModuleSideMenu.h"
#include "ModuleEnemy.h"
#include "ModuleEnemyGenerator.h"
#include "ModuleItems.h"
#include "ModuleScore.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneIntro.h"
#include "ModuleLevel5.h"
/// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{

	pause.frames.push_back({ 268, 159, 191, 52 });

	// idle animation (just the ship)
	idlenorth.frames.push_back({586, 58, 16, 16});
	idlesouth.frames.push_back({ 658, 58, 16, 16 });
	idlewest.frames.push_back({ 694, 58, 16, 16 });
	idleeast.frames.push_back({ 622, 58, 16, 16 });

	idlenortheast.frames.push_back({ 604, 58, 16, 16 });
	idlenorthwest.frames.push_back({ 712, 58, 16, 16 });
	idlesoutheast.frames.push_back({ 640, 58, 16, 16 });
	idlesouthwest.frames.push_back({ 676, 58, 16, 16 });

	// move upwards
	north.frames.push_back({586, 58, 16, 16});
	north.frames.push_back({730, 58, 16, 16});
	north.frames.push_back({ 82, 76, 16, 16 });
	north.loop = true;
	north.speed = 0.2f;

	// Move down
	south.frames.push_back({ 658, 58, 16, 16 });
	south.frames.push_back({ 10, 76, 16, 16 });
	south.frames.push_back({ 154, 76, 16, 16 });
	south.loop = true;
	south.speed = 0.2f;

	east.frames.push_back({ 622, 58, 16, 16 });
	east.frames.push_back({ 766, 58, 16, 16 });
	east.frames.push_back({ 118, 76, 16, 16 });
	east.loop = true;
	east.speed = 0.2f;

	west.frames.push_back({ 694, 58, 16, 16 });
	west.frames.push_back({ 46, 76, 16, 16 });
	west.frames.push_back({ 190, 76, 16, 16 });
	west.loop = true;
	west.speed = 0.2f;

	northeast.frames.push_back({ 604, 58, 16, 16 });
	northeast.frames.push_back({ 748, 58, 16, 16 });
	northeast.frames.push_back({ 100, 76, 16, 16 });
	northeast.loop = true;
	northeast.speed = 0.2f;

	northwest.frames.push_back({ 712, 58, 16, 16 });
	northwest.frames.push_back({ 64, 76, 16, 16 });
	northwest.frames.push_back({ 208, 76, 16, 16 });
	northwest.loop = true;
	northwest.speed = 0.2f;

	southeast.frames.push_back({ 640, 58, 16, 16 });
	southeast.frames.push_back({ 784, 58, 16, 16 });
	southeast.frames.push_back({ 136, 76, 16, 16 });
	southeast.loop = true;
	southeast.speed = 0.2f;

	southwest.frames.push_back({ 676, 58, 16, 16 });
	southwest.frames.push_back({ 28, 76, 16, 16 });
	southwest.frames.push_back({ 172, 76, 16, 16 });
	southwest.loop = true;
	southwest.speed = 0.2f;
	//----------------------------------------------------------
	idlenorthfaster.frames.push_back({ 514, 40, 16, 16 });
	idlesouthfaster.frames.push_back({ 586, 40, 16, 16 });
	idlewestfaster.frames.push_back({ 622, 40, 16, 16 });
	idleeastfaster.frames.push_back({ 550, 40, 16, 16 });

	idlenortheastfaster.frames.push_back({ 532, 40, 16, 16 });
	idlenorthwestfaster.frames.push_back({ 640, 40, 16, 16 });
	idlesoutheastfaster.frames.push_back({ 568, 40, 16, 16 });
	idlesouthwestfaster.frames.push_back({ 604, 40, 16, 16 });

	// move upwards
	northfaster.frames.push_back({ 514, 40, 16, 16 });
	northfaster.frames.push_back({ 658, 40, 16, 16 });
	northfaster.frames.push_back({ 10, 58, 16, 16 });
	northfaster.loop = true;
	northfaster.speed = 0.2f;

	// Move down
	southfaster.frames.push_back({ 586, 40, 16, 16 });
	southfaster.frames.push_back({ 730, 40, 16, 16 });
	southfaster.frames.push_back({ 82, 58, 16, 16 });
	southfaster.loop = true;
	southfaster.speed = 0.2f;

	eastfaster.frames.push_back({ 550, 40, 16, 16 });
	eastfaster.frames.push_back({ 694, 40, 16, 16 });
	eastfaster.frames.push_back({ 46, 58, 16, 16 });
	eastfaster.loop = true;
	eastfaster.speed = 0.2f;

	westfaster.frames.push_back({ 622, 40, 16, 16 });
	westfaster.frames.push_back({ 766, 40, 16, 16 });
	westfaster.frames.push_back({ 118, 58, 16, 16 });
	westfaster.loop = true;
	westfaster.speed = 0.2f;

	northeastfaster.frames.push_back({ 532, 40, 16, 16 });
	northeastfaster.frames.push_back({ 676, 40, 16, 16 });
	northeastfaster.frames.push_back({ 28, 58, 16, 16 });
	northeastfaster.loop = true;
	northeastfaster.speed = 0.2f;

	northwestfaster.frames.push_back({ 640, 40, 16, 16 });
	northwestfaster.frames.push_back({ 784, 40, 16, 16 });
	northwestfaster.frames.push_back({ 136, 58, 16, 16 });
	northwestfaster.loop = true;
	northwestfaster.speed = 0.2f;

	southeastfaster.frames.push_back({ 568, 40, 16, 16 });
	southeastfaster.frames.push_back({ 712, 40, 16, 16 });
	southeastfaster.frames.push_back({ 64, 58, 16, 16 });
	southeastfaster.loop = true;
	southeastfaster.speed = 0.2f;

	southwestfaster.frames.push_back({ 604, 40, 16, 16 });
	southwestfaster.frames.push_back({ 748, 40, 16, 16 });
	southwestfaster.frames.push_back({ 100, 58, 16, 16 });
	southwestfaster.loop = true;
	southwestfaster.speed = 0.2f;
	//-----------------------------------------------------
	idlenorthpower.frames.push_back({ 550, 202, 16, 16 });
	idlesouthpower.frames.push_back({ 604, 202, 16, 16 });
	idlewestpower.frames.push_back({ 658, 202, 16, 16 });
	idleeastpower.frames.push_back({ 586, 202, 16, 16 });

	idlenortheastpower.frames.push_back({ 568, 202, 16, 16 });
	idlenorthwestpower.frames.push_back({ 676, 202, 16, 16 });
	idlesoutheastpower.frames.push_back({ 604, 202, 16, 16 });
	idlesouthwestpower.frames.push_back({ 640, 202, 16, 16 });

	// move upwards
	northpower.frames.push_back({ 550, 202, 16, 16 });
	northpower.frames.push_back({ 694, 202, 16, 16 });
	northpower.frames.push_back({ 46, 220, 16, 16 });
	northpower.loop = true;
	northpower.speed = 0.2f;

	// Move down
	southpower.frames.push_back({ 622, 202, 16, 16 });
	southpower.frames.push_back({ 766, 202, 16, 16 });
	southpower.frames.push_back({ 118, 220, 16, 16 });
	southpower.loop = true;
	southpower.speed = 0.2f;

	eastpower.frames.push_back({ 586, 202, 16, 16 });
	eastpower.frames.push_back({ 730, 202, 16, 16 });
	eastpower.frames.push_back({ 82, 220, 16, 16 });
	eastpower.loop = true;
	eastpower.speed = 0.2f;

	westpower.frames.push_back({ 658, 202, 16, 16 });
	westpower.frames.push_back({ 10, 220, 16, 16 });
	westpower.frames.push_back({ 154, 220, 16, 16 });
	westpower.loop = true;
	westpower.speed = 0.2f;

	northeastpower.frames.push_back({ 568, 202, 16, 16 });
	northeastpower.frames.push_back({ 712,202, 16, 16 });
	northeastpower.frames.push_back({ 64, 220, 16, 16 });
	northeastpower.loop = true;
	northeastpower.speed = 0.2f;

	northwestpower.frames.push_back({ 676, 202, 16, 16 });
	northwestpower.frames.push_back({ 28, 220, 16, 16 });
	northwestpower.frames.push_back({ 172, 220, 16, 16 });
	northwestpower.loop = true;
	northwestpower.speed = 0.2f;

	southeastpower.frames.push_back({ 604, 202, 16, 16 });
	southeastpower.frames.push_back({ 748, 202, 16, 16 });
	southeastpower.frames.push_back({ 100, 220, 16, 16 });
	southeastpower.loop = true;
	southeastpower.speed = 0.2f;

	southwestpower.frames.push_back({ 640, 202, 16, 16 });
	southwestpower.frames.push_back({ 784, 202, 16, 16 });
	southwestpower.frames.push_back({ 136, 220, 16, 16 });
	southwestpower.loop = true;
	southwestpower.speed = 0.2f;
	//-------------------------------------------------------
	idlenorthguard.frames.push_back({ 10, 94, 16, 16 });
	idlesouthguard.frames.push_back({ 82, 94, 16, 16 });
	idlewestguard.frames.push_back({ 118, 94, 16, 16 });
	idleeastguard.frames.push_back({ 46, 94, 16, 16 });

	idlenortheastguard.frames.push_back({ 28, 94, 16, 16 });
	idlenorthwestguard.frames.push_back({ 136, 94, 16, 16 });
	idlesoutheastguard.frames.push_back({ 64, 94, 16, 16 });
	idlesouthwestguard.frames.push_back({ 100, 94, 16, 16 });

	// move upwards
	northguard.frames.push_back({ 10, 94, 16, 16 });
	northguard.frames.push_back({ 154, 94, 16, 16 });
	northguard.frames.push_back({ 298, 94, 16, 16 });
	northguard.loop = true;
	northguard.speed = 0.2f;

	// Move down
	southguard.frames.push_back({ 82, 94, 16, 16 });
	southguard.frames.push_back({ 226, 94, 16, 16 });
	southguard.frames.push_back({ 370, 94, 16, 16 });
	southguard.loop = true;
	southguard.speed = 0.2f;

	eastguard.frames.push_back({ 46, 94, 16, 16 });
	eastguard.frames.push_back({ 190, 94, 16, 16 });
	eastguard.frames.push_back({ 334, 94, 16, 16 });
	eastguard.loop = true;
	eastguard.speed = 0.2f;

	westguard.frames.push_back({ 118, 94, 16, 16 });
	westguard.frames.push_back({ 262, 94, 16, 16 });
	westguard.frames.push_back({ 406, 94, 16, 16 });
	westguard.loop = true;
	westguard.speed = 0.2f;

	northeastguard.frames.push_back({ 28, 94, 16, 16 });
	northeastguard.frames.push_back({ 172, 94, 16, 16 });
	northeastguard.frames.push_back({ 316, 94, 16, 16 });
	northeastguard.loop = true;
	northeastguard.speed = 0.2f;

	northwestguard.frames.push_back({ 136, 94, 16, 16 });
	northwestguard.frames.push_back({ 280, 94, 16, 16 });
	northwestguard.frames.push_back({ 424, 94, 16, 16 });
	northwestguard.loop = true;
	northwestguard.speed = 0.2f;

	southeastguard.frames.push_back({ 64, 94, 16, 16 });
	southeastguard.frames.push_back({ 208, 94, 16, 16 });
	southeastguard.frames.push_back({ 352, 94, 16, 16 });
	southeastguard.loop = true;
	southeastguard.speed = 0.2f;

	southwestguard.frames.push_back({ 100, 94, 16, 16 });
	southwestguard.frames.push_back({ 244, 94, 16, 16 });
	southwestguard.frames.push_back({ 388, 94, 16, 16 });
	southwestguard.loop = true;
	southwestguard.speed = 0.2f;
	// Particles ---
	// Explosion particle
	// explosion.anim.frames.push_back({208, 112, 16, 16});
	// explosion.anim.frames.push_back({ 226, 112, 16, 16 });
	// explosion.anim.frames.push_back({ 244, 112, 16, 16 });
	// explosion.anim.frames.push_back({ 262, 112, 16, 16 });
	// explosion.anim.loop = false;
	// explosion.anim.speed = 0.3f;
	
	// Laser particle
	laser.anim.frames.push_back({694, 76, 16, 16});
	laser.anim.frames.push_back({712, 76, 16, 16});
	laser.anim.frames.push_back({ 730, 76, 16, 16 });
	laser.speed.x = 0;
	laser.speed.y = 0;
	laser.life = 1000;
	laser.anim.speed = 1.0f;

	explosionlaser.frames.push_back({ 100, 112, 16, 16 });
    explosionlaser.frames.push_back({ 118, 112, 16, 16 });
    explosionlaser.frames.push_back({ 136, 112, 16, 16 });
    explosionlaser.frames.push_back({ 154, 112, 16, 16 });
	explosionlaser.frames.push_back({ 172, 112, 16, 16 });
	explosionlaser.frames.push_back({ 190, 112, 16, 16 });
    explosionlaser.loop = true;
    explosionlaser.speed = 0.005f;

	transformation.frames.push_back({ 676, 166, 16, 16 });
	transformation.frames.push_back({ 694, 166, 16, 16 });
	transformation.frames.push_back({ 712, 166, 16, 16 });
	transformation.loop = true;
	transformation.speed = 0.5f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	
	graphics = App->textures->Load("Gauntlet/g.png");
	graphics2 = App->textures->Load("Gauntlet/in.png");

	fx = App->audio->LoadFx("starting.wav");
	fxe = App->audio->LoadFx("explosion.wav");

	string size;
	myfilemap.open("Gauntlet/score.txt", std::fstream::in);
	while (getline(myfilemap, size)){

		int num = atoi(size.c_str());
		scores.push_back(num);
	}
	myfilemap.close();
	App->renderer->playermovement.x = position.x;
	App->renderer->playermovement.y = position.y;

	positioncolision.x = position.x;
	positioncolision.y = position.y;

	current_animation = &idlesouth;
	colisionorientation = "S";
	life = 2;
	score = 0;
	SDL_Texture* particles = App->textures->Load("Gauntlet/g.png");
	//explosion.graphics = laser.graphics = particles;
	laser.graphics = particles;

	//explosion.fx = App->audio->LoadFx("explosion.wav");
	laser.fx = App->audio->LoadFx("slimeball.wav");

	collider = App->collision->AddCollider({0, 0, 16, 16}, COLLIDER_PLAYER, this);

	finished = false;

	App->renderer->cameragame = true;

	score = App->playerscore;
	//potion1 = App->potion1;
	//potion2 = App->potion2;
	//potion3 = App->potion3;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(graphics2);
	scores.clear();
	key = false;
	 potion1 = false;
	 potion2 = false;
	 potion3 = false;
	 activepotion = false;
	 food = false;

	 potion1efect = false;
	 potion3efect = false;
	 potion2efect = false;
	return true;
}

update_status ModulePlayer::PreUpdate(){
	if (potion1efect == false){
		speed = 1;
		speed2 = 3;
	}
	else if (potion1efect == true){

		speed = 3;
		speed2 = 10;
	}
	
	return UPDATE_CONTINUE;
}
// Update
update_status ModulePlayer::Update()
{



	if (finished == true)
		return UPDATE_CONTINUE;

	if ((App->input->GetKey(SDL_SCANCODE_Y) == KEY_UP)){
		if (notpause == false){
			App->pause = true;
			notpause = true;
		}
		else if (notpause == true){
			App->pause = false;
			notpause = false;

		}
	}
	if (App->pause == false){
		if ((App->input->GetKey(SDL_SCANCODE_P) == KEY_UP)){
			App->audio->PlayFx(fx);

			App->scene_ghost->CleanUp();
			App->scene_ghost->Disable();
			App->scene_ghost_generator->CleanUp();
			App->scene_ghost_generator->Disable();
			App->scene_items->CleanUp();
			App->scene_items->Disable();
			//App->scene_menu->CleanUp();
			App->scene_menu->Disable();
			//App->player->CleanUp();

			scores.push_back(score);

			for (int i = 0; i < scores.size(); i++){
				for (int j = 0; j < scores.size() - 1; j++){
					if (scores[j] < scores[j + 1]){
						tm = scores[j];
						scores[j] = scores[j + 1];
						scores[j + 1] = tm;
					}
				}
			}

			ofstream logg;
			logg.open("Gauntlet/score.txt");
			logg << scores[0];
			logg << "\n";
			logg << scores[1];
			logg << "\n";
			logg << scores[2];

			logg.close();
			App->potion1 = potion1;
			App->potion2 = potion2;
			App->potion3 = potion3;


			App->player->Disable();

			//App->collision->CleanUp();
			//App->collision->Disable();



			App->fade->FadeToBlack((Module*)App->scene_score, this, 1.0f);


		}


		if ((App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) && potion1 == true && activepotion == false){
			activepotion = true;
			potion.Start();
			potion1efect = true;
			potion1 = false;
			transformation1 = true;
			destransformation = true;
			transformationt.Start();

			current_animation = &idlenorthwestfaster;


		}
		if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) && potion2 == true && activepotion == false){
			activepotion = true;
			potion.Start();
			potion2efect = true;
			potion2 = false;
			transformation2 = true;
			destransformation = true;
			transformationt.Start();
			current_animation = &idlenorthwestpower;
		}
		if ((App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) && potion3 == true && activepotion == false){
			activepotion = true;
			potion.Start();
			potion3efect = true;
			potion3 = false;
			transformation3 = true;
			destransformation = true;
			transformationt.Start();
			current_animation = &idlenorthwestguard;
		}

		if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && potion2efect == true)
		{
			if (potion2efect == true){

				laser.speed.y = -2;
				laser.speed.x = 0;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "N");
				laser.speed.y = 2;
				laser.speed.x = 0;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "S");
				laser.speed.y = 0;
				laser.speed.x = 2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "E");
				laser.speed.y = 0;
				laser.speed.x = -2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "W");

				laser.speed.y = -2;
				laser.speed.x = -2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "NW");
				laser.speed.y = -2;
				laser.speed.x = 2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "NE");
				laser.speed.y = 2;
				laser.speed.x = -2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "SW");
				laser.speed.y = 2;
				laser.speed.x = 2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, "SE");

			}
		}

		if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) && potion2efect == false)
		{


			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN){
				colisionorientation = "W";
			}
			else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN){
				colisionorientation = "S";
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN){
				colisionorientation = "A";
			}
			else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN){
				colisionorientation = "D";
			}
			else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)){
				colisionorientation = "NE";
			}
			else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)){
				colisionorientation = "NW";
			}
			else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)){
				colisionorientation = "SE";
			}
			else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)){
				colisionorientation = "SW";
			}

			if ((colisionorientation == "W")){
				if (transformation1 == true)
					current_animation = &idlenorthfaster;
				else if (transformation2 == true)
					current_animation = &idlenorthpower;
				else if (transformation3 == true)
					current_animation = &idlenorthguard;
				else current_animation = &idlenorth;
				laser.speed.y = -2;
				laser.speed.x = 0;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}

			else if (((colisionorientation == "S"))){
				if (transformation1 == true)
					current_animation = &idlesouthfaster;
				else if (transformation2 == true)
					current_animation = &idlesouthpower;
				else if (transformation3 == true)
					current_animation = &idlesouthguard;
				else current_animation = &idlesouth;
				laser.speed.y = 2;
				laser.speed.x = 0;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}
			else if (colisionorientation == "A"){
				if (transformation1 == true)
					current_animation = &idlewestfaster;
				else if (transformation2 == true)
					current_animation = &idlewestpower;
				else if (transformation3 == true)
					current_animation = &idlewestguard;
				else current_animation = &idlewest;
				laser.speed.x = -2;
				laser.speed.y = 0;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}
			else if (colisionorientation == "D"){
				if (transformation1 == true)
					current_animation = &idleeastfaster;
				else if (transformation2 == true)
					current_animation = &idleeastpower;
				else if (transformation3 == true)
					current_animation = &idleeastguard;
				else current_animation = &idleeast;
				laser.speed.x = 2;
				laser.speed.y = 0;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}
			else if (colisionorientation == "NE"){
				if (transformation1 == true)
					current_animation = &idlenortheastfaster;
				else if (transformation2 == true)
					current_animation = &idlenortheastpower;
				else if (transformation3 == true)
					current_animation = &idlenortheastguard;
				else current_animation = &idlenortheast;
				laser.speed.x = 2;
				laser.speed.y = -2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}
			else if (colisionorientation == "NW"){
				if (transformation1 == true)
					current_animation = &idlenorthwestfaster;
				else if (transformation2 == true)
					current_animation = &idlenorthwestpower;
				else if (transformation3 == true)
					current_animation = &idlenorthwestguard;
				else current_animation = &idlenorthwest;
				laser.speed.x = -2;
				laser.speed.y = -2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}
			else if (colisionorientation == "SE"){
				if (transformation1 == true)
					current_animation = &idlesoutheastfaster;
				else if (transformation2 == true)
					current_animation = &idlesoutheastpower;
				else if (transformation3 == true)
					current_animation = &idlesoutheastguard;
				else current_animation = &idlesoutheast;
				laser.speed.x = 2;
				laser.speed.y = 2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}
			else if (colisionorientation == "SW"){
				if (transformation1 == true)
					current_animation = &idlesouthwestfaster;
				else if (transformation2 == true)
					current_animation = &idlesouthwestpower;
				else if (transformation3 == true)
					current_animation = &idlesouthwestguard;
				else current_animation = &idlesouthwest;
				laser.speed.x = -2;
				laser.speed.y = 2;
				App->particles->AddParticle(laser, position.x, position.y, COLLIDER_PLAYER_SHOT, colisionorientation);
			}
		}

		else{
			if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
			{
				if (colisionNORTHEAST == false){
					positioncolision.y = position.y;
					positioncolision.x = position.x;
					position.y -= speed;
					position.x += speed;

					if ((App->renderer->camera.x > -550) && (App->renderer->camera.y < 0)){

						App->renderer->camera.x -= speed2;
						App->renderer->camera.y += speed2;

					}

					colisionorientation = "NE";
					colisionWEST = false;
					colisionNORTH = false;
					colisionSOUTH = false;
					colisionEAST = false;

					colisionSOUTHWEST = false;
					colisionNORTHWEST = false;
					colisionSOUTHEAST = false;
				}
				else if (colisionNORTHEAST == true){
					position.y = positioncolision.y + 1;
					position.x = positioncolision.x - 1;

					if (transformation1 == true)
						current_animation = &idlenortheastfaster;
					else if (transformation2 == true)
						current_animation = &idlenortheastpower;
					else if (transformation3 == true)
						current_animation = &idlenortheastguard;
					else current_animation = &idlenortheast;
					//colisionNORTHEAST = false;
				}
				if ((current_animation != &northeast) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					northeast.Reset();
					current_animation = &northeast;
				}
				if ((current_animation != &northeastpower) && (transformation2 == true))
				{
					northeastpower.Reset();
					current_animation = &northeastpower;

				}
				if ((current_animation != &northeastfaster) && (transformation1 == true))
				{
					northeastfaster.Reset();
					current_animation = &northeastfaster;

				}
				if ((current_animation != &northeastguard) && (transformation3 == true))
				{
					northeastguard.Reset();
					current_animation = &northeastguard;

				}
			}
			else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
			{
				if (colisionNORTHWEST == false){
					positioncolision.y = position.y;
					positioncolision.x = position.x;
					position.y -= speed;
					position.x -= speed;

					if ((App->renderer->camera.x < 0) && (App->renderer->camera.y < 0)){

						App->renderer->camera.x += speed2;
						App->renderer->camera.y += speed2;

					}

					colisionorientation = "NW";
					colisionWEST = false;
					colisionNORTH = false;
					colisionSOUTH = false;
					colisionEAST = false;
					colisionNORTHEAST = false;
					colisionSOUTHWEST = false;

					colisionSOUTHEAST = false;
				}
				else if (colisionNORTHWEST == true){
					position.y = positioncolision.y + 1;
					position.x = positioncolision.x + 1;

					if (transformation1 == true)
						current_animation = &idlenorthwestfaster;
					else if (transformation2 == true)
						current_animation = &idlenorthwestfaster;
					else if (transformation3 == true)
						current_animation = &idlenorthwestfaster;
					else current_animation = &idlenorthwest;
					//colisionNORTHWEST = false;
				}
				if ((current_animation != &northwest) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					northwest.Reset();
					current_animation = &northwest;
				}
				if ((current_animation != &northwestpower) && (transformation2 == true))
				{
					northwestpower.Reset();
					current_animation = &northwestpower;

				}
				if ((current_animation != &northwestfaster) && (transformation1 == true))
				{
					northwestfaster.Reset();
					current_animation = &northwestfaster;

				}
				if ((current_animation != &northwestguard) && (transformation3 == true))
				{
					northwestguard.Reset();
					current_animation = &northwestguard;

				}
			}
			else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
			{
				if (colisionSOUTHEAST == false){
					positioncolision.y = position.y;
					positioncolision.x = position.x;
					position.y += speed;
					position.x += speed;

					if ((App->renderer->camera.x > -550) && (App->renderer->camera.y > -600)){

						App->renderer->camera.x -= speed2;
						App->renderer->camera.y -= speed2;

					}

					colisionorientation = "SE";
					colisionWEST = false;
					colisionNORTH = false;
					colisionSOUTH = false;
					colisionEAST = false;
					colisionNORTHEAST = false;
					colisionSOUTHWEST = false;
					colisionNORTHWEST = false;

				}
				else if (colisionSOUTHEAST == true){
					position.y = positioncolision.y - 1;
					position.x = positioncolision.x - 1;

					if (transformation1 == true)
						current_animation = &idlesoutheastfaster;
					else if (transformation2 == true)
						current_animation = &idlesoutheastpower;
					else if (transformation3 == true)
						current_animation = &idlesoutheastguard;
					else current_animation = &idlesoutheast;
					//colisionSOUTHEAST = false;
				}
				if ((current_animation != &southeast) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					southeast.Reset();
					current_animation = &southeast;
				}
				if ((current_animation != &southeastpower) && (transformation2 == true))
				{
					southeastpower.Reset();
					current_animation = &southeastpower;

				}
				if ((current_animation != &southeastfaster) && (transformation1 == true))
				{
					southeastfaster.Reset();
					current_animation = &southeastfaster;

				}
				if ((current_animation != &southeastguard) && (transformation3 == true))
				{
					southeastguard.Reset();
					current_animation = &southeastguard;

				}
			}
			else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
			{
				if (colisionSOUTHWEST == false){
					positioncolision.y = position.y;
					positioncolision.x = position.x;
					position.y += speed;
					position.x -= speed;

					if ((App->renderer->camera.x < 0) && (App->renderer->camera.y > -600)){

						App->renderer->camera.x += speed2;
						App->renderer->camera.y -= speed2;

					}

					colisionorientation = "SW";
					colisionWEST = false;
					colisionNORTH = false;
					colisionSOUTH = false;
					colisionEAST = false;
					colisionNORTHEAST = false;

					colisionNORTHWEST = false;
					colisionSOUTHEAST = false;
				}
				else if (colisionSOUTHWEST == true){
					position.y = positioncolision.y - 1;
					position.x = positioncolision.x + 1;

					if (transformation1 == true)
						current_animation = &idlesouthwestfaster;
					else if (transformation2 == true)
						current_animation = &idlesouthwestpower;
					else if (transformation3 == true)
						current_animation = &idlesouthwestguard;
					else current_animation = &idlesouthwest;
					//colisionSOUTHWEST = false;
				}
				if ((current_animation != &southwest) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					southwest.Reset();
					current_animation = &southwest;
				}
				if ((current_animation != &southwestpower) && (transformation2 == true))
				{
					southwestpower.Reset();
					current_animation = &southwestpower;

				}
				if ((current_animation != &southwestfaster) && (transformation1 == true))
				{
					southwestfaster.Reset();
					current_animation = &southwestfaster;

				}
				if ((current_animation != &southwestguard) && (transformation3 == true))
				{
					southwestguard.Reset();
					current_animation = &southwestguard;

				}
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				if (colisionWEST == false){
					positioncolision.x = position.x;
					positioncolision.y = position.y;
					position.x -= speed;

					if (App->renderer->camera.x < 0){
						if (position.x < 400){      //300
							App->renderer->camera.x += speed2;
						}
					}

					colisionorientation = "A";

					colisionNORTH = false;
					colisionSOUTH = false;
					colisionEAST = false;
					colisionNORTHEAST = false;
					colisionSOUTHWEST = false;
					colisionNORTHWEST = false;
					colisionSOUTHEAST = false;
				}
				else if (colisionWEST == true){
					position.y = positioncolision.y;
					position.x = positioncolision.x + 1;

					if (transformation1 == true)
						current_animation = &idlewestfaster;
					else if (transformation2 == true)
						current_animation = &idlewestpower;
					else if (transformation3 == true)
						current_animation = &idlewestguard;
					else current_animation = &idlewest;
					//colisionWEST= false;
				}
				if ((current_animation != &west) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					west.Reset();
					current_animation = &west;
				}
				if ((current_animation != &westpower) && (transformation2 == true))
				{
					westpower.Reset();
					current_animation = &westpower;

				}
				if ((current_animation != &westfaster) && (transformation1 == true))
				{
					westfaster.Reset();
					current_animation = &westfaster;

				}
				if ((current_animation != &westguard) && (transformation3 == true))
				{
					westguard.Reset();
					current_animation = &westguard;

				}

			}

			else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				if (colisionEAST == false){
					positioncolision.x = position.x;
					positioncolision.y = position.y;
					position.x += speed;

					if (App->renderer->camera.x > -550){
						if (position.x > 120){      //120
							App->renderer->camera.x -= speed2;
						}
					}


					colisionorientation = "D";
					colisionWEST = false;
					colisionNORTH = false;
					colisionSOUTH = false;

					colisionNORTHEAST = false;
					colisionSOUTHWEST = false;
					colisionNORTHWEST = false;
					colisionSOUTHEAST = false;
				}
				else if (colisionEAST == true){
					position.y = positioncolision.y;
					position.x = positioncolision.x - 1;

					if (transformation1 == true)
						current_animation = &idleeastfaster;
					else if (transformation2 == true)
						current_animation = &idleeastpower;
					else if (transformation3 == true)
						current_animation = &idleeastguard;
					else current_animation = &idleeast;
					//colisionEAST = false;
				}
				if ((current_animation != &east) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					east.Reset();
					current_animation = &east;
				}
				if ((current_animation != &eastpower) && (transformation2 == true))
				{
					eastpower.Reset();
					current_animation = &eastpower;

				}
				if ((current_animation != &eastfaster) && (transformation1 == true))
				{
					eastfaster.Reset();
					current_animation = &eastfaster;

				}
				if ((current_animation != &eastguard) && (transformation3 == true))
				{
					eastguard.Reset();
					current_animation = &eastguard;

				}

			}

			else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				if (colisionSOUTH == false){
					positioncolision.y = position.y;
					positioncolision.x = position.x;
					position.y += speed;

					if (App->renderer->camera.y > -600){
						if (position.y > 120){
							App->renderer->camera.y -= speed2;
						}
					}


					colisionorientation = "S";
					colisionWEST = false;
					colisionNORTH = false;

					colisionEAST = false;
					colisionNORTHEAST = false;
					colisionSOUTHWEST = false;
					colisionNORTHWEST = false;
					colisionSOUTHEAST = false;
				}
				else if (colisionSOUTH == true){
					position.y = positioncolision.y - 1;
					position.x = positioncolision.x;

					if (transformation1 == true)
						current_animation = &idlesouthfaster;
					else if (transformation2 == true)
						current_animation = &idlesouthpower;
					else if (transformation3 == true)
						current_animation = &idlesouthguard;
					else current_animation = &idlesouth;
					//colisionSOUTH = false;

				}
				if ((current_animation != &south) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					south.Reset();
					current_animation = &south;
				}
				if ((current_animation != &southpower) && (transformation2 == true))
				{
					southpower.Reset();
					current_animation = &southpower;

				}
				if ((current_animation != &southfaster) && (transformation1 == true))
				{
					southfaster.Reset();
					current_animation = &southfaster;

				}
				if ((current_animation != &southguard) && (transformation3 == true))
				{
					southguard.Reset();
					current_animation = &southguard;

				}
			}

			else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{

				if (colisionNORTH == false){
					positioncolision.y = position.y;
					positioncolision.x = position.x;
					position.y -= speed;

					if (App->renderer->camera.y < 0){
						if (position.y < 400){
							App->renderer->camera.y += speed2;
						}
					}

					colisionorientation = "W";
					colisionWEST = false;

					colisionSOUTH = false;
					colisionEAST = false;
					colisionNORTHEAST = false;
					colisionSOUTHWEST = false;
					colisionNORTHWEST = false;
					colisionSOUTHEAST = false;
				}
				else if (colisionNORTH == true){
					position.y = positioncolision.y + 1;
					position.x = positioncolision.x;

					if (transformation1 == true)
						current_animation = &idlenorthfaster;
					else if (transformation2 == true)
						current_animation = &idlenorthpower;
					else if (transformation3 == true)
						current_animation = &idlenorthguard;
					else current_animation = &idlenorth;
					//colisionNORTH = false;
				}
				if ((current_animation != &north) && (transformation2 == false) && (transformation3 == false) && (transformation1 == false))
				{
					north.Reset();
					current_animation = &north;
				}
				if ((current_animation != &northpower) && (transformation2 == true))
				{
					northpower.Reset();
					current_animation = &northpower;

				}
				if ((current_animation != &northfaster) && (transformation1 == true))
				{
					northfaster.Reset();
					current_animation = &northfaster;

				}
				if ((current_animation != &northguard) && (transformation3 == true))
				{
					northguard.Reset();
					current_animation = &northguard;

				}
			}
		}

		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)){

			if (current_animation != &idlenortheast)
			{
				idlenortheast.Reset();
				if (transformation1 == true)
					current_animation = &idlenortheastfaster;
				else if (transformation2 == true)
					current_animation = &idlenortheastpower;
				else if (transformation3 == true)
					current_animation = &idlenortheastguard;
				else current_animation = &idlenortheast;
			}

		}
		else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)){

			if (current_animation != &idlenorthwest)
			{
				idlenorthwest.Reset();
				if (transformation1 == true)
					current_animation = &idlenorthwestfaster;
				else if (transformation2 == true)
					current_animation = &idlenorthwestpower;
				else if (transformation3 == true)
					current_animation = &idlenorthwestguard;
				else current_animation = &idlenorthwest;
			}

		}
		else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)){

			if (current_animation != &idlesoutheast)
			{
				idlesoutheast.Reset();
				if (transformation1 == true)
					current_animation = &idlesoutheastfaster;
				else if (transformation2 == true)
					current_animation = &idlesoutheastpower;
				else if (transformation3 == true)
					current_animation = &idlesoutheastguard;
				else current_animation = &idlesoutheast;
			}

		}
		else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)){

			if (current_animation != &idlesouthwest)
			{
				idlesouthwest.Reset();
				if (transformation1 == true)
					current_animation = &idlesouthwestfaster;
				else if (transformation2 == true)
					current_animation = &idlesouthwestpower;
				else if (transformation3 == true)
					current_animation = &idlesouthwestguard;
				else current_animation = &idlesouthwest;
			}

		}
		else if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP)){

			if (current_animation != &idlesouth)
			{
				idlesouth.Reset();
				if (transformation1 == true)
					current_animation = &idlesouthfaster;
				else if (transformation2 == true)
					current_animation = &idlesouthpower;
				else if (transformation3 == true)
					current_animation = &idlesouthguard;
				else current_animation = &idlesouth;
			}

		}
		else if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_UP)){

			if (current_animation != &idlenorth)
			{
				idlenorth.Reset();
				if (transformation1 == true)
					current_animation = &idlenorthfaster;
				else if (transformation2 == true)
					current_animation = &idlenorthpower;
				else if (transformation3 == true)
					current_animation = &idlenorthguard;
				else current_animation = &idlenorth;
			}

		}
		else if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)){

			if (current_animation != &idlewest)
			{
				idlewest.Reset();
				if (transformation1 == true)
					current_animation = &idlewestfaster;
				else if (transformation2 == true)
					current_animation = &idlewestpower;
				else if (transformation3 == true)
					current_animation = &idlewestguard;
				else current_animation = &idlewest;
			}

		}
		else if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)){

			if (current_animation != &idleeast)
			{
				idleeast.Reset();
				if (transformation1 == true)
					current_animation = &idleeastfaster;
				else if (transformation2 == true)
					current_animation = &idleeastpower;
				else if (transformation3 == true)
					current_animation = &idleeastguard;
				else current_animation = &idleeast;
			}

		}


		collider->SetPos(position.x, position.y);
	}
	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	if (destransformation == true){
		App->renderer->Blit(graphics, position.x, position.y, &(transformation.GetCurrentFrame()));
	}
	
	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (App->pause == true){

		App->renderer->Blit(graphics2, 70,130, &(pause.GetCurrentFrame()),0.0f);
	}
	if ((potion.Read() > 10000) && activepotion==true){
		potion.Stop();
		activepotion = false;
		potion1efect = false;
		potion3efect = false;
		potion2efect = false;
	}
	if (transformationt.Read() > 500){
		destransformation = false;
		transformationt.Stop();
		

	}
	if ((transformation1 == true || transformation2 == true || transformation3 == true) && transformationt.Read() > 10000){
		transformation1 = false;
		transformation2 = false;
		transformation3 = false;
		destransformation = true;
		transformationt.Start();
		//destran.Start();
		current_animation = &idlesouth;
	}
	return UPDATE_CONTINUE;

}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if ((finished == false) && ((c2->type == COLLIDER_WALL) || (c2->type == COLLIDER_DOOR) || (c2->type == COLLIDER_DOOR2) || (c2->type == COLLIDER_CORNER) || (c2->type == COLLIDER_DESTRUCTIBLE_DOOR) || (c2->type == COLLIDER_ENEMY)))
	{
		//App->particles->AddParticle(explosion, position.x, position.y, COLLIDER_NONE,colisionorientation);

		if (colisionorientation == "A"){
			colisionWEST = true;
			colisionNORTH = false;
			colisionSOUTH = false;
			colisionEAST = false;
			colisionNORTHEAST = false;
			colisionSOUTHWEST = false;
			colisionNORTHWEST = false;
			colisionSOUTHEAST = false;
			
		}
		else if (colisionorientation == "D"){
			colisionEAST = true;
			colisionNORTH = false;
			colisionSOUTH = false;
			colisionWEST = false;
			colisionNORTHEAST = false;
			colisionSOUTHWEST = false;
			colisionNORTHWEST = false;
			colisionSOUTHEAST = false;
		}
		else if ((colisionorientation == "W")){
			colisionNORTH = true;
			colisionSOUTH = false;
			colisionEAST = false;
			colisionWEST = false;
			colisionNORTHEAST = false;
			colisionSOUTHWEST = false;
			colisionNORTHWEST = false;
			colisionSOUTHEAST = false;
		}
		else if (colisionorientation == "S"){
			colisionSOUTH = true;
			colisionNORTH = false;
			colisionEAST = false;
		    colisionWEST = false;
			colisionNORTHEAST = false;
			colisionSOUTHWEST = false;
			colisionNORTHWEST = false;
			colisionSOUTHEAST = false;
		}
		else if (colisionorientation == "NE"){
			colisionNORTHEAST = true;
			colisionSOUTHWEST = false;
			colisionNORTHWEST = false;
		    colisionSOUTHEAST = false;
			colisionSOUTH = false;
			colisionNORTH = false;
			colisionEAST = false;
			colisionWEST = false;
		}
		else if (colisionorientation == "NW"){
			colisionNORTHEAST = false;
			colisionSOUTHWEST = false;
			colisionNORTHWEST = true;
			colisionSOUTHEAST = false;
			colisionSOUTH = false;
			colisionNORTH = false;
			colisionEAST = false;
			colisionWEST = false;
		}
		else if (colisionorientation == "SE"){
			colisionNORTHEAST = false;
			colisionSOUTHWEST = false;
			colisionNORTHWEST = false;
			colisionSOUTHEAST = true;
			colisionSOUTH = false;
			colisionNORTH = false;
			colisionEAST = false;
			colisionWEST = false;
		}
		else if (colisionorientation == "SW"){
			colisionNORTHEAST = false;
			colisionSOUTHWEST = true;
			colisionNORTHWEST = false;
			colisionSOUTHEAST = false;
			colisionSOUTH = false;
			colisionNORTH = false;
			colisionEAST = false;
			colisionWEST = false;
		}
		//App->fade->FadeToBlack((Module*) App->scene_intro, (Module*) App->scene_space, 1.0f);
		//finished = true;
	}
	if (c2->type == COLLIDER_EXIT && finished == false)
	{
		App->audio->PlayFx(fx);

		App->scene_ghost->CleanUp();
		App->scene_ghost->Disable();
		App->scene_ghost_generator->CleanUp();
		App->scene_ghost_generator->Disable();
		App->scene_items->CleanUp();
		App->scene_items->Disable();
		//App->scene_menu->CleanUp();
		App->scene_menu->Disable();
		//App->player->CleanUp();

		App->playerscore = score;

		App->potion1 = potion1;
		App->potion2 = potion2;
		App->potion3 = potion3;
		key = false;
		key2 = false;
		App->player->Disable();

		//App->collision->CleanUp();
		//App->collision->Disable();

	    App->lvl1 = false;
		App->lvl2 = true;
		App->lvl3 = false;
		App->lvl4 = false;
		App->lvl5 = false;

		App->fade->FadeToBlack((Module*)App->scene_level2go, this, 1.0f);

	}if (c2->type == COLLIDER_EXIT3 && finished == false)
	{
		App->audio->PlayFx(fx);

		App->scene_ghost->CleanUp();
		App->scene_ghost->Disable();
		App->scene_ghost_generator->CleanUp();
		App->scene_ghost_generator->Disable();
		App->scene_items->CleanUp();
		App->scene_items->Disable();
		//App->scene_menu->CleanUp();
		App->scene_menu->Disable();
		//App->player->CleanUp();

		App->playerscore = score;

		App->potion1 = potion1;
		App->potion2 = potion2;
		App->potion3 = potion3;
		key = false;
		key2 = false;
		App->player->Disable();

		//App->collision->CleanUp();
		//App->collision->Disable();

		App->lvl1 = false;
		App->lvl2 = false;
		App->lvl3 = true;
		App->lvl4 = false;
		App->lvl5 = false;

		App->fade->FadeToBlack((Module*)App->scene_level3go, this, 1.0f);
	}if (c2->type == COLLIDER_EXIT4 && finished == false)
	{
		App->audio->PlayFx(fx);

		App->scene_ghost->CleanUp();
		App->scene_ghost->Disable();
		App->scene_ghost_generator->CleanUp();
		App->scene_ghost_generator->Disable();
		App->scene_items->CleanUp();
		App->scene_items->Disable();
		//App->scene_menu->CleanUp();
		App->scene_menu->Disable();
		//App->player->CleanUp();

		App->playerscore = score;

		App->potion1 = potion1;
		App->potion2 = potion2;
		App->potion3 = potion3;
		key = false;
		key2 = false;
		App->player->Disable();

		//App->collision->CleanUp();
		//App->collision->Disable();

		App->lvl1 = false;
		App->lvl2 = false;
		App->lvl3 = false;
		App->lvl4 = true;
		App->lvl5 = false;

		App->fade->FadeToBlack((Module*)App->scene_level4go, this, 1.0f);
	}if (c2->type == COLLIDER_EXIT5 && finished == false)
	{
		App->audio->PlayFx(fx);

		App->scene_ghost->CleanUp();
		App->scene_ghost->Disable();
		App->scene_ghost_generator->CleanUp();
		App->scene_ghost_generator->Disable();
		App->scene_items->CleanUp();
		App->scene_items->Disable();
		//App->scene_menu->CleanUp();
		App->scene_menu->Disable();
		//App->player->CleanUp();

		App->playerscore = score;

		App->potion1 = potion1;
		App->potion2 = potion2;
		App->potion3 = potion3;
		key = false;
		key2 = false;
		App->player->Disable();

		//App->collision->CleanUp();
		//App->collision->Disable();

		App->lvl1 = false;
		App->lvl2 = false;
		App->lvl3 = false;
		App->lvl4 = false;
		App->lvl5 = true;

		App->fade->FadeToBlack((Module*)App->scene_level5go, this, 1.0f);
	}
	if (c2->type == COLLIDER_EXIT6 && finished == false)
	{
		App->audio->PlayFx(fx);

		App->scene_ghost->CleanUp();
		App->scene_ghost->Disable();
		App->scene_ghost_generator->CleanUp();
		App->scene_ghost_generator->Disable();
		App->scene_items->CleanUp();
		App->scene_items->Disable();
		//App->scene_menu->CleanUp();
		App->scene_menu->Disable();
		//App->player->CleanUp();

		scores.push_back(score);

		for (int i = 0; i < scores.size(); i++){
			for (int j = 0; j < scores.size() - 1; j++){
				if (scores[j] < scores[j + 1]){
					tm = scores[j];
					scores[j] = scores[j + 1];
					scores[j + 1] = tm;
				}
			}
		}
		
		ofstream logg;
		logg.open("Gauntlet/score.txt");
		logg << scores[0];
		logg << "\n";
		logg << scores[1];
		logg << "\n";
		logg << scores[2];

		logg.close();
		App->potion1 = potion1;
		App->potion2 = potion2;
		App->potion3 = potion3;

		
		App->player->Disable();

		//App->collision->CleanUp();
		//App->collision->Disable();

		App->lvl1 = true;
		App->lvl2 = false;
		App->lvl3 = false;
		App->lvl4 = false;
		App->lvl5 = false;

		App->fade->FadeToBlack((Module*)App->scene_score, this, 1.0f);
	}
	if (c2->type == COLLIDER_ENEMY && finished == false)
	{

		if ((collider == c1))
		{
			App->audio->PlayFx(fxe);

			if (potion3efect == false){
				life = life - 1;
				if (life == 0){
					//App->collision->Disable(); // enable before player

					scores.push_back(score);
					
					for (int i = 0; i < scores.size(); i++){
						for (int j = 0; j < scores.size()-1; j++){
							if (scores[j] < scores[j + 1]){
								tm = scores[j];
								scores[j] = scores[j + 1];
								scores[j + 1] = tm;
							}
						}
					}

					ofstream logg;
					logg.open("Gauntlet/score.txt");
					logg << scores[0];
					logg << "\n";
					logg << scores[1];
					logg << "\n";
					logg << scores[2];
					
					logg.close();

					life = 2;
					App->scene_ghost->CleanUp();
					App->scene_ghost->Disable();
					App->scene_ghost_generator->CleanUp();
					App->scene_ghost_generator->Disable();
					App->scene_items->CleanUp();
					App->scene_items->Disable();
					//App->scene_menu->CleanUp();
					App->scene_menu->Disable();
					//App->player->CleanUp();

					App->playerscore = score;
					
					
					

					App->player->Disable();
					
					//App->collision->CleanUp();
					//App->collision->Disable();

					
					
					App->fade->FadeToBlack((Module*)App->scene_score, this, 1.0f);
				}
			}
		}
	}

	
}

void ModulePlayer::OnNotCollision(Collider* c1, Collider* c2)
{	
				
	
}