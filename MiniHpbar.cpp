#include "MiniHpbar.h"



MiniHpbar::MiniHpbar(unsigned int width, unsigned int height, float offsetY)
{
	rect.setSize(sf::Vector2f(width, height));
	maxLength = static_cast<float>(width);
	rect.setFillColor(sf::Color::Red);

	barDimensions.x = width;
	barDimensions.y = height;
	offsetHeight = offsetY;

}

MiniHpbar::MiniHpbar()
{
}


MiniHpbar::~MiniHpbar()
{
}

void MiniHpbar::init(unsigned int width, unsigned int height, float offsety)
{
	rect.setSize(sf::Vector2f(width, height));
	maxLength = static_cast<float>(width);
	rect.setFillColor(sf::Color::Red);

	barDimensions.x = width;
	barDimensions.y = height;
	offsetHeight = offsety;
}

void MiniHpbar::draw(sf::RenderTarget & t)
{
	t.draw(rect);
}

void MiniHpbar::update(const sf::Vector2f & ownerPos, unsigned int percent)
{
	rect.setSize(sf::Vector2f(maxLength*0.01f*percent,barDimensions.y));
	rect.setPosition(ownerPos);

	
}
