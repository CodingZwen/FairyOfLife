#include "Raven.h"




Raven::Raven(sf::Vector2f spawnPos, sf::Texture * tex, float timeTodie)
{
	this->initAnimation(tex);
	createMovementComponent(150.f, 20.f, 10.f);
	initVariables();
	movementComponent->setPosition(spawnPos);
	this->timeToDie = timeTodie;
	name = "Raven";
	
	
}

Raven::~Raven()
{
}


void Raven::initVariables()
{
	direction = 0;
	id = 8; //genesis acht kapitel 6-7 noah lässt seinen raben schauen obs land gibt
}

void Raven::initComponents()
{
}

void Raven::initAnimation(const sf::Texture * texture)
{

	int spritex = 16;
	int spritey = 16;
	int picCount = 4;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), picCount, *texture, "FLYING_UP");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey, spritex, spritey), picCount, *texture, "FLYING_DOWN");

	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 2, spritex, spritey), picCount, *texture, "FLYING_LEFT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 3, spritex, spritey), picCount, *texture, "FLYING_RIGHT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 4, spritex, spritey), picCount, *texture, "STANDING");

	animatedSprite.setCurrentAnimation("FLYING_UP");

	animatedSprite.setFrameTime(sf::seconds(0.2));

}

void Raven::flyAround(sf::Time elapsed)
{
	this->elapsed += elapsed;

	if (this->elapsed.asSeconds() > 5)
	{
		direction = rand() % 10 + 1;
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
	case 2: animatedSprite.setCurrentAnimation("FLYING_DOWN"); break;
	case 3: animatedSprite.setCurrentAnimation("FLYING_LEFT"); break;
	case 4: animatedSprite.setCurrentAnimation("FLYING_RIGHT"); break;
	default:animatedSprite.setCurrentAnimation("STANDING");

		break;
	}

}

void Raven::update(sf::Time elapsed, sf::Vector2f ownerPos)
{
	//flyAround(elapsed);
	lifeTime += elapsed.asSeconds();
	FollowAndAttackEnemy(elapsed, ownerPos);

	if (this->movementComponent)
	{
		this->movementComponent->update(elapsed.asSeconds());

	}

	animatedSprite.play();
	animatedSprite.update(elapsed);


	if (lifeTime > timeToDie) life = false;



}

void Raven::draw(sf::RenderWindow & window)
{
	window.draw(animatedSprite);
}
