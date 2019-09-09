
#pragma once
#include "Game.h"
#include <math.h>
#include "Button.h"


//Spiel_Projekt_Asteroiden_Assets

class Hauptmenu : public Gamestate
{
public:
	Hauptmenu(sf::Vector2i screenDimension);
	~Hauptmenu();

	void initButtons(sf::Vector2i screenDimensions);
	void UpdateButtons(Game &game);
	void RenderButtons(sf::RenderTarget &target);

private:

	std::map<std::string, std::shared_ptr<Button>> shareptr_Buttons;

	void HandleEvents(Game &game) override;
	void Update(Game &game) override;
	void Draw(Game &game) override;
	
	sf::Texture twolke;
	sf::Sprite _swolke;
	sf::Sprite _swolke2;
		
	sf::Font font;
	sf::Sprite sprBackground;
	sf::Texture texture;

};

