#pragma once
#include <SFML\Graphics.hpp>
#define  RADIANT 0.017453f

class SingleText
{
protected:
	sf::Time _elapsed;
	bool destroy = false;
	bool showSprite = false;
	float angle=-90.f;
	int dx, dy, speed;
	int count = 0;


public:

	sf::Text text;
	SingleText();
	bool is_finish() { return destroy; }
	void init_font(sf::Font &font);
	void set_text(const std::string &_text) ;
	void set_text(int dmg);
	void set_position(sf::Vector2f pos);
	void initiate(std::string str, sf::Vector2f startpos,int color =0);
	virtual void update(sf::Time _elapsed, sf::Vector2f pos)=0;
	virtual void draw(sf::RenderTarget &t)=0;
	~SingleText();
};

