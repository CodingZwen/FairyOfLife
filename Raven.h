#pragma once
#include "Entity.h"
class Raven :
	public Entity
{

	void initVariables();
	void initComponents();

	void initAnimation(const sf::Texture *spriteSheet);

	sf::Time kaTimer;

	float lifeTime;
	float timeToDie;

public:
	Raven(sf::Vector2f spawnPos, sf::Texture *tex, float timeTodie=7.f);
	virtual ~Raven();

	void flyAround(sf::Time elapsed);


	void update(sf::Time elapsed, sf::Vector2f ownerPos);
	void draw(sf::RenderWindow &window);


};

