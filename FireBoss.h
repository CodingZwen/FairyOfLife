#pragma once
#include "Enemy.h"
class FireBoss : public Enemy
{
public:
	FireBoss();
	~FireBoss();

	void update(sf::Time _elapsed, sf::Vector2f ownerpos);

};

