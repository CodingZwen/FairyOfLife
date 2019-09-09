#include "LvHandler.h"



LvHandler::LvHandler()
{
}


LvHandler::~LvHandler()
{
}

void LvHandler::InitLevels(AssetManager * Assetm)
{

	std::string sMountainTMXFilePath = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\Mountain.tmx";
	std::string sPotionShopTMXFilePath = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\room.tmx";
	std::string sHomelandFilePath = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\Homeland.tmx";
	std::string sDesertFilePath = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\desert.tmx";
	std::string sDesertBossFilePath = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\desertboss.tmx";
	std::string sTownFilePath = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\town1.tmx";
	std::string sBossGroundFilePath = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\BossGround.tmx";



	Map lvMountain;
	Map lvPotionShop;
	Map lvHomeland;
	Map lvDesert;
	Map lvDesertBoss;
	Map lvTown;
	Map lvBossGround;

	if (lvMountain.initalize_map_from_tmx(sMountainTMXFilePath, Assetm->GetTexture("world2"), 768, 40, 30))
	{
		this->maps["Mountain"] = lvMountain;
	}
	else {
	
	
	}

	if (lvPotionShop.initalize_map_from_tmx(sPotionShopTMXFilePath, Assetm->GetTexture("house1"), 512, 16, 12))
	{
		this->maps["PotionShop"] = lvPotionShop;
	}

	if (lvHomeland.initalize_map_from_tmx(sHomelandFilePath, Assetm->GetTexture("world2"), 768, 40, 30))
	{
		this->maps["Homeland"] = lvHomeland;
	}

	if (lvDesert.initalize_map_from_tmx(sDesertFilePath, Assetm->GetTexture("world2"), 768, 40, 30))
	{
		this->maps["Desert"] = lvDesert;
	}


	if (lvDesertBoss.initalize_map_from_tmx(sDesertBossFilePath, Assetm->GetTexture("world2"), 768, 40, 30))
	{
		this->maps["DesertBoss"] = lvDesertBoss;
	}


	if (lvTown.initalize_map_from_tmx(sTownFilePath, Assetm->GetTexture("world2"), 768, 40, 30))
	{
		this->maps["Town"] = lvTown;
	}

	if (lvBossGround.initalize_map_from_tmx(sBossGroundFilePath, Assetm->GetTexture("world"), 576, 40, 30))
	{
		this->maps["BossGround"] = lvBossGround;
	}




	ECurrentLevel = eMaps::Mountain;


}

Map  &  LvHandler::getLevel(std::string LevelName)
{
	// TODO: hier Rückgabeanweisung eingeben
	std::map< std::string, Map >::iterator it;
	it = maps.find(LevelName);

	if (it != maps.end()) {

	
		return this->maps.at(LevelName);
	}
	else {
		it = maps.begin();
		//wenn karte nicht gefunden gib ersstes level zurueck
		return it->second;
	}



}

Map const & LvHandler::GetCurrentLevel()
{
	Map map;
	// TODO: hier Rückgabeanweisung eingeben
	return map;
}




/*
old initalisation in main game with string with path


	std::string tmx = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\room.tmx";
	std::string tmx2 = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\new_world.tmx";
	std::string tmx3 = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\upscroller.tmx";
	std::string lvend = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\dungeonet1.tmx";

	std::string lvtown = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\town.tmx";
	std::string lv2 = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\Brunnenvorhof.tmx";
	std::string lv3 = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\DungeonEntrance.tmx";
	std::string lv1 = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\StartGebiet.tmx";
	std::string lvMountain = "Spiel_Projekt_Protectyourisle_Assets\\Maps\\Mountain.tmx";


	lvstart.initalize_map_from_tmx(lv1, assetmanager.GetTexture("world"), 576, 40, 40);
	lvbrunnen.initalize_map_from_tmx(lv2, assetmanager.GetTexture("world"), 576, 40, 40);
	lvdungeoneingang.initalize_map_from_tmx(lv3, assetmanager.GetTexture("world"), 576, 40, 40);
	lvstadt.initalize_map_from_tmx(lvtown, assetmanager.GetTexture("world"), 576, 40, 40);
	lvdungeon.initalize_map_from_tmx(lvend, assetmanager.GetTexture("world"), 576, 40, 40);
	mountain.initalize_map_from_tmx(lvMountain, assetmanager.GetTexture("world2"), 608, 40, 30);


	Worldmap.initalize_map_from_tmx(tmx2, assetmanager.GetTexture("world"), 576, 200, 200);
	Upscrollmap.initalize_map_from_tmx(tmx3, assetmanager.GetTexture("world"), 576, 40, 180);
	Potionshop.initalize_map_from_tmx(tmx, assetmanager.GetTexture("house1"), 512, 16, 12);


*/