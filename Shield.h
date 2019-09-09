#pragma once
#include <SFML\Graphics.hpp>

class Shield
{
public:
	Shield();
	~Shield();


	void init();
	void update(int dir, sf::Vector2f playerpos, bool defending);
	void draw(sf::RenderTarget &target);


	sf::Sprite shieldsprite;
	sf::Texture *texture;

};

