#include "SingleText.h"



SingleText::SingleText()
{
	speed = 2;
	angle = -90;
}

void SingleText::init_font(sf::Font & font)
{
	text.setFont(font);
	text.setFillColor(sf::Color::Yellow);   //text kommt von entity
	text.setCharacterSize(18);
	text.setString("default");
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0);
	angle = -90;
}

void SingleText::set_text(const std::string &_text)
{

	text.setString(_text);
}

void SingleText::set_text(int dmg)
{
	text.setString(std::to_string(dmg));
}

void SingleText::set_position(sf::Vector2f pos)
{
	text.setPosition(pos);
}

void SingleText::initiate(std::string str, sf::Vector2f startpos,int color)
{	
	switch (color) {
	case 0: text.setFillColor(sf::Color::Red); break;
	case 1: text.setFillColor(sf::Color::Green); break;
	case 2: text.setFillColor(sf::Color::Blue); break;
	case 3: text.setFillColor(sf::Color::Yellow); break;

	default:break;
	}
	text.setString(str);
	text.setPosition(startpos);
}



SingleText::~SingleText()
{
}


/*

elapsed += _elapsed;


dx = cos(angle*RADIANT) * speed; //bei 0 also nach rechts kommt hier cos =1 raus
dy = sin(angle*RADIANT) * speed; //hier kommt bei angle 0, also sin 0 = 0 raus deswegen nach rechts
text.move(dx, dy);

angle += 3.01f;

if (angle > 90) {
angle = -90;
count++;
}

if (count > 0)destroy = true;

//version die doppsen tut
*/