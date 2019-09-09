#include "MagickBullet.h"



MagickBullet::MagickBullet(int _atk, float _angle, sf::Vector2f Spawnpos, sf::Texture *texture)
{

	if (texture)initAnimation(texture);
	name = "bullet";
	attributs.setAtk(_atk);
	angle = _angle;
	id = 20;
	createMovementComponent(180.f , 10, 5);
	movementComponent->setPosition(Spawnpos);
	animatedSprite.setRot(_angle+90);

	float dx = cos(angle*RADIANT) * 200; //bei 0 also nach rechts kommt hier cos =1 raus
	float dy = sin(angle*RADIANT) * 200; //hier kommt bei angle 0, also sin 0 = 0 raus deswegen nach rechts	

	movementComponent->lockedVelocity = sf::Vector2f(dx, dy);

}


MagickBullet::~MagickBullet()
{
}




void MagickBullet::update(sf::Time _elapsed,sf::Vector2f ownerpos)
{
	elapsed += _elapsed;	
		
		movementComponent->moveWithoutAcceleration(movementComponent->lockedVelocity, _elapsed.asSeconds());
	//	movementComponent->update(_elapsed.asSeconds());
		

		if (elapsed.asSeconds() > 5)kill();

		animatedSprite.play();
		animatedSprite.update(elapsed);	
}

void MagickBullet::draw(sf::RenderWindow & window)
{
	window.draw(animatedSprite);
}

void MagickBullet::initAnimation(sf::Texture * texture)
{

	int spritex = 32;
	int spritey = 32;
	int picCount = 16;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), picCount, *texture, "FLYING");


	animatedSprite.setCurrentAnimation("FLYING");

	animatedSprite.setFrameTime(sf::seconds(0.2f));


}


