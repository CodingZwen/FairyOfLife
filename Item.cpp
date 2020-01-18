#include "Item.h"


//wenn inventar voll ist fliegen items nach china 
	
//id ist letzendlich nur das bild
	Item::Item(unsigned int ID, int atk, int def,
		int speed, int iq,float krit, Rarity rarity,
		sf::Vector2f spawnPos, sf::Sprite &spr, sf::Font *font)
	{
		if (ID >= 70) {
			printf("kein item erstellt\n");
			return;

		}

		sf::Vector2f Pos = spawnPos;
		itemSprite = spr;
	
		setPosition(spawnPos);


		rect.setSize(sf::Vector2f(50, 50));
		rect.setFillColor(sf::Color(10, 14, 46, 200));
		rect.setOutlineThickness(3.f);
		rect.setOutlineColor(sf::Color(200, 200, 200, 250));

		this->textBackground.setSize(sf::Vector2f(32, 32));
		this->textBackground.setFillColor(sf::Color(50, 50, 50, 170));
		this->textBackground.setPosition(sf::Vector2f(Pos));


		this->itemDescription.setFont(*font);
		this->itemDescription.setPosition(sf::Vector2f(Pos.x + 32, Pos.y+32));
		this->itemDescription.setCharacterSize(11);
		this->itemDescription.setFillColor(sf::Color::White);
		this->itemDescription.setOutlineThickness(1.2);
		this->itemDescription.setOutlineColor(sf::Color::Black);
		
		this->itemName.setFont(*font);
		this->itemName.setPosition(sf::Vector2f(Pos.x + 32, Pos.y));
		this->itemName.setCharacterSize(14);
		this->itemName.setOutlineThickness(1.2);
		this->itemName.setOutlineColor(sf::Color::Black);
	

		itemSprite.setPosition(sf::Vector2f(Pos));
		velocity = sf::Vector2f(0, 0);



		setID(ID);
		id = ID;
		
		stats.atk = atk;
		stats.def = def;
		stats.speed = speed;
		stats.iq = iq;
		stats.krit = krit;


		if (atk > 50 && atk <= 99) { itemName.setFillColor(sf::Color::Blue); }
		else if (atk > 100) { itemName.setFillColor(sf::Color(210, 1, 255)); }
		else if (atk <= 50) { itemName.setFillColor(sf::Color(30, 255, 0)); }

		//hier noch eine speziell funktion die den string formatier für die anzeige
		if (id <= 9) { type = EquipType::Weapon; itemName.setString("Erwachte Klinge"); itemDescription.setString(get_description_string("Schwert", stats.atk, stats.def, stats.speed, stats.iq)); }
		else if (id > 9 && id <= 19) { type = EquipType::Shield; itemName.setString("Helden Schild"); itemDescription.setString(get_description_string("Nebenhand", stats.atk, stats.def, stats.speed, stats.iq)); }
		else if (id > 19 && id <= 29) { type = EquipType::Amulet; itemName.setString("Kaiseramulett"); itemDescription.setString(get_description_string("Schmuck", stats.atk, stats.def, stats.speed, stats.iq)); }
		else if (id > 29 && id <= 39) { type = EquipType::Ring1; itemName.setString("Ring der Schatten"); itemDescription.setString(get_description_string("Finger", stats.atk, stats.def, stats.speed, stats.iq)); }
		else if (id > 39 && id <= 49) { type = EquipType::Head; itemName.setString("Stahlhelm"); itemDescription.setString(get_description_string("Kopf", stats.atk, stats.def, stats.speed, stats.iq)); }
		else if (id > 49 && id <= 59) { type = EquipType::Chest; itemName.setString("Magierkutte"); itemDescription.setString(get_description_string("Brust", stats.atk, stats.def, stats.speed, stats.iq)); }
		else if (id > 59 && id <= 69) { type = EquipType::Boots; itemName.setString("Hasenstiefel"); itemDescription.setString(get_description_string("Füße", stats.atk, stats.def, stats.speed, stats.iq)); }
		else { printf("achtung nichts erstellt!!!!!\n"); }

		

	}



	Item::Item()
	{
	}


	Item::~Item()
	{
	}

	void Item::update(sf::Time elapsed, sf::FloatRect player,  sf::Vector2i mousepos)
	{
	
		if (havetarget)
		{
			setVelocityToTarget(sf::Vector2f(player.left, player.top));

		}


		if (itemSprite.getGlobalBounds().contains(sf::Vector2f(mousepos)))
		{
			descriptionON();

		}
		else {
			descriptionOFF();

		}

	rect.move(velocity);
	itemSprite.move(velocity);
	itemName.move(velocity);
	itemDescription.move(velocity);


	}

	void Item::draw(sf::RenderTarget & target)
	{

		//das trennen in funktionen um einzeln im inventar items anzuzeigen
		if (showdescription)
		{
			
			target.draw(rect);
			target.draw(itemName);
			target.draw(itemDescription);
		}
		target.draw(itemSprite);
	}

	Item & Item::operator=(const Item left)
	{
		stats = left.stats;

		return *this;
	}






	void Item::drawDescription(sf::RenderTarget & target)
	{
		if (showdescription)
		{

			target.draw(rect);
			target.draw(itemName);
			target.draw(itemDescription);
		}
	}

	void Item::drawOnlySprite(sf::RenderTarget & target)
	{
		target.draw(itemSprite);
	}

	std::string Item::get_description_string(std::string art, int atk, int def, int speed, int _iq)
	{


		std::string buffer = art;
		buffer += ":\nAtk:   ";
		buffer += std::to_string(atk);


		buffer += "\tInt:\t";
		buffer += std::to_string(_iq);
		buffer += "\nDef:   ";
		buffer += std::to_string(def);

		buffer += "\tSpd:   ";
		buffer += std::to_string(speed);


		return buffer;



	}

	sf::Vector2f Item::getVelocityToTarget(const sf::Vector2f & targetPos)
	{

		sf::Vector2f itempos = rect.getPosition();
		sf::Vector2f velocity;
		sf::Vector2f dir;


		dir.x = (targetPos.x - itempos.x);
		dir.y = (targetPos.y - itempos.y);

		float factor = sqrt(128/((dir.x*dir.x) + (dir.y*dir.y)));

		velocity.x = dir.x*factor;
		velocity.y = dir.y*factor;

		return velocity;
	}




	bool Item::sprIsHovered(sf::Vector2i const mousepos)
	{
		
		if (itemSprite.getGlobalBounds().contains(sf::Vector2f(mousepos)))
		{
			return true;
		}

		return false;
	}

	bool Item::descriptrectIsHovered(sf::Vector2i const mousepos)
	{
		
		if (rect.getGlobalBounds().contains(sf::Vector2f(mousepos)))
		{


			return true;
		}
		return false;


	}

	void Item::setPosition(sf::Vector2f pos)
	{
		rect.setPosition(pos);
		itemSprite.setPosition(pos);
		itemName.setPosition(sf::Vector2f(pos.x+textboxoffset,pos.y));
		itemDescription.setPosition(sf::Vector2f(pos.x + textboxoffset, pos.y+32));
	}

	void Item::setVelocity(sf::Vector2f velo)
	{
		velocity = velo;
	}

	void Item::setVelocityToTarget(sf::Vector2f Targetpos)
	{
		velocity = getVelocityToTarget(Targetpos);
	}

	sf::Sprite & Item::getSprite()
	{
		return itemSprite;
	}

	const Stats & Item::getStats()
	{
		return stats;
	
	}

	
	void Item::setItemRarity(const char * weaponrarity)
	{
		if (weaponrarity == "green")
		{
			rarity = Rarity::GREEN;

		}
		else if (weaponrarity == "blue")
		{
			rarity = Rarity::BLUE;
		}
		else if (weaponrarity == "purple")
		{
			rarity = Rarity::PURPLE;
		}
		else
		{
			rarity = Rarity::GREY;
		}
	}

	void Item::setWeaponType(const char * weapontype)
	{

			if (weapontype == "Weapon")
			{
				type = EquipType::Weapon;

			}
			else if (weapontype == "Shield")
			{
				type = EquipType::Shield;
			}
			else if (weapontype == "Head")
			{
				type = EquipType::Head;
			}
			else if (weapontype == "Boots")
			{
				type = EquipType::Boots;
			}
			else if (weapontype == "Amulet")
			{
				type = EquipType::Amulet;
			}
			else if (weapontype == "Ring")
			{
				type = EquipType::Ring1;
			}
			else if (weapontype == "Chest")
			{
				type = EquipType::Chest;
			}

		
	}

	void Item::turnofftarget()
	{
		 havetarget = false;
		 velocity = sf::Vector2f(0,0);
	}

	void Item::descriptionON()
	{
		rect.setSize(sf::Vector2f(210, 80));
		showdescription = true;
	}

	void Item::descriptionOFF()
	{
		rect.setSize(sf::Vector2f(50, 50));
		showdescription = false;
	}

	
	void Item::setID(int ID)
	{
		int tilecount = ID;
		id = ID;
		int tv, tu;

		tu = (tilecount % (320 / 32));
		tv = (tilecount / (320 / 32));
	
		itemSprite.setTextureRect(sf::IntRect(tu * 32, tv * 32, 32, 32));
	}

	std::string Item::getItemasString()
	{

		std::stringstream ss;

		ss << static_cast<unsigned int>(id);
		ss << static_cast<unsigned int>(stats.atk);
		ss << static_cast<unsigned int>(stats.def);
		ss << static_cast<unsigned int>(stats.speed);
		ss << static_cast<unsigned int>(stats.iq);
		ss << static_cast<float>(stats.krit);



		return ss.str();
	}

	std::vector<float> Item::getItemStats()
	{

		std::vector<float> vstats;

		vstats.push_back(static_cast<float>(id));
		vstats.push_back(static_cast<float>(stats.atk));
		vstats.push_back(static_cast<float>(stats.def));
		vstats.push_back(static_cast<float>(stats.speed));
		vstats.push_back(static_cast<float>(stats.iq));
		vstats.push_back(static_cast<float>(stats.krit));


		return vstats;
	}

	//templates

	/*
	template<>
	const char* Item::getName<const char*>()
	{
		return itemName.getString().toAnsiString().c_str();
	}

	template <>
	std::string Item::getName<std::string>()
	{
		return itemName.getString();
	}

	*/
	/*
	savefile
	int itemcount

	int playerlevel
	int money
	int posx;
	int posy;
	int currentxp;
	
	id 4bytes und ein float
	atk
	def
	speed
	iq
	krit
	bool equipped
	
	*/