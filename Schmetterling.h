#pragma once
#include "Entity.h"
class Schmetterling :
	public Entity
{
private:
	void initVariables();
	void initComponents();

	void initAnimation(sf::Texture &tex);

	sf::Time DirectionTimer;


public:
	Schmetterling(sf::Vector2f spawnPos, sf::Texture *tex);
	virtual ~Schmetterling();

	void flyAround(sf::Time elapsed);

	void update(sf::Time elapsed, sf::Vector2f ownerPos);
	void draw(sf::RenderWindow & target);
};

