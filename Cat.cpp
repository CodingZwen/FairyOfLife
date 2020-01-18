#include "Cat.h"




Cat::Cat(sf::Vector2f spawnPos, sf::Texture *tex)
{
	float randomSpeed = rand() % 150 + 100;
	this->initAnimation(tex);

	createMovementComponent(randomSpeed, 10.f, 5.f);

	initVariables();
	movementComponent->setPosition(spawnPos);
}


void Cat::initVariables()
{
	direction = 0;
}

void Cat::initComponents()
{
}

void Cat::initAnimation(const sf::Texture * texture)
{

	int spritex = 22;
	int spritey = 20;
	int picCount = 6;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), picCount, *texture, "WATCH_AROUND_LEFT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey, spritex, spritey), picCount, *texture, "SITTING_LEFT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 2, spritex, spritey), picCount, *texture, "RUNNING_LEFT");

	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 3, spritex, spritey), picCount, *texture, "WATCH_AROUND_RIGHT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 4, spritex, spritey), picCount, *texture, "SITTING_RIGHT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 5, spritex, spritey), picCount, *texture, "RUNNING_RIGHT");

	animatedSprite.setCurrentAnimation("WATCH_AROUND_LEFT");

	animatedSprite.setFrameTime(sf::seconds(static_cast<float>(0.2)));
	this->id = 99;
}

Cat::~Cat()
{
}

void Cat::walkAround(sf::Time elapsed)
{
	this->elapsed += elapsed;

	if (this->elapsed.asSeconds() > 5)
	{
		direction = rand() % 10 + 3;
		this->elapsed = this->elapsed.Zero;
	}

	
	 if (direction == 3)
	{

		moveLeft(elapsed);

	}
	else if (direction == 4)
	{

		moveRight(elapsed);

	}
	else {


	}


	
}

void Cat::update(sf::Time elapsed, sf::Vector2f playerpos)
{

	//walkAround(elapsed);

	WatchAndFollow(elapsed, playerpos);

	if (this->movementComponent)
	{
		this->movementComponent->update(elapsed.asSeconds());
		updateAnimation();
		
	}

	//cout << "caty: " << movementComponent->getPosition().y << endl;

	animatedSprite.play();
	animatedSprite.update(elapsed);
}

void Cat::draw(sf::RenderWindow & window)
{
	window.draw(animatedSprite);
}

void Cat::updateAnimation()
{
	if(movementComponent->getStates(MOVING_LEFT))
		animatedSprite.setCurrentAnimation("RUNNING_LEFT");
	else if(movementComponent->getStates(MOVING_UP))
		animatedSprite.setCurrentAnimation("RUNNING_RIGHT");
	else if(movementComponent->getStates(STANDING))
		animatedSprite.setCurrentAnimation("SITTING_LEFT");



}
