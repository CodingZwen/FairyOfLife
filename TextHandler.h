#pragma once
#include <SFML\Graphics.hpp>
#include "DamageText.h"
#include "Textbox.h"

class TextHandler
{



	std::vector<SingleText*> vptrtext;
	
	sf::Texture *ptrTexTextbox;
	sf::Font f;

public:
	TextHandler();
	~TextHandler();

	void init(sf::Font &font, sf::Texture  &texTextbox);		//erstmal gemischt mit draw unfktion
	void update(sf::Time _elapsed, sf::Vector2f pos);
	void draw(sf::RenderTarget &window );
	void popDmg(std::string str, sf::Vector2f startpos,int c);
	void popDmg(int dmg, sf::Vector2f startpos,int c);
	void popTextbox(std::string string, sf::Vector2f pos);

};


