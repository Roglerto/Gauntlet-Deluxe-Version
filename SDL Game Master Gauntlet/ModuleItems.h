#ifndef __MODULEITEMS_H__
#define __MODULEITEMS_H__

#include "Module.h"
#include "Animation.h"
#include <list>
#include <vector>
#include "Point.h"
#include "Timer.h"
#include <string>
struct SDL_Texture;
struct Collider;

using namespace std;

enum item_type
{
	TREASURE,
	FOOD,
	POTION1,
	POTION2,
	POTION3,
	KEY,
	KEY2,
	DOOR,
	DOOR2,
	DESTRUCTIBLE_DOOR,
	EXIT,
	EXIT3,
	EXIT4,
	EXIT5,
	EXIT6
};

struct items{
	iPoint position;
	Collider* collider = nullptr;
	Animation animation;
	item_type type;
	
	SDL_Rect pos;

	int score=0;
	int life = 0;
	bool key2 = false;
	bool key = false;
	bool potion1 = false;
	bool potion2 = false;
	bool potion3 = false;

	items();
	 ~items();
};

struct Treasure : public items{
	
	Treasure();
	~Treasure();
};
struct Food : public items{

	Food();
	~Food();
};

struct Potion1 : public items{
		

	Potion1();
	~Potion1();
};

struct Exit : public items{


	Exit();
	~Exit();
};

struct Exit3 : public items{


	Exit3();
	~Exit3();
};
struct Exit4 : public items{


	Exit4();
	~Exit4();
};
struct Exit5 : public items{


	Exit5();
	~Exit5();
};
struct Exit6 : public items{


	Exit6();
	~Exit6();
};
struct Potion2 : public items{


	Potion2();
	~Potion2();
};

struct Potion3 : public items{


	Potion3();
	~Potion3();
};

struct Key : public items{
	

	Key();
	~Key();
};
struct Key2 : public items{


	Key2();
	~Key2();
};
struct Door : public items{


	Door();
	~Door();
};
struct Door2 : public items{


	Door2();
	~Door2();
};
struct Destructible_Door : public items{


	Destructible_Door();
	~Destructible_Door();
};

class ModuleItems : public Module
{
public:
	ModuleItems(bool start_enabled = true);
	~ModuleItems();

	void additems(item_type type,int x, int y);
	void OnCollision(Collider* c1, Collider* c2);
	void deletedoors();
	void deletedoors2();
	void doorexplosion(int x, int y);

	bool Start();
	bool CleanUp();
	update_status Update();

	Timer timeexplosion;
	Timer timedor;
	Animation explosionani;
	Animation explosionkey;
	Animation destructible_dor;
	bool explo = false;
	bool explodoor = false;
	bool explodoor2 = false;
	bool deletedoor = false;
	iPoint posexplosion;
	iPoint dorexplosion;

	vector<iPoint> door;
	vector<iPoint> door2;
	SDL_Texture* image;
	uint fx = 0;
	list<items*> itemlist;
};



#endif