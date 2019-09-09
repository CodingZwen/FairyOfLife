#include "Schmetterling.h"




void Schmetterling::initVariables()
{
	direction = 0;
}

void Schmetterling::initComponents()
{
}

void Schmetterling::initAnimation(sf::Texture & texture)
{


	int spritex = 16;
	int spritey = 32;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), 3, texture, "FLYING_UP");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey, spritex, spritey), 3, texture, "FLYING_DOWN");

	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 2, spritex, spritey), 3, texture, "FLYING_LEFT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 3, spritex, spritey), 3, texture, "FLYING_RIGHT");

	animatedSprite.setCurrentAnimation("FLYING_UP");

	animatedSprite.setFrameTime(sf::seconds(static_cast<float>(0.2)));
	

}

Schmetterling::Schmetterling(sf::Vector2f spawnPos, sf::Texture * tex)
{
	this->initAnimation(*tex);
	createMovementComponent(100.f, 10.f, 5.f);
	initVariables();
	movementComponent->setPosition(spawnPos);
}

Schmetterling::~Schmetterling()
{
}

void Schmetterling::flyAround(sf::Time elapsed)
{
	this->elapsed+= elapsed;
	
	if (this->elapsed.asSeconds() > 3)
	{
		direction = rand() % 5 + 1;
		this->elapsed = this->elapsed.Zero;
	}

	if (direction == 1)
	{
		moveUp(elapsed);

	}
	else if (direction == 2)
	{
		moveDown(elapsed);


	}
	else if (direction == 3)
	{

		moveLeft(elapsed);

	}
	else if (direction == 4)
	{

		moveRight(elapsed);

	}
	else {

		
	}

	switch (direction)
	{
	case 1: animatedSprite.setCurrentAnimation("FLYING_UP"); break;
	case 2:	animatedSprite.setCurrentAnimation("FLYING_DOWN"); break;
	case 3: animatedSprite.setCurrentAnimation("FLYING_LEFT"); break;
	case 4: animatedSprite.setCurrentAnimation("FLYING_RIGHT"); break;
	default:break;
	}



	
}

void Schmetterling::update(sf::Time elapsed, sf::Vector2f ownerPos)
{

	flyAround(elapsed);

	if (this->movementComponent)
	{
		this->movementComponent->update(elapsed.asSeconds());

	}

	animatedSprite.play();
	animatedSprite.update(elapsed);

}

void Schmetterling::draw(sf::RenderWindow & target)
{
	target.draw(animatedSprite);
}
