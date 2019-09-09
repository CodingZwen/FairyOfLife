#include "MagickBlizzard.h"



MagickBlizzard::MagickBlizzard()
{
	name = "blizzard";
	attributs.setAtk(50);
	moving = true;
	id = 88;
}


MagickBlizzard::~MagickBlizzard()
{
}

void MagickBlizzard::update(sf::Time _elapsed, sf::Vector2f ownerpos)
{

	elapsed += _elapsed;


	if (moving) {
		animatedSprite.setPosition(_mousepos.x - 105, _mousepos.y - 135);
		animatedSprite.pause();
	}

	if (elapsed.asSeconds() > 0.05 && !moving) { //wenn halbe sekundew vorbei springen wir ein frame

		animatedSprite.play();


		//konnte es nicht besser lösen, bei animcount > 0 kam trotzdem erstes bild
		//muss noch gekillt werden

	}

}

void MagickBlizzard::draw(sf::RenderWindow & window)
{
	window.draw(animatedSprite);
}

void MagickBlizzard::initAnimation(const sf::Texture * texture)
{
	int spritex = 224;
	int spritey = 160;
	int picCount = 10;
	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), picCount, *texture, "FALLDOWN");
	animatedSprite.setFrameTime(sf::seconds(static_cast<float>(0.2)));
	this->id = 99;
}
