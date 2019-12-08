#pragma once
#include <SFML\Graphics.hpp>

//SIMPLE ANIMATION, ONE PICTURE CUT OUT FROM SPRITE
//USED FOR ITEMS

class Animation
{
	sf::Sprite sprite;
	sf::Time elapsed;

	int width, height;
	int currentrow;//derzeitige reihe von oben nach uinten 
	int column; // ->x von links nach rechts 

public:

	Animation();
	Animation(const sf::Texture &tex,
	int x, int y, int w, int h);

	~Animation();

	void setRotation(float rot);
	void init(const sf::Texture *tex,	int x, int y, int w, int h);

	void update(sf::Time _elapsed,sf::Vector2f position);
	void set_animrow(int _row) { currentrow = _row; };
	void set_animcolumn(int _column);
	void draw(sf::RenderWindow &window);
	   	 
};



