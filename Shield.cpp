#include "Shield.h"



Shield::Shield()
{
}


Shield::~Shield()
{
	delete texture;
}

void Shield::init()
{

	texture = new sf::Texture;

	if (!texture->loadFromFile("shild.png")) {
		printf("fehler beim laden der spielertextur\n");
	}
	else {
		printf("Spieler geladen\n");
	}

	shieldsprite.setTexture(*texture);
	shieldsprite.setTextureRect(sf::IntRect(128, 0, 32, 32));



}

void Shield::update(int dir, sf::Vector2f playerpos, bool defending)
{
	if (!defending) dir = 5;

	shieldsprite.setPosition(playerpos.x, playerpos.y +10);

	switch (dir) {

	case 2: shieldsprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); break;
	case 1: shieldsprite.setPosition(playerpos.x,playerpos.y-10); shieldsprite.setTextureRect(sf::IntRect(32, 0, 32, 32)); break;
	case 3: shieldsprite.setTextureRect(sf::IntRect(64, 0, 32, 32)); break;
	case 4: shieldsprite.setTextureRect(sf::IntRect(96, 0, 32, 32)); break;
	default:shieldsprite.setTextureRect(sf::IntRect(128, 0, 32, 32)); break;

	}

	 // wieder zurücksetzen, wird neugesetzt wenn spieler auf d bleibt
	defending = false;

}

void Shield::draw(sf::RenderTarget &target)
{

	target.draw(shieldsprite);


}
