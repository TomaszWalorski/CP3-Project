#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <time.h>
#include "object.h"
#include "box.h"
#include "flor.h"
#include "wall.h"
#include "player.h"
#include "key.h"
#include "door.h"
#include "enemy.h"
#include "purpose.h"
#include "bullet.h"
#include "gun.h"
#include "active_obj.h"
#include "static_obj.h"


class dataset
{
private:
	std::vector <std::vector <char> > tab_so;
	std::vector <std::vector <object *> > aop_so;
	std::vector <std::vector <char> > tab_ao;
	std::vector <std::vector <object *> > aop_ao;
	box *b;
	wall *w;
	flor *f;
	player p;
	key k;
	enemy e;
	door d;
	gun g;
	bullet bu;
	purpose *pu;
	int x, y, xp, yp;
	int xe, ye;

public:

    void move(int varx, int vary, bool &condition, int &nr_2);
	void move_enemy(int varx, int vary, bool &condition);
	void move_bullet(int varx, int vary, bool &condition);
	void tester();
	void showset(int nr_1, int &nr_2, time_t t);
	void update();
	void take_key();
	void open_door();
	void gameover(bool &condition);
	bool state_of_enemy();
	void shot(int counter);
	dataset();

};
