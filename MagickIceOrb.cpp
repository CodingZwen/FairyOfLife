#include "MagickIceOrb.h"



MagickIceOrb::MagickIceOrb(short atk, short _lifetime,   Entity *ownerEntity
	, sf::Texture *texture)
{

	this->lifetime = _lifetime;

	if (ownerEntity)
	{
		setTarget(ownerEntity);
	}

	if (texture)initAnimation(texture);


	attributs.setAtk(atk);
	name = "iceorb";

	id = 32;

	createMovementComponent(static_cast<float>(100), 20.f, 15.f);
	

}


MagickIceOrb::~MagickIceOrb()
{
}

void MagickIceOrb::update(sf::Time _elapsed, sf::Vector2f ownerpos)
{

	elapsed += _elapsed;

	if (!ownerEntity)
	{
		float _x = ownerpos.x + 18 + cos(angle) * 50; //radius ist letzter param
		float _y = ownerpos.y + 22 + sin(angle) * 50;
		angle += _elapsed.asSeconds()*6;

		movementComponent->setPosition(sf::Vector2f(_x, _y));

		if (elapsed.asSeconds() > lifetime) { life = false; }


		//vielleicht könnte man hier die umdrehungen zählen und anhand dessen löschen
		//dann könnten wir uns eigentlich die zeit sparen
		if (angle > 360)angle = 0;
	}


	animatedSprite.play();
	animatedSprite.update(elapsed);

}

void MagickIceOrb::draw(sf::RenderWindow & window)
{
	window.draw(animatedSprite);
}

void MagickIceOrb::initAnimation(sf::Texture * texture)
{
	int spritex = 32;
	int spritey = 32;
	int picCount = 5;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), picCount, *texture, "FLYING");

	animatedSprite.setCurrentAnimation("FLYING");

	animatedSprite.setFrameTime(sf::seconds(0.2f));

	animatedSprite.setOrigin(spritex / 2.f, spritey / 2.f);
}
