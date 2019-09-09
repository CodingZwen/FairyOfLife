#pragma once
#include "SingleText.h"
class Textbox : public SingleText
{
	sf::Sprite sprTextbox;
	sf::Vector2f offSetTextbox;
	sf::Vector2f offSetText;
	bool show = true;

	void draw(sf::RenderTarget &t)override;
	void update(sf::Time elapsed, sf::Vector2f pos) override;
	
public:
	Textbox();
	~Textbox();

	void createTextbox(std::string  string, sf::Vector2f pos);
	void setSprite(sf::Texture &t);
	sf::Sprite const & getSprite() const { return sprTextbox; }
};

