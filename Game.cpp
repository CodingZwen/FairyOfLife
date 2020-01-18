#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	initWindow();
	running = true;
	current_state = std::move(std::unique_ptr<Hauptmenu>(new Hauptmenu(sf::Vector2i(window.getSize().x, window.getSize().y)))); 
	window.setVerticalSyncEnabled(0);

	printf("init ausgeführt\n");

}

void Game::initWindow()
{
	std::ifstream ifs("settings/settings.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode(); //current desktop resolution
	unsigned int Framerate = 120;
	bool verticalSync = false;

	if (ifs.is_open())
	{
		//erste zeile wird gelesen und in name gesdpeichert
		

		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullScreen;
		ifs >> Framerate;
		ifs >> verticalSync;
		std::cout << "Erfolgreich Ini geladen" << std::endl;
	}
	ifs.close();


	if (window_bounds.height > 1080 || window_bounds.height < 240
		|| window_bounds.width >1920 || window_bounds.width < 320)
	{
		std::cout << "w: " << window_bounds.width << " height: " << window_bounds.height << std::endl;
		window_bounds.width = 800;
		window_bounds.height = 600;
	}

	this->fullScreen = fullScreen;
	this->windowSettings.antialiasingLevel = 0;

	if (this->fullScreen)
	 window.create(window_bounds, GAMENAME, sf::Style::Fullscreen, windowSettings);
	else
	 window.create(window_bounds, GAMENAME, sf::Style::Titlebar | sf::Style::Close, windowSettings);

	window.setFramerateLimit(Framerate);
	window.setVerticalSyncEnabled(verticalSync);
}

void Game::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(this->window);
	this->mousePosView = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));

}

void Game::setFPSMax(unsigned int fps)
{
	window.setFramerateLimit(fps);
}

void Game::ActivateFPS()
{
	showFPS = !showFPS;
}

void Game::Run()
{

	while (window.isOpen()) {

		now = clock.getElapsedTime();
		framedeltatime = (now - vergangenezeit); //zeit zwischen den frames
		vergangenezeit = now;
		current_state->HandleEvents(*this);
		updateMousePositions();

		
		if (showFPS)
		{
			sf::Time time = fpsClock.getElapsedTime();
			float fps = 1.0f / time.asSeconds();
			window.setTitle(std::to_string(fps));
			fpsClock.restart();
			
		}

		window.clear();


		current_state->Update(*this);
		current_state->Draw(*this);
		window.display();
	}
}

void Game::ChangeState(Instanzen inst)
{

	switch (inst) {

	case  Instanzen::Startmenue:
		current_state = std::move(std::unique_ptr<Hauptmenu>(new Hauptmenu(sf::Vector2i(window.getSize().x, window.getSize().y)))); break;
	case Instanzen::Start_Game:
		current_state = std::move
		(std::unique_ptr<Main_Game>(new Main_Game(sf::Vector2i(window.getSize().x, window.getSize().y),*this))); break;
	case Instanzen::Options:
		break;

	default:break;
	}


	//system("pause");

}

void Game::Screenshot()
{
	sf::Texture tex;

	tex.create(window.getSize().x, window.getSize().y);
	tex.update(window);

	if (tex.copyToImage().saveToFile("screenshot1.jpg"))
	{
		printf("erster screenshot:d");
	}

}
