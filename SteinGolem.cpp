#include "SteinGolem.h"



SteinGolem::SteinGolem(sf::Vector2f spawnPos, sf::Texture *texture)
{

	if (texture)initAnimation(texture);
	
	name = "golem";
	animatedSprite.setPosition(spawnPos);

	attacktimer = 0;
	attributs.setAtk(5);
	attributs.setHp(100);
	hpbar.init(32, 2, 2);
	id = 1;
	createMovementComponent(100, 10.f, 5.f);
	

	
}


SteinGolem::~SteinGolem()
{
}

void SteinGolem::update(sf::Time _elapsed, sf::Vector2f playerpos)
{

	invicibletimer += _elapsed.asSeconds();
	attacktimer += _elapsed.asSeconds();

	WatchAndFollow(_elapsed, playerpos, 500.f);

	//printf("velox: %f veloy: %f\n", movementComponent->getVelocity().x, movementComponent->getVelocity().y);

	if (this->movementComponent)
	{
		this->movementComponent->update(_elapsed.asSeconds());


	}

	animatedSprite.play();
	animatedSprite.update(_elapsed);
	//updateAnimation();

	if (!attributs.isalive())life = false;
	//anim.sprite.setPosition(x, y);

	//hpbar.update(movementComponent->getPosition(), attributs.getHpAsPercent());
	hpbar.update(movementComponent->getPosition(), attributs.getHpAsPercent());



}

void SteinGolem::draw(sf::RenderWindow & window)
{
	window.draw(animatedSprite);
	hpbar.draw(window);
}

void SteinGolem::initAnimation(sf::Texture *texture)
{
	int spritex = 32;
	int spritey = 32;
	int picCount = 3;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), picCount, *texture, "WALKING_UP");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey, spritex, spritey), picCount, *texture, "WALKING_DOWN");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 2, spritex, spritey), picCount, *texture, "WALKING_LEFT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 3, spritex, spritey), picCount, *texture, "WALKING_RIGHT");
	

	animatedSprite.setCurrentAnimation("WALKING_UP");

	animatedSprite.setFrameTime(sf::seconds(0.2f));

}
