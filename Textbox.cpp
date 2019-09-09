#include "Textbox.h"



void Textbox::draw(sf::RenderTarget & t)
{
	if (show)
	{
		t.draw(sprTextbox);
		t.draw(text);
	}
}

void Textbox::createTextbox(std::string string, sf::Vector2f pos)
{
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color(111, 111, 111, 255));
	text.setOutlineThickness(5);

	offSetTextbox = sf::Vector2f(-350.f, 100.f);
	offSetText = sf::Vector2f(-245, 160);

	text.setString(string);
	show = true;

}

void Textbox::update(sf::Time elapsed, sf::Vector2f pos)
{
	_elapsed += elapsed;
	sprTextbox.setPosition(pos.x + offSetTextbox.x, pos.y + offSetTextbox.y);
	text.setPosition(pos.x + offSetText.x, pos.y + offSetText.y);

	if (_elapsed.asSeconds() > 10)destroy = true;
}

void Textbox::setSprite(sf::Texture & t)
{
	sprTextbox.setTexture(t);
}

Textbox::Textbox()
{
}


Textbox::~Textbox()
{
}
