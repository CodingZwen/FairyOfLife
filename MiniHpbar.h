#include <SFML/Graphics.hpp>
#pragma once
class MiniHpbar
{
public:
	MiniHpbar(unsigned int width,unsigned int height, float offsety =2);
	MiniHpbar();

	~MiniHpbar();

	void init(unsigned int width, unsigned int height, float offsety = 2);
	void draw(sf::RenderTarget &t);
	void update(const sf::Vector2f &ownerPos,unsigned int percent);


private:

	sf::Vector2f barDimensions;
	sf::RectangleShape rect;
	float maxLength = 0;
	float offsetHeight;
};

