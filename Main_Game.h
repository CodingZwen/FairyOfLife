#pragma once


#include "AssetManager.h"
#include "LvHandler.h"
#include "Gamestate.h"
#include "Player.h"
#include "Game.h"
#include "GUI.h"
#include "Items.h"
#include "Weather.h"

#include "Tilemap_with_Collision.h"


#include "MagickBullet.h"
#include "MagickIceOrb.h"
#include "MagickBlizzard.h"

#include "PlayerWeapon.h"
#include "EntityHandler.h"
#include "TextHandler.h"
#include "SoundHandler.h"

#include "BENCHMARK.h"

class Main_Game : public Gamestate
{
public:
	Main_Game(sf::Vector2i screenDimensions);
	~Main_Game();
	
	void HandleEvents(Game &game);
	void Update(Game &game);
	void Draw(Game &game); 


	void changeLevelExtended();
	

	void handle_menues(sf::Event e);
	void handle_items(Game &game);
	void handle_player(Game &game);
	void handlePlayerInput(Game &game);


	sf::Vector2i mousepos;
	
	bool showskills = false;
	bool skillmenueisactiv = false;


	int choosenspell = 0;
	bool activatecollision = false;

	


private: 

	SoundHandler sh;
	Tilemap_with_Collision TileMapPainter;
	EntityHandler eh;
	AssetManager assetmanager;
	LvHandler lvhandler;
	TextHandler TextManager;
	
	sf::Vector2i camerapos;
	int xp = 0;
	 


	bool showinventory = false;
	bool showequip = false;
	bool bweather_on = false;
	
	std::unique_ptr<Weather> wetter;
	
	
	
	Items items;
	
	std::shared_ptr<Player> Spieler1;

		
	sf::View view;

	GUI gui;

	
	Animation *Blizzard;
	Animation *AWeaponset;

	MagickBlizzard *ptr_magickblizzard;
	//
	PlayerWeapon* wp;


};





/*

for (list<Object*>::const_iterator iter = this->objectlist.begin(),
end = this->objectlist.end();
iter != end;
++iter)
{
(*iter)->print();
}
*/