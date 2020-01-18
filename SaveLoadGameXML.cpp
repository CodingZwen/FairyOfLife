#include "SaveLoadGameXML.h"



SaveLoadGameXML::SaveLoadGameXML()
{
}


SaveLoadGameXML::~SaveLoadGameXML()
{
}



void SaveLoadGameXML::createSaveFile(const char * playername, int posx, int posy, int level, int money, int xp, std::vector<Item>& itembucket)
{
	TiXmlDocument doc;

	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "no");
	doc.LinkEndChild(decl);

	TiXmlElement * root = new TiXmlElement("savefile");
	doc.LinkEndChild(root);


	TiXmlElement * playerinfo = new TiXmlElement("playerinfo");
	root->LinkEndChild(playerinfo);
	playerinfo->SetAttribute("name", playername);


	TiXmlElement* pos;
	pos = new TiXmlElement("pos");
	playerinfo->LinkEndChild(pos);
	pos->SetAttribute("x", std::to_string(posx).c_str());
	pos->SetAttribute("y", std::to_string(posy).c_str());

	
	pos = new TiXmlElement("stats");
	playerinfo->LinkEndChild(pos);
	pos->SetAttribute("level", std::to_string(level).c_str());
	pos->SetAttribute("money", std::to_string(money).c_str());
	pos->SetAttribute("xp", std::to_string(xp).c_str());


	TiXmlElement * items = new TiXmlElement("items");
	root->LinkEndChild(items);

	const char *test = "Kackschwert";

	for (auto const &e : itembucket)
	{

		Item currentitem = e;

		TiXmlElement * item;
		item = new TiXmlElement("item");
		items->LinkEndChild(item);
		item->SetAttribute("type", "Weapon");
		item->SetAttribute("id", currentitem.getid());
		item->SetAttribute("rarity", "green"); //just test, need getrarity function from items as string return shit
		item->SetAttribute("name", currentitem.getName<std::string>().c_str());

		std::cout << "folgender Item name wurde gespeichert: " << currentitem.getName<std::string>().c_str() << std::endl;



		TiXmlElement * stats;
		stats = new TiXmlElement("stats");
		item->LinkEndChild(stats);
		stats->SetAttribute("atk", currentitem.getStats().atk);
		stats->SetAttribute("def", currentitem.getStats().def);
		stats->SetAttribute("speed", currentitem.getStats().speed);
		stats->SetAttribute("iq", currentitem.getStats().iq);
		stats->SetAttribute("krit", std::to_string(currentitem.getStats().krit).c_str()); //saved as string because setattribute takes as int if parameter



	}

	doc.SaveFile("newsavefile.xml");
}


void SaveLoadGameXML::loadSavefile(std::string &playername, int & posx, 
	int & posy, int & level, int & money, int & xp,
	std::vector<Item>& items,  sf::Sprite &Itemsprite, sf::Font *font,
	std::string savefilepath)
{

	TiXmlDocument doc(savefilepath.c_str());

	if (doc.LoadFile())	std::cout << "xml savefile erfolgreich geladen" << std::endl;
	else {std:: cout << "xml file konnte nicht geladen werden\n";		return; }



	if (doc.LoadFile())
	{

		TiXmlNode* playernode = 0;
		TiXmlElement* playerelement = 0;
		//playerinfo name etc

		//wir holen uns wurzek
		playernode = doc.FirstChild("savefile")->FirstChild(); //solten bei playerinfo sein
		assert(playernode);
		playerelement = playernode->ToElement();
		playername = playerelement->Attribute("name"); //name geholt

		TiXmlElement *posElement = playernode->FirstChild()->ToElement();
		posElement->QueryIntAttribute("x", &posx);
		posElement->QueryIntAttribute("y", &posy);

		TiXmlElement *statsElement = playernode->FirstChild()->NextSibling()->ToElement();
		assert(statsElement);
		statsElement->QueryIntAttribute("level", &level);
		statsElement->QueryIntAttribute("money", &money);
		statsElement->QueryIntAttribute("xp", &xp);


		TiXmlNode* itemsnode = 0;

		//items
		itemsnode = doc.FirstChild("savefile");
		assert(itemsnode);
		itemsnode = itemsnode->FirstChild(); //holen uns kind playerinfo
		assert(itemsnode);
		itemsnode = itemsnode->NextSibling(); //wir holen uns ITEMS
		assert(itemsnode); //jetzt sollten wir bei items sein
		itemsnode = itemsnode->FirstChild();//wir holen uns erstes item kind
		assert(itemsnode);

		while (itemsnode)//itemS node, its not the Items but its all items
		{

			TiXmlElement *itemelement = itemsnode->ToElement();
			assert(itemelement);

			//waffentyp
			const char *weapontype = itemelement->Attribute("type");
		
			//waffenid
			const char *weaponid = itemelement->Attribute("id");
			std::string s = weaponid;
		
			//waffenname
			const char *weaponname = itemelement->Attribute("name");	
			const char *rarity = itemelement->Attribute("rarity");
		

			//stats
			TiXmlElement *statselement = itemsnode->FirstChild()->ToElement();
			assert(statselement);

			int atk, def, speed, iq; float krit;
			statselement->QueryIntAttribute("atk", &atk); // If this fails, original value is left as-is
			statselement->QueryIntAttribute("def", &def);
			statselement->QueryIntAttribute("speed", &speed);
			statselement->QueryIntAttribute("iq", &iq);
			statselement->QueryFloatAttribute("krit", &krit);

			
			Item it(stoi(s),atk, def, speed, iq, krit,Rarity::BLUE, sf::Vector2f(10,10), Itemsprite, font);
			it.setWeaponType(weapontype);
			
		
			

			items.push_back(it);
			

			

			itemsnode = itemsnode->NextSibling();

		}
	}

}
