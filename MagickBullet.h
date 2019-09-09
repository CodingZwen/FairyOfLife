#pragma once
#include "Entity.h"
#include <list>
class MagickBullet : public Entity
{
	float angle=0;
	enum TYPE {PSY,FIRE};
	

public:
	MagickBullet(int _atk,float angle, sf::Vector2f Spawnpos, sf::Texture *texture=nullptr);
	~MagickBullet();

	void MagickBullet::update(sf::Time _elapsed,sf::Vector2f ownerpos);
	void draw(sf::RenderWindow &window);
	void MagickBullet::hurt(int dmg) {};

	void initAnimation(sf::Texture *texture);

};


/*
#define W 1280
#define H 720
= 0.017453f

*/