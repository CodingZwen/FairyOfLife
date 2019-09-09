#include "Item.h"


namespace SVEN
{


	

	Item::Item(unsigned int ID, short atk, short def, short speed, short iq, 
		sf::Vector2f spawnPos, sf::Sprite * spr, sf::Font *font)
	{
		//if (ID >= 70) {
		//	printf("kein item erstellt\n");
		//	return;

		//}

		//sf::Vector2f Pos = spawnPos;
		//itemSprite = spr;

		//this->textBackground.setSize(sf::Vector2f(32, 32));
		//this->textBackground.setFillColor(sf::Color(50, 50, 50, 170));
		//this->textBackground.setPosition(sf::Vector2f(Pos));


		//this->itemDescription.setFont(*font);
		//this->itemDescription.setPosition(sf::Vector2f(Pos.x + 32, Pos.y));
		//this->itemDescription.setCharacterSize(11);
		//this->itemDescription.setFillColor(sf::Color::White);

		//this->itemName.setFont(*font);
		//this->itemName.setPosition(sf::Vector2f(Pos.x + 32, Pos.y+32));
		//this->itemName.setCharacterSize(14);
		//this->itemDescription.setFillColor(sf::Color::Green);


		//this->itemSprite->setPosition(sf::Vector2f(Pos));
		//item.velocity = sf::Vector2f(0, 0);



		////itemsnur wird in enemy handler gesetzt und kann 
		////0-69 sein, dementsprechend brauch ich hier tv tu
		////damit daraus in item wird (texturerect weapon sheet)
		//int tilecount = itemnr;
		//item.id = itemnr;
		//int tv, tu;

		//tu = (tilecount % (320 / 32));
		//tv = (tilecount / (320 / 32));
		//printf("\ndas war tv: %d und das war tu: %d\n", tu, tv);

		//intrect = sf::IntRect(tu * 32, tv * 32, 32, 32);
		//item.irect = intrect;
		//item.sprite = s_itemsprite;
		//item.sprite.setTextureRect(intrect);

		//item.text.setFont(font);
		//item.description.setFont(font);

		//int randomFaktor = 0;
		//switch (Rarity)
		//{
		//case 0: break;
		//case 1: randomFaktor = 50; break;
		//case 2: randomFaktor = 99; break;
		//}

		//int random = rand() % 150 + randomFaktor;
		//item.dmg = random;

		//if (random > 50 && random <= 99) { item.text.setFillColor(sf::Color::Blue); }
		//else if (random > 100) { item.text.setFillColor(sf::Color(210, 1, 255)); }


		//item.description.setOutlineThickness(1.2);
		//item.description.setOutlineColor(sf::Color::Black);

		//item.text.setOutlineThickness(1.2);
		//item.text.setOutlineColor(sf::Color::Black);

		//item.krit = 1.0f;
		//item.def = rand() % 150;
		//item.speed = rand() % 150;
		//item.iq = rand() % 150;

		////hier noch eine speziell funktion die den string formatier für die anzeige
		//if (itemnr <= 9) { item.type = Equip_Type::Sword; item.text.setString("Schwert"); item.description.setString(get_description_string("Schwert des Grauens", item.dmg, item.def, item.speed, item.iq)); }
		//else if (itemnr > 9 && itemnr <= 19) { item.type = Equip_Type::Shield; item.text.setString("Nebenhand"); item.description.setString(get_description_string("Schild der Verfluchten", item.dmg, item.def, item.speed, item.iq)); }
		//else if (itemnr > 19 && itemnr <= 29) { item.type = Equip_Type::Amulet; item.text.setString("Schmuck"); item.description.setString(get_description_string("Amulet des Kaisers", item.dmg, item.def, item.speed, item.iq)); }
		//else if (itemnr > 29 && itemnr <= 39) { item.type = Equip_Type::Ring; item.text.setString("Finger"); item.description.setString(get_description_string("Ring der Schatten", item.dmg, item.def, item.speed, item.iq)); }
		//else if (itemnr > 39 && itemnr <= 49) { item.type = Equip_Type::Head; item.text.setString("Kopfbedeckung"); item.description.setString(get_description_string("Stahlhelm", item.dmg, item.def, item.speed, item.iq)); }
		//else if (itemnr > 49 && itemnr <= 59) { item.type = Equip_Type::Chest; item.text.setString("Brust"); item.description.setString(get_description_string("Magierkutte", item.dmg, item.def, item.speed, item.iq)); }
		//else if (itemnr > 59 && itemnr <= 69) { item.type = Equip_Type::Boots; item.text.setString("Füße"); item.description.setString(get_description_string("Stiefel des Hasen", item.dmg, item.def, item.speed, item.iq)); }
		//else { printf("achtung nichts erstellt!!!!!\n"); }



		//_vitems.push_back(item);
	}

	Item::~Item()
	{
	}

	void Item::draw(sf::RenderTarget & target)
	{
		target.draw(*itemSprite);
	}


}