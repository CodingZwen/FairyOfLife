#include "TextHandler.h"



TextHandler::TextHandler()
{
	printf("texthandler erstellt\n");
}


TextHandler::~TextHandler()
{
}

void TextHandler::init(sf::Font & font, sf::Texture  &texTextbox)
{
	ptrTexTextbox = &texTextbox;
	f = font;
}

void TextHandler::update(sf::Time _elapsed,sf::Vector2f pos)
{
	
	for (auto i = vptrtext.begin(); i != vptrtext.end(); ) {
		SingleText *st = *i;
		st->update(_elapsed, pos);
	
		if (st->is_finish()){i = vptrtext.erase(i); delete st;}
		else{	i++;	}
		

	}

}

 void TextHandler::draw(sf::RenderTarget  &window )
{

	for (auto i = vptrtext.begin(); i != vptrtext.end();++i ) {
		SingleText *st = *i;
		//window.draw(st->text);
		st->draw(window);


	}
}

void TextHandler::popDmg(std::string str, sf::Vector2f startpos,int color)
{
	
	DamageText* dmgtext = new DamageText();
	dmgtext->init_font(f);
	dmgtext->initiate(str, startpos, color);
	vptrtext.push_back(dmgtext);
	
}


void TextHandler::popDmg(int dmg, sf::Vector2f startpos,int color)
{
	
	DamageText* dmgtext = new DamageText();
	dmgtext->init_font(f);
	dmgtext->initiate(std::to_string(dmg), startpos, color);
	
	vptrtext.push_back(dmgtext);


}

void TextHandler::popTextbox(std::string string, sf::Vector2f pos)
{
	Textbox* textbox = new Textbox();
	textbox->init_font(f);
	textbox->setSprite(*ptrTexTextbox);
	textbox->createTextbox(string, pos);

	
	vptrtext.push_back(textbox);

}
