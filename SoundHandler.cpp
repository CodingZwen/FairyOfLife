#include "SoundHandler.h"



void SoundHandler::stopMusic()
{
	
	if (currentMusic!=nullptr)currentMusic->stop();
}

void SoundHandler::init(AssetManager & Amanager)
{
	
	currentMusic = nullptr;
	sounds["treesound"].setBuffer(*Amanager.ptr_GetSound("treesound"));
	sounds["Swordswing"].setBuffer(*Amanager.ptr_GetSound("Swordswing"));
	sounds["Fireballsound"].setBuffer(*Amanager.ptr_GetSound("Fireballsound"));
	sounds["Electrichitsound"].setBuffer(*Amanager.ptr_GetSound("Electrichitsound"));
	sounds["Snowballsound"].setBuffer(*Amanager.ptr_GetSound("Snowballsound"));
	sounds["Lvupsound"].setBuffer(*Amanager.ptr_GetSound("Lvupsound"));
	sounds["Kachingsound"].setBuffer(*Amanager.ptr_GetSound("Kachingsound"));
	sounds["nomana1"].setBuffer(*Amanager.ptr_GetSound("nomana1"));
	sounds["nomana2"].setBuffer(*Amanager.ptr_GetSound("nomana2"));


	
	lastsound = "";
	

	Music["DesertMusic"].openFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Desert.ogg");
	Music["WoodMusic"].openFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Woodmusic.ogg");
	Music["BossMusic"].openFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Bossmusic.ogg");
	Music["HomeMusic"].openFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Homemusic.ogg");
	Music["TownMusic"].openFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sounds\\Townmusic.ogg");
}

void SoundHandler::playSound(std::string soundName, bool loop)
{
	//if (soundTimer.asSeconds() > 0.3)
	if (lastsound != soundName)
	{
		lastsound = soundName;
		sounds[soundName].setVolume(50);
		sounds[soundName].play();
		sounds[soundName].setLoop(loop);
		soundTimer = soundTimer.Zero;
	}
	else
	{
		if (soundTimer.asSeconds() > 0.3)
		{
			lastsound = soundName;
			sounds[soundName].setVolume(50);
			sounds[soundName].play();
			sounds[soundName].setLoop(loop);
			soundTimer = soundTimer.Zero;
			

		}
	}
}

void SoundHandler::playMusic(std::string SongName, bool loop)
{
	if(currentMusic!=nullptr)currentMusic->stop();
	Music[SongName].setVolume(5.5);
	Music[SongName].play();
	Music[SongName].setLoop(loop);
	currentMusic = &Music[SongName];

}

void SoundHandler::update(sf::Time elapsed)
{
	soundTimer += elapsed;
}

SoundHandler::SoundHandler()
{
}


SoundHandler::~SoundHandler()
{
}
