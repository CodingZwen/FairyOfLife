#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "Gamestate.h"
#include "Hauptmenu.h"
#include "Main_Game.h"

#define DEFAULTSCREENSIZEX 1280
#define DEFAULTSCREENSIZEY 720



class Game
{

	const std::string GAMENAME = "Fairy of Life";

	sf::ContextSettings windowSettings;
	std::unique_ptr<Gamestate> current_state;
	std::vector<sf::VideoMode> videoModes;
	


	bool showFPS = false;
	bool running = false;
	bool fullScreen = false;
	

public:
	Game();
	~Game();

	sf::RenderWindow window;
	enum class Instanzen { Startmenue, Start_Game, Options, Pause };

	void Init();
	void initWindow();
	void updateMousePositions();
	void setFPSMax(unsigned int fps);
	void ActivateFPS();

	void Run();
	void ChangeState(Instanzen inst);
	bool isRunning() { return running; }
	void stoprunning() {running = false; window.close();}

	sf::Clock fpsClock; //für fps
	sf::Clock clock;
	sf::Time now;
	sf::Time framedeltatime;
	sf::Time vergangenezeit = clock.getElapsedTime();

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//der pointer zeigt auf den jeweiligen spielstatus der von 
	//gamestate erbt, gamestate hat standard funktionen -> update,handle events, 
};

