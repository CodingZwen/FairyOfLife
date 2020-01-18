#pragma once
#include <iostream>
#include "tinystr.h"
#include "tinyxml.h"
#include "Item.h"
#include <string>



class SaveLoadGameXML
{
	


public:
	SaveLoadGameXML();
	~SaveLoadGameXML();

	
	void createSaveFile(const char *playername, int posx, int posy, int level, int money,
		int xp,std::vector<Item> &items);

	void loadSavefile(std::string &playername, int &posx, int &posy, int &level, int &money,
		int &xp, std::vector<Item> &items,
		sf::Sprite &Itemsprite,sf::Font *font, std::string savefilepath);

};

