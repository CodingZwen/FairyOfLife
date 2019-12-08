#include "Animation.h"


//updatet nur sprite und drawt nicht
//und bewet sprite auch nicht, updatet nur bilder abfolge

Animation::Animation()
{

	currentrow = 0;
	column = 0;
		
	
}


Animation::~Animation()
{
}



Animation::Animation(const sf::Texture &tex,
	int x, int y, int w, int h)
{


	currentrow = 0;
	column = 0;

	
	height = h;
	width = w;

	sprite.setTexture(tex);
	sprite.setPosition(500, 500);
	sprite.setTextureRect(sf::IntRect(x, y, w, h));
	sprite.setOrigin(w / 2, h / 2);
	

}



void Animation::setRotation(float rot)
{
	sprite.setRotation(rot);
}

void Animation::init(const sf::Texture *tex,
	int x, int y, int w, int h)
{


	currentrow = 0;
	column = 0;


	height = h;
	width = w;

	sprite.setTexture(*tex);
	sprite.setTextureRect(sf::IntRect(x, y, w, h));
	sprite.setOrigin(w / 2, h / 2);
	sprite.setPosition(x, y);


}






void Animation::update(sf::Time _elapsed, sf::Vector2f position)
{

	elapsed += _elapsed;
	sprite.setTextureRect(sf::IntRect(column*width, currentrow*height, width, height));
	sprite.setPosition(position);
	
}

void Animation::set_animcolumn(int _column)
{
	this->column = _column;
	

	
}

void Animation::draw(sf::RenderWindow & window)
{
	window.draw(sprite);



}



