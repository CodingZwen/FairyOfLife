#pragma once
#include "Entity.h"
class MagickBlizzard : public Entity
{

	sf::Vector2f _mousepos;
	bool moving = false;

public:
	MagickBlizzard();
	~MagickBlizzard();

	void activate() { moving = false; }
	void update(sf::Time _elapsed, sf::Vector2f ownerpos);
	void draw(sf::RenderWindow &window);

	void initAnimation(const sf::Texture *texture);

};

