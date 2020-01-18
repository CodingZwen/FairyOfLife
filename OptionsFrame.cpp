#include "OptionsFrame.h"



OptionsFrame::OptionsFrame()
{
}


OptionsFrame::~OptionsFrame()
{
}

void OptionsFrame::init(sf::Texture *tex, sf::RenderTarget &t,
	FileMaker &fm, sf::Font *_font)
{
	sprOptionmenue.setTexture(*tex);

	ptrWindow = &t;
	ptrFilemaker = &fm;
	

	font = _font;
	initButtons();//need pointers
	states = States::loop;

}

void OptionsFrame::initButtons()
{

	int x = -50;
	int y = -160;
	int width = 100;
	int height = 20;
	int verticalGap = 50;


	Buttons["save"] = std::make_shared<Button>(x, y, width, height, this->font, "Save Game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	Buttons["load"] = std::make_shared<Button>(x, y + verticalGap, width, height, this->font, "Load Game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));



	Buttons["options"] = std::make_shared<Button>(x, y + verticalGap * 2, width, height, this->font, "Options",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));



	Buttons["exit"] = std::make_shared<Button>(x, y + verticalGap * 3, width, height, this->font, "Exit Game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	Buttons["return"] = std::make_shared<Button>(x, y + verticalGap *4, width, height, this->font, "Close",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));



}

void OptionsFrame::draw(sf::RenderTarget & t)
{

	if (aktiv)
	{

		t.draw(sprOptionmenue);
		drawButtons(t);

	}
}

void OptionsFrame::drawButtons(sf::RenderTarget & t)
{
	for (auto it = Buttons.begin(); it != Buttons.end(); ++it)
	{
		it->second->render(&t);
	}
}

void OptionsFrame::updateButtons(sf::Vector2f &mousepos)
{
	
	if (!aktiv)return;


	//const  sf::FloatRect rect = ptrWindow->getView().g
	viewcenterpos = ptrWindow->getView().getCenter();


	int x = sprOptionmenue.getGlobalBounds().width;
	int y = sprOptionmenue.getGlobalBounds().height;

	sprOptionmenue.setPosition(sf::Vector2f((viewcenterpos.x-x/2),
			viewcenterpos.y -y/2));

	for (auto it = Buttons.begin(); it != Buttons.end(); ++it)
	{
		
		it->second->updatePosition(viewcenterpos);
		it->second->update(mousepos);
	}

	

	if (this->Buttons["save"]->isPressed())
	{
	
	}
	else if (this->Buttons["load"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{
		
	}
	else if (this->Buttons["options"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{

	}
	else if (this->Buttons["exit"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{
		states = States::gomainmenue;
	}
	else if (this->Buttons["return"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{
		toggle();
	}

}

void OptionsFrame::update(sf::Vector2f &mousepos)
{

	 updateButtons(mousepos);

}

