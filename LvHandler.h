#pragma once
#include "Map.h"
#include <map>
#include "AssetManager.h"



enum class eMaps { start, Mountain, Desert, DesertBossGround,Town, potionshop,BossGround };


class LvHandler
{
		
	unsigned int MapCount;
	unsigned int CurrentLevelNumber;
	
	

	std::map<std::string, Map> maps;

	Map CurrentLevel;


public:
	LvHandler();
	~LvHandler();

	//void LoadMap(std::string name, std::string filename);
	void InitLevels(AssetManager *Assetm);
	//tilemap with collission so ändern das sie einen pointer hat 
	//dann kann ich hier die current map versschieben und auch dementsprechend verändern im lvhaendler laos hier
	Map  &getLevel(std::string LevelName);
	Map const &GetCurrentLevel();

	eMaps ECurrentLevel;

};

