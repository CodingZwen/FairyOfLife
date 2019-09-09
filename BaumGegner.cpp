#include "BaumGegner.h"



BaumGegner::BaumGegner(sf::Vector2f spawnPos, const  sf::Texture *tex)
{
	name = "baum";

	if (tex)initAnimation(tex);

	animatedSprite.setPosition(spawnPos);
	attacktimer = 0;
	attributs.setAtk(5);
	attributs.setHp(100);
	havetarget = 0;
	collide = false;
	id = 3;
	
	int randomSpeed = rand() % 80 + 60;
	//this->initAnimation(tex);

	createMovementComponent(static_cast<float>(randomSpeed), 20.f, 15.f);
	hpbar.init(32, 2, 2);
}


BaumGegner::~BaumGegner()
{
}

void BaumGegner::initAnimation(const sf::Texture * texture)
{
	int spritex = 64;
	int spritey = 64;
	int picCount = 7;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), picCount, *texture, "WALKING_DOWN");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey, spritex, spritey), picCount, *texture, "WALKING_UP");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 2, spritex, spritey), picCount, *texture, "WALKING_LEFT");

	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 3, spritex, spritey), picCount, *texture, "WALKING_RIGHT");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 4, spritex, spritey), picCount, *texture, "SPAWNANIMATION");
	animatedSprite.insertAnimation(sf::IntRect(0, spritey * 5, spritex, spritey), picCount, *texture, "STANDING");
	

	animatedSprite.setCurrentAnimation("SPAWNANIMATION");
	animatedSprite.setOrigin(spritex / 2, spritey / 2);
	animatedSprite.setFrameTime(sf::seconds(0.2f));

}

void BaumGegner::update(sf::Time _elapsed, sf::Vector2f playerpos)
{
	invicibletimer += _elapsed.asSeconds();
	attacktimer += _elapsed.asSeconds();

	WatchAndFollow(_elapsed, playerpos,500.f);

	//printf("velox: %f veloy: %f\n", movementComponent->getVelocity().x, movementComponent->getVelocity().y);

	if (this->movementComponent)
	{
		this->movementComponent->update(_elapsed.asSeconds());
	

	}

	animatedSprite.play();
	animatedSprite.update(_elapsed);
	updateAnimation();

	if (!attributs.isalive())life = false;
	//anim.sprite.setPosition(x, y);
	
	//hpbar.update(movementComponent->getPosition(), attributs.getHpAsPercent());
	hpbar.update(movementComponent->getPosition(), attributs.getHpAsPercent());



}

void BaumGegner::draw(sf::RenderWindow & window)
{
	window.draw(animatedSprite);
	hpbar.draw(window);

}

void BaumGegner::updateAnimation()
{

	if (animatedSprite.firstAnimationDone())
	{

		if (movementComponent->getStates(MOVING_UP))
			animatedSprite.setCurrentAnimation("WALKING_UP");
		else if (movementComponent->getStates(MOVING_DOWN))
			animatedSprite.setCurrentAnimation("WALKING_DOWN");
		else if (movementComponent->getStates(MOVING_LEFT))
			animatedSprite.setCurrentAnimation("WALKING_LEFT");
		else if (movementComponent->getStates(MOVING_RIGHT))
			animatedSprite.setCurrentAnimation("WALKING_RIGHT");
		else if (movementComponent->getStates(STANDING))
			animatedSprite.setCurrentAnimation("STANDING");
		
	}

	
}




