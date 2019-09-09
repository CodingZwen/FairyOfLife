#include "Entity.h"
#pragma once
class MagickIceOrb : public Entity
{

	Entity *ownerEntity = nullptr;
	short lifetime = 10;
	float angle = 0;
public:

	MagickIceOrb(short atk, short lifetime,  Entity *ownerEntity = nullptr,
		sf::Texture *texture= nullptr);

	virtual ~MagickIceOrb();

	void update(sf::Time _elapsed,sf::Vector2f ownerpos);
	void draw(sf::RenderWindow &window);
	void hurt(int dmg) {};

	
	void initAnimation(sf::Texture *texture);

};

