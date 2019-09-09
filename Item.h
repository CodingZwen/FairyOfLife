#pragma once
#include "SFML/Graphics.hpp"

namespace SVEN 
{

	enum EquipType { Sword, Shield,
	Head, Chest, Boots, 
	Amulet, Ring1,Ring2  };

class Item
{


	sf::Sprite *itemSprite = nullptr;
	sf::FloatRect itemSpriteRect;
	sf::RectangleShape textBackground;
	sf::Text itemName;
	sf::Text itemDescription; //stats etc

	sf::Vector2f velocity;

public:
	Item(unsigned int ID, short atk, short def, short speed, short iq,
		sf::Vector2f spawnPos,	sf::Sprite *spr,sf::Font *font);
	~Item();


	void update(sf::Time elapsed);
	void draw(sf::RenderTarget &target);

};


}