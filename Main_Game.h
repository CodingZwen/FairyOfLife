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

#include "FileMaker.h"

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

	template<class T>
	T getBytesAs(std::vector<unsigned char> bytes);


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

template<class T>
inline T Main_Game::getBytesAs(std::vector<unsigned char> bytes)
{

	unsigned char code[4];
	T foo;
	code[0] = bytes.at(0);
	code[1] = bytes.at(1);
	code[2] = bytes.at(2);
	code[3] = bytes.at(3);

	//11111111 00000000 0000000 0000000
	
	foo = (T)code[0] << 24;
	//00000000 11111111 0000000 0000000
	foo |= (T)code[1] << 16;
	//00000000 00000000 1111111 0000000
	foo |= (T)code[2] << 8;
	//00000000 00000000 0000000 1111111
	foo |= (T)code[3];


	return foo;
}
