#pragma once
#include "Enemy.h"
class SteinGolem : public Enemy 
{
public:
	SteinGolem(sf::Vector2f spawnPos,sf::Texture *texture);
	virtual ~SteinGolem();

	void update(sf::Time _elapsed, sf::Vector2f ownerpos);
	void draw(sf::RenderWindow &window);
	void initAnimation(sf::Texture *tex);
};

