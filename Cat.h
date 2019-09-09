#include "Entity.h"
#pragma once
class Cat : public Entity
{

	void initVariables();
	void initComponents();

	void initAnimation(const sf::Texture *spriteSheet);

	sf::Time kaTimer;

	

public:
	Cat(sf::Vector2f spawnPos, sf::Texture *tex);
	virtual ~Cat();

	void walkAround(sf::Time elapsed);

	void update(sf::Time elapsed, sf::Vector2f ownerPos);
	void draw(sf::RenderWindow &window);
	void updateAnimation();

};

