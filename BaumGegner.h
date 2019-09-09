#pragma once
#include "Enemy.h"
class BaumGegner : public Enemy
{
public:

	BaumGegner(sf::Vector2f spawnPos,const sf::Texture *texture);
	~BaumGegner();

	void initAnimation(const sf::Texture * tex);

	void update(sf::Time _elapsed, sf::Vector2f ownerpos);
	void draw(sf::RenderWindow &window) override;
	void updateAnimation();

	

};

