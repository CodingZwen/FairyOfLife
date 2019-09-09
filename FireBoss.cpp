#include "FireBoss.h"



FireBoss::FireBoss()
{
	name = "Fireboss";

	attacktimer = 0;
	attributs.setAtk(50);
	havetarget = 0;
	attributs.setHp(100);
	collide = false;
	id = 33;
	hpbar.init(32, 2, 10);
	createMovementComponent(100, 10.f, 5.f);

	
}


FireBoss::~FireBoss()
{
}

void FireBoss::update(sf::Time _elapsed, sf::Vector2f playerpos)
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
	

	if (!attributs.isalive())life = false;
	//anim.sprite.setPosition(x, y);

	//hpbar.update(movementComponent->getPosition(), attributs.getHpAsPercent());
	hpbar.update(movementComponent->getPosition(), attributs.getHpAsPercent());



}
