#pragma once
#include "Entity.h"


//enum class eAnimation { WALKDOWN, WALKLEFT, WALKRIGHT, WALKUP, ATTACKDOWN, ATTACKLEFT, ATTACKRIGHT, ATTACKUP };


class Enemy : public Entity
{
	


public:
	Enemy();
	~Enemy();

	//void update(sf::Time _elapsed, sf::Vector2f ownerpos);
	void update_row();
	void init();
	sf::Vector2f calculate_velocity(sf::Vector2f targetpos);
void Enemy::set_Spawn_Area(sf::Vector2i const & pos, int fieldsize);

	//komm in der schleife nicht von entitiy auf enemy
	//entweder die vars und funktionen in entitiy verschieben
	//oder c+ lernen )/
	
	//noch in cpp rein machen
	


	
};

