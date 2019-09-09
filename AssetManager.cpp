#include "AssetManager.h"



AssetManager::AssetManager()
{
	 //error sound,bild,font zum abfangen
	if (!t_error.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\Sonstige_Assets\\error.png")) {
		printf("fehler beim laden der errortextur\n");
	}
	else {
		printf("errortextur geladen\n");
			
	}


}


AssetManager::~AssetManager()
{
}


void AssetManager::LoadTexture(std::string  name, const char *fileName, bool smooth)
{
	sf::Texture tex;
		if (tex.loadFromFile(fileName)) {
		
			tex.setSmooth(smooth);
			this->_textures[name] = tex;


			std::vector<char> pngBinary = fm.ReadFile(fileName);
			std::string s = fm.addFileNameToBinaryVec(pngBinary, name);
			TexturesForFile.push_back(s);
			
		}
		else {

			printf("\nTextur mit Pfad: %s konnte nicht geladen werden!", fileName);

		}

}


	//evtl rosa texture laden wenn name nicht trifft
	//anscheinend programmiere ich mit c++ 17 da c++ 20 bei map die funktion contains hat
	sf::Texture & AssetManager::GetTexture(std::string name)
	{
		std::map< std::string, sf::Texture >::iterator it;
		it = _textures.find(name);

		//ganz komisch, funktioniert wie eine while schleife
		if (it != _textures.end()) {
			
			//printf("\nTexture gefunden und geladen -> Name:  %s",  it->first);
			return this->_textures.at(name);
		}
		else {
			//printf("\nTexture mit dem Namen  %s konnte nicht gefunden werden",name);

			return this->t_error;
		}


	
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{


		sf::Font font;

		if (font.loadFromFile(fileName)) {

			this->_fonts[name] = font;
		}
		else {

			//printf("\nSound mit Pfad: %s konnte nicht geladen werden!", fileName);

		}

	}

	sf::Font * AssetManager::ptr_GetFont(std::string name)
	{
		std::map< std::string, sf::Font >::iterator it;
		it = _fonts.find(name);
		sf::Font *ptr_font;

		//ganz komisch, funktioniert wie eine while schleife
		if (it != _fonts.end()) {

			//printf("\nFont gefunden und geladen -> Name:  %s", it->first);
			ptr_font =&_fonts.at(name);
			return ptr_font;
		}
		else {
			//printf("\nFont mit dem Namen  %s konnte nicht gefunden werden", name);

			return nullptr;
		}
	}

	void AssetManager::LoadSound(std::string name, std::string fileName)
	{

		sf::SoundBuffer soundbuffer;

		if (soundbuffer.loadFromFile(fileName)) {

			this->_sounds[name] = soundbuffer;
		}
		else {

			//printf("\nSound mit Pfad: %s konnte nicht geladen werden!", fileName);

		}

	}

	sf::SoundBuffer * AssetManager::ptr_GetSound(std::string name)
	{
		std::map< std::string, sf::SoundBuffer >::iterator it;
		it = _sounds.find(name);
		sf::SoundBuffer *ptr_sound;

		//ganz komisch, funktioniert wie eine while schleife
		if (it != _sounds.end()) {

			//printf("\nSound gefunden und geladen -> Name:  %s", it->first);
			ptr_sound = &_sounds.at(name);
			return ptr_sound;
		}
		else {
		//	printf("\nSound mit dem Namen  %s konnte nicht gefunden werden", name);

			return nullptr;
		}
	}


	void AssetManager::createCurrentResourceAsBinaryFile()
	{
		//aus dem string vector in dem die bilder bereits mit name gespeicher sind
		//wird hier nur der char vector erstellt 
		std::vector<unsigned char> bytes = fm.CreateBinaryVecReadyToPrint(TexturesForFile);
		fm.createBinaryFile(bytes,"resource.binary");
		printf("groesse bildvec: %d! bytesvec: %d\n", TexturesForFile.size(), bytes.size());
	}

	void AssetManager::LoadFromFile()
	{
		vector<unsigned char> file = fm.getBytesFromFile("bin\\resource.binary");
		vector<vector<unsigned char>> stringfile(fm.readBinaryCharVecToStringV(file));

		_textures = fm.getBinaryFileAsMap(stringfile);


		setTextureSmooth("playerframe");
		setTextureSmooth("skillbarframe");
		setTextureSmooth("diamondanimation");
		setTextureSmooth("skillmenueframe");
		setTextureSmooth("skillmenueSpellSprites");
		setTextureSmooth("butterfly");
		setTextureSmooth("cat");
		setTextureSmooth("raven");


	}

	void AssetManager::LoadAllTexturesFromImages()
	{

		LoadTexture("feuerball", "Spiel_Projekt_Protectyourisle_Assets\\Spell_Assets\\fireball.png");
		LoadTexture("eisball", "Spiel_Projekt_Protectyourisle_Assets\\Spell_Assets\\iceball.png");
		LoadTexture("eisball2", "Spiel_Projekt_Protectyourisle_Assets\\Spell_Assets\\fire_blue.png");
		LoadTexture("iceorb", "Spiel_Projekt_Protectyourisle_Assets\\Spell_Assets\\iceorb.png");
		LoadTexture("blizzard", "Spiel_Projekt_Protectyourisle_Assets\\Spell_Assets\\eishagel.png");
		LoadTexture("golem", "Spiel_Projekt_Protectyourisle_Assets\\Enemy_Assets\\steingolem.png");
		LoadTexture("baum", "Spiel_Projekt_Protectyourisle_Assets\\Enemy_Assets\\baummonster2.png");
		LoadTexture("Fireboss", "Spiel_Projekt_Protectyourisle_Assets\\Enemy_Assets\\fireboss.png");
		LoadTexture("weaponset", "Spiel_Projekt_Protectyourisle_Assets\\Item_Assets\\swords.png");
		LoadTexture("world2", "Spiel_Projekt_Protectyourisle_Assets\\Tilemaps\\Cliff.png");
		LoadTexture("world", "Spiel_Projekt_Protectyourisle_Assets\\Tilemaps\\map8.png");
		LoadTexture("playertexture", "Spiel_Projekt_Protectyourisle_Assets\\Player_Assets\\mainchar_.png");
		LoadTexture("house1", "Spiel_Projekt_Protectyourisle_Assets\\Tilemaps\\map_indoor.png");
		LoadTexture("textbox", "Spiel_Projekt_Protectyourisle_Assets\\Sonstige_Assets\\textbox3.png");
		//gui zeugs
		LoadTexture("playerframe", "Spiel_Projekt_Protectyourisle_Assets\\Gui\\playerframe.png", 1);
		LoadTexture("skillbarframe", "Spiel_Projekt_Protectyourisle_Assets\\Gui\\skillbarframe.png", 1);
		LoadTexture("diamondanimation", "Spiel_Projekt_Protectyourisle_Assets\\Gui\\diamondanimation.png", 1);
		LoadTexture("skillmenueframe", "Spiel_Projekt_Protectyourisle_Assets\\Gui\\skillmenueframe.png", 1);
		LoadTexture("skillmenueSpellSprites", "Spiel_Projekt_Protectyourisle_Assets\\Gui\\skillmenueSpellSprites.png", 1);
		LoadTexture("butterfly", "Spiel_Projekt_Protectyourisle_Assets\\Animal_Assets\\butterfly.png", 1);
		LoadTexture("cat", "Spiel_Projekt_Protectyourisle_Assets\\Animal_Assets\\cat.png", 1);
		LoadTexture("raven", "Spiel_Projekt_Protectyourisle_Assets\\Animal_Assets\\raven.png", 1);


		LoadTexture("items", "Spiel_Projekt_Protectyourisle_Assets\\Item_Assets\\items.png", 1);
		LoadTexture("inventorybackground", "Spiel_Projekt_Protectyourisle_Assets\\Gui\\inventory.png", 1);
		LoadTexture("equipbackground", "Spiel_Projekt_Protectyourisle_Assets\\Resources\\charmenue.png", 1);
		LoadTexture("diamonds", "Spiel_Projekt_Protectyourisle_Assets\\Item_Assets\\diamonds.png", 1);
		LoadTexture("objects", "Spiel_Projekt_Protectyourisle_Assets\\Item_Assets\\Item_Assets\\objects.png", 1);





	}

	void AssetManager::setTextureSmooth(string name)
	{
		_textures[name].setSmooth(1);
	}


