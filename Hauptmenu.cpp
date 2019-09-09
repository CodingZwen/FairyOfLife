#include "Hauptmenu.h"
#include <iostream>


Hauptmenu::Hauptmenu(sf::Vector2i screenDimension)
{
	//font besorgen
	if (!font.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\Fonts\\Kamikaze.ttf")) {
		std::cout << "fehler beim laden des fonts\n";
	}
	else {
		printf("font geladen\n");
	}




	if (!texture.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sonstige_Assets\\background.png")) {
		printf("fehler  background!\n");

	}
	else {
		printf("erfolgreich\n");
	}

	sprBackground.setTexture(texture);
	sprBackground.setPosition(0, 0);


	if (!twolke.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sonstige_Assets\\wolke.png")) {
		printf("fehler wolke!\n");

	}
	else {
		printf("erfolgreich\n");
	}

	_swolke.setTexture(twolke);
	_swolke.setPosition(50, 50);

	_swolke2.setTexture(twolke);
	_swolke2.setPosition(200, 150);



	initButtons(screenDimension);


}


Hauptmenu::~Hauptmenu()
{

}

void Hauptmenu::initButtons(sf::Vector2i screenDimensions)
{


	std::cout << "screenx: " << screenDimensions.x;
	std::cout << " screeny: " << screenDimensions.y << std::endl;


	int x = screenDimensions.x /2;
	int y = screenDimensions.y / 2;
	int width = 150;
	int height = 50;
	int verticalGap = 100;
	x -= width/2;
	y -= height/2;

	int helpButtonsX = 10;
	int helpButtonsY = 10;
	int helpButtonwidth = 120;
	int helpButtonheight = 50;
	int horizontalGap = 150;


	shareptr_Buttons["Start"] = std::make_shared<Button>(x, y, width, height, &this->font, "Start Game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	shareptr_Buttons["Exit"] = std::make_shared<Button>(x, y+verticalGap, width, height, &this->font, "Exit Game",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));



	shareptr_Buttons["Options"] = std::make_shared<Button>(x, y + verticalGap*2, width, height, &this->font, "Options",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	//help buttons
	verticalGap = 0;

	shareptr_Buttons["ShowFPS"] = std::make_shared<Button>(helpButtonsX+horizontalGap*0, helpButtonsY + verticalGap * 0, helpButtonwidth, helpButtonheight, &this->font, "ShowFPS",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	shareptr_Buttons["Max40FPS"] = std::make_shared<Button>(helpButtonsX+horizontalGap*1, helpButtonsY + verticalGap * 1, helpButtonwidth, helpButtonheight, &this->font, "Max FPS Off",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	shareptr_Buttons["MaxFPS"] = std::make_shared<Button>(helpButtonsX+horizontalGap*2, helpButtonsY + verticalGap * 2, helpButtonwidth, helpButtonheight, &this->font, "Max FPS On",
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


}

void Hauptmenu::UpdateButtons(Game &game)
{

	for (auto it = shareptr_Buttons.begin(); it != shareptr_Buttons.end(); ++it)
	{
		it->second->update(game.mousePosView);
	}
	
	if (this->shareptr_Buttons["Start"]->isPressed())
	{
		game.ChangeState(Game::Instanzen::Start_Game);
		printf("versucht spiel zu starten\n\n");
	}
	else if (this->shareptr_Buttons["Exit"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{

		game.stoprunning();
	}
	else if (this->shareptr_Buttons["ShowFPS"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{

		game.ActivateFPS();
	}
	else if (this->shareptr_Buttons["Max40FPS"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{

		game.setFPSMax(40);
	}
	else if (this->shareptr_Buttons["MaxFPS"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{
		game.setFPSMax(39999);
	}




	
}

void Hauptmenu::RenderButtons(sf::RenderTarget &target)
{
	for (auto it = shareptr_Buttons.begin(); it != shareptr_Buttons.end(); ++it)
	{
		it->second->render(&target);
	}
}


void Hauptmenu::HandleEvents(Game & game)
{
	sf::Event e;
	while (game.window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			game.window.close();
			game.stoprunning();
		}
			
	}
	//achtung wenn in poll event oder darüber dann kack game ab
	this->UpdateButtons(game);
}

void Hauptmenu::Update(Game & game)
{
	sf::Vector2i mousepos = sf::Mouse::getPosition(game.window);

	

	_swolke.move(-3.5, 0);
	_swolke2.move(-3, 0);

	if (_swolke.getPosition().x < -200) {
		int rnd = rand() % 700 + 1;
		_swolke.setPosition(1300, rnd);
	}


	if (_swolke2.getPosition().x < -200) {
		int rnd = rand() % 700 + 1;
		_swolke2.setPosition(1300, rnd);
	}

	



}

void Hauptmenu::Draw(Game & game)
{
	game.window.draw(sprBackground);
	game.window.draw(_swolke);
	game.window.draw(_swolke2);

	
	RenderButtons(game.window);

}





/*



_swolke.move(-3.5, 0);
_swolke2.move(-3, 0);


if (_swolke.getPosition().x < -200) {
int rnd = rand() % 700 + 1;
_swolke.setPosition(1300, rnd);
}


if (_swolke2.getPosition().x < -200) {
int rnd = rand() % 700 + 1;
_swolke2.setPosition(1300, rnd);
}



*/


/*

im kreis bewegen formel

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
{
angle++;

}



x = center.x + cos(angle)*radius;
y = center.y + sin(angle)*radius;

_swolke.setPosition(x, y);


if (angle > 360)angle = 0;
*/