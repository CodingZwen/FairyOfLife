#pragma once
#include "Button.h"
#include "FileMaker.h"


//option frame muss können: sich schliessen, state ändern ins hauptmenue
//spiel laden spiel speichern


enum class States {  loop,back,gomainmenue,savegame,loadgame};

class OptionsFrame
{

	States states;
	bool aktiv= false;
	bool show = false;
	
	sf::Sprite sprOptionmenue;
	sf::RenderTarget  *ptrWindow=0;
	FileMaker *ptrFilemaker=0;
	sf::Font *font=0;
	sf::Vector2f viewcenterpos;
	sf::View newview;
public:
	OptionsFrame();
	~OptionsFrame();

	void init(sf::Texture *tex,sf::RenderTarget &t,
		FileMaker &fm,sf::Font *font);
	void initButtons();
	void draw(sf::RenderTarget &t);
	void drawButtons(sf::RenderTarget &t);
	void updateButtons(sf::Vector2f &mousepos);
	void update(sf::Vector2f &mousepos);
	void toggle() { show = !show; aktiv = !aktiv; }

	bool gomainmenue() { return (states == States::gomainmenue) ? true : false; }
	
	


	std::map<std::string, std::shared_ptr<Button>> Buttons;



};




/*

Spiel speichern 

Spielladen 






*/