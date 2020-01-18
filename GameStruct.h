#pragma once
#include <vector>
#include <string>
#include "Item.h"


using namespace std;


struct player
{

	int x, y, money, xp;
	int level;
	string name;


	player() {
		x = 0, y = 0;
		level = 10;
		name = "playername";
		money = 1337;
	}


	void setplayerstats(int x, int y, int level, int money)
	{

		this->x = x;
		this->y = y;
		this->level = level;
		this->money = money;
	}

	const int getX()const { return x; }
	const int getY()const { return y; }
	const int getLevel()const { return level; }
	const string &getnameS() const { return name; }
	const char *getname() const { return name.c_str(); }
	const int getMoney()const { return money; }
	const unsigned int getXP() const { return xp; }

};



class GameStruct
{


public:
	GameStruct();
	~GameStruct();

	
};





