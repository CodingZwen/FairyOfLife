#include "Items.h"



Items::Items()
{

	
	
	if (!font.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\Fonts\\KenPixel Future Square.ttf")) {
		printf("font in item konnte nicht geladen werden");
	}

	//statuswerte
	t_stats.setFont(font);
	t_stats.setCharacterSize(10);
	s_stats = { "\t  Statuswerte\nAtk:\t10\tInt:\t10\nDef:\t10\tSpd:\t10"};

	t_stats.setString(s_stats);
	t_stats.setOutlineColor(sf::Color(95,205,220,150));
	t_stats.setOutlineThickness(0.1);

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Magenta);
	rect.setSize(sf::Vector2f(32, 32));


	for (int i = 0; i < 8; i++) {
		_equiprects.push_back(rect);
	}
	
	
	
	_sword = 0;

	screenDimension = sf::Vector2i(0, 0);
	

	printf("\nitems konstrutkor ausgefuehrt\n");
}


Items::~Items()
{
}

void Items::initSprites(AssetManager & am)
{
	
	s_itemsprite.setTexture(am.GetTexture("items"));
	s_inventory.setTexture(am.GetTexture("inventorybackground"));
	s_equip.setTexture(am.GetTexture("equipbackground"));
	s_diamonds.setTexture(am.GetTexture("diamonds"));
	s_objectsprite.setTexture(am.GetTexture("objects"));

}

bool Items::loaditem(sf::Vector2f itempos, int itemnr,int Rarity)
{

	if (itemnr >= 70) {

		return false;

	}

	Item item;
	sf::IntRect intrect;

	item.rect.setSize(sf::Vector2f(32, 32));
	//hier noch vier farben einfueren
	//weiss gruen blau lila
	item.rect.setFillColor(sf::Color(50, 50, 50, 170));
	item.rect.setPosition(sf::Vector2f(itempos));

	item.text.setPosition(sf::Vector2f(itempos.x + 32, itempos.y));
	item.text.setCharacterSize(14);
	item.text.setFillColor(sf::Color::Green);

	item.description.setPosition(sf::Vector2f(itempos.x + 32, itempos.y + 32));
	item.description.setCharacterSize(11);
	item.description.setFillColor(sf::Color::White);


	item.velocity = sf::Vector2f(0, 0);



	//itemsnur wird in enemy handler gesetzt und kann 
	//0-69 sein, dementsprechend brauch ich hier tv tu
	//damit daraus in item wird (texturerect weapon sheet)
	int tilecount = itemnr;
	item.id = itemnr;
	int tv, tu;

	tu = (tilecount % (320 / 32));
	tv = (tilecount / (320 / 32));
	printf("\ndas war tv: %d und das war tu: %d\n", tu, tv);
	printf("\nx %f y: %f\n", itempos.x, itempos.y);

	intrect = sf::IntRect(tu * 32, tv * 32, 32, 32);
	item.irect = intrect;
	item.sprite = s_itemsprite;
	item.sprite.setTextureRect(intrect);
	item.sprite.setPosition(sf::Vector2f(itempos));

	item.text.setFont(font);
	item.description.setFont(font);
	
	int randomFaktor = 0;
	switch (Rarity)
	{
	case 0: break;
	case 1: randomFaktor = 50; break;
	case 2: randomFaktor = 99; break;
	}

	int random = rand() % 150+ randomFaktor;
	item.dmg = random;

	if (random > 50 && random <= 99) { item.text.setFillColor(sf::Color::Blue); }
	else if (random > 100) { item.text.setFillColor(sf::Color(210, 1, 255)); }


	item.description.setOutlineThickness(1.2);
	item.description.setOutlineColor(sf::Color::Black);

	item.text.setOutlineThickness(1.2);
	item.text.setOutlineColor(sf::Color::Black);

	item.krit = 1.0f;
	item.def = rand() % 150;
	item.speed = rand() % 150;
	item.iq = rand() % 150;

	//hier noch eine speziell funktion die den string formatier für die anzeige
	if (itemnr <= 9) { item.type = Equip_Type::Sword; item.text.setString("Schwert"); item.description.setString(get_description_string("Schwert des Grauens", item.dmg, item.def, item.speed, item.iq)); }
	else if (itemnr > 9 && itemnr <= 19) { item.type = Equip_Type::Shield; item.text.setString("Nebenhand"); item.description.setString(get_description_string("Schild der Verfluchten", item.dmg, item.def, item.speed, item.iq)); }
	else if (itemnr > 19 && itemnr <= 29) { item.type = Equip_Type::Amulet; item.text.setString("Schmuck"); item.description.setString(get_description_string("Amulet des Kaisers", item.dmg, item.def, item.speed, item.iq));}
	else if (itemnr > 29 && itemnr <= 39) { item.type = Equip_Type::Ring; item.text.setString("Finger"); item.description.setString(get_description_string("Ring der Schatten", item.dmg, item.def, item.speed, item.iq));}
	else if (itemnr > 39 && itemnr <= 49) { item.type = Equip_Type::Head; item.text.setString("Kopfbedeckung"); item.description.setString(get_description_string("Stahlhelm", item.dmg, item.def, item.speed, item.iq));}
	else if (itemnr > 49 && itemnr <= 59) { item.type = Equip_Type::Chest; item.text.setString("Brust"); item.description.setString(get_description_string("Magierkutte", item.dmg, item.def, item.speed, item.iq));	}
	else if (itemnr > 59 && itemnr <= 69){ item.type = Equip_Type::Boots; item.text.setString("Füße"); item.description.setString(get_description_string("Stiefel des Hasen", item.dmg, item.def, item.speed, item.iq));}
	else { printf("achtung nichts erstellt!!!!!\n"); }


	
	_vitems.push_back(item);

}

//draw the dropped items
void Items::draw(sf::RenderTarget & target)
{
	
	for (std::size_t i = 0; i < _vitems.size(); ++i)
	{

		if (_vitems[i].hovered) {
			target.draw(_vitems[i].rect);
			target.draw(_vitems[i].text);
			target.draw(_vitems[i].description);

		}


		target.draw(_vitems[i].sprite);

		printf("\nx %f y: %f\n", _vitems[i].sprite.getPosition().x, _vitems[i].sprite.getPosition().y);

		
	}
}

void Items::draw_inventory(sf::RenderTarget & target)
{
	target.draw(s_inventory);

	for (std::size_t i = 0; i < _inventory_items.size(); ++i)
	{

		target.draw(_inventory_items[i].sprite);


	}

	for (std::size_t i = 0; i < _inventory_items.size(); ++i)
	{
		

		if (_inventory_items[i].hovered) {
			target.draw(_inventory_items[i].rect);
			target.draw(_inventory_items[i].text);
			target.draw(_inventory_items[i].description); // schwierig eventuell irgend nach innen verschieben

		}

	}
	
	//hier war if teil in seperater schleife, da jetzt die description rects 
	//die andern überschreiben, evtl etwas einfallen lassen
}

void Items::draw_euqip(sf::RenderTarget & target)
{
	target.draw(s_equip);
	target.draw(t_stats);

	for (std::size_t i = 0; i < _equip_items.size(); ++i)
	{
		
		target.draw(_equip_items[i].sprite);
	//  target.draw(_equiprects[i]);
	}
		
}

void Items::draw_diamonds(sf::RenderTarget & target)
{
	sf::IntRect i_rect;
	for (std::size_t i = 0; i < vmoney.size(); i++)
	{
		i_rect = vmoney[i].irect;
		s_diamonds.setTextureRect(sf::IntRect(i_rect));
		s_diamonds.setPosition(vmoney[i].rect.getPosition());
		target.draw(s_diamonds);
		
	}


}

void Items::update_diamonds(sf::Vector2i mousepos, sf::Vector2f playerpos)
{
	//abaändern ist kopiert von update itemvektor

	//hovered evtl unnätig bei diamonds

	for (std::size_t i = 0; i < vmoney.size(); ++i)
	{
		vmoney[i].rect.move(vmoney[i].velocity);
	
		//es lag am origin, wenn schwert von unten links gekommen ist, hat es die obere rechte kante nicht erwischt (origin)
	
		if (vmoney[i].flying) {
			vmoney[i].velocity = getVelocityToTarget(sf::Vector2f(playerpos.x -490,playerpos.y +260),vmoney[i].rect.getPosition(),elapsed);

			if (vmoney[i].velocity.x > 4 || vmoney[i].velocity.y < -4)vmoney[i].destroy = true;

		//	printf("velocitiyx: %f", vmoney[i].velocity.x);

		}

		if (vmoney[i].rect.getGlobalBounds().contains(playerpos)|| vmoney[i].rect.getGlobalBounds().contains(sf::Vector2f(playerpos.x+15, playerpos.y + 15 ))) //hier war vor vektor2f(mousepos) drin um die sachen beim mauszeiger üverfahren in den geldbeutel fliegen zu lassen
		{
			vmoney[i].flying = true;
			//am besten nur ssetzen wenn geklickt wird aber dann 
			//kann es sein, das item an spieler vorbeifliegt wenn spieler sich bewegt.

		}
		
	}
}

bool Items::load_diamond(sf::Vector2f pos,unsigned int color)
{
	if (color >= 3)return false;

	Diamond dm;
	dm.rect.setSize(sf::Vector2f(34.f, 34.f));
	dm.rect.setPosition(pos);
	dm.irect = sf::IntRect(0,color*24,24,24);
	dm.destroy = false;
	dm.flying = false;
	dm.velocity = (sf::Vector2f(0, 0));

	vmoney.push_back(dm);

	return true;
}

void Items::animate_diamonds(sf::Time _elapsed)
{
	elapsed += _elapsed;
	
	if (elapsed.asSeconds() > 0.07) { //wenn halbe sekundew vorbei springen wir ein frame

		for (int i = 0; i < vmoney.size(); i++) {

			vmoney[i].irect.left = (frame * 24);
		
		}

		frame++;
		if (frame >= frames)frame = 0;

		elapsed = elapsed.Zero;
	}
}

void Items::diamond_all(sf::Vector2i mousepos, sf::Vector2f playerpos, sf::Time _elapsed)
{

	animate_diamonds(_elapsed);
	update_diamonds(mousepos, playerpos);
	clear_money_vector();

}




void Items::update_equip(sf::Vector2i mousepos, sf::Vector2f playerpos)
{
	s_equip.setPosition(sf::Vector2f(playerpos.x + 120, playerpos.y - 128));
	sf::Vector2f windowpos = sf::Vector2f(s_equip.getPosition().x +36, s_equip.getPosition().y + 22);
	t_stats.setPosition(sf::Vector2f(playerpos.x + 140, playerpos.y + 30));

	


	for (std::size_t i = 0; i  < _equip_items.size(); ++i)
	{

		int tu = i % 2;
		int tv = i / 2;

		_equiprects[i].setPosition(windowpos.x + (tu * 100), windowpos.y + (tv * 58));
	
		
		if (_equip_items[i].type == Equip_Type::Head) {
			_equip_items[i].sprite.setPosition(windowpos.x , windowpos.y );

		}

		if (_equip_items[i].type == Equip_Type::Chest) {
			_equip_items[i].sprite.setPosition(windowpos.x-20, windowpos.y +50);

		}

		if (_equip_items[i].type == Equip_Type::Boots) {
			_equip_items[i].sprite.setPosition(windowpos.x -20 , windowpos.y + 100);

		}

		if (_equip_items[i].type == Equip_Type::Ring) {
			_equip_items[i].sprite.setPosition(windowpos.x + 113, windowpos.y +50);

		}

		if (_equip_items[i].type == Equip_Type::Amulet) {
			_equip_items[i].sprite.setPosition(windowpos.x + 95, windowpos.y );

		}

		if (_equip_items[i].type == Equip_Type::Sword) {
			_equip_items[i].sprite.setPosition(windowpos.x + 1, windowpos.y + 190);

		}

		if (_equip_items[i].type == Equip_Type::Shield) {
			_equip_items[i].sprite.setPosition(windowpos.x + 90, windowpos.y + 190);

		}

	

	}



}

void Items::update_inventory(sf::Vector2i mousepos, sf::Vector2f playerpos)
{

	sf::Vector2f pos = sf::Vector2f((playerpos.x-302),(playerpos.y-112));


	s_inventory.setPosition(sf::Vector2f(pos.x - 15, pos.y - 14));

	for (std::size_t i = 0; i < _inventory_items.size(); ++i)
	{
		int tu = i % 6;
		int tv = i / 6;
		

		

		_inventory_items[i].rect.setPosition(pos.x + (tu * 52), pos.y + (tv * 48));
		_inventory_items[i].sprite.setPosition(pos.x + (tu * 52), pos.y + (tv * 48));
		
		_inventory_items[i].text.setPosition(pos.x + (tu * 52), pos.y + (tv * 48));

		_inventory_items[i].description.setPosition(pos.x + (tu * 52), (pos.y+15) + (tv * 48));


		if ((_inventory_items[i].rect.getGlobalBounds().left + 32) > mousepos.x &&(
			_inventory_items[i].rect.getGlobalBounds().left < mousepos.x) && (
				_inventory_items[i].rect.getGlobalBounds().top < mousepos.y) && (
					_inventory_items[i].rect.getGlobalBounds().top + 32 > mousepos.y))
		{
			_inventory_items[i].rect.setSize(sf::Vector2f(200, 64));
			printf("mauszeiger ist auf item\n\n\n");
			_inventory_items[i].hovered = true;

			if (_clicked) {
				equip_item(_inventory_items[i]);
			
			}


			if (_rclicked) {
				_inventory_items[i].for_sale = true;
				clear_inventory();

			}

			//am besten nur ssetzen wenn geklickt wird aber dann 
			//kann es sein, das item an spieler vorbeifliegt wenn spieler sich bewegt.


		}else
		{
			_inventory_items[i].hovered = false;
			_inventory_items[i].rect.setSize(sf::Vector2f(50, 50));
			
		}

	}

	_clicked = false;
	_rclicked = false;

}


void Items::playerstats_inkrement_from_equ(Attributs & atribs)
{
	int stats = 0;
	int dmg = 0;
	int def = 0;
	int intellekt = 0;
	float krit = 0;


	for (std::size_t i = 0; i < _equip_items.size(); ++i)
	{
		dmg += _equip_items[i].dmg;
		def += _equip_items[i].def;
		krit += _equip_items[i].krit;
		intellekt += _equip_items[i].iq;

	}


	atribs.setEquipStats(dmg, def, intellekt, krit,0);


}

void Items::update(sf::Vector2i mousepos , sf::Vector2f playerpos, Attributs &atribs)
{
	playerstats_inkrement_from_equ(atribs);
	t_stats.setString(get_eq_stats_as_string(atribs));

	for (std::size_t i = 0; i < _vitems.size(); ++i)
	{
		_vitems[i].rect.move(_vitems[i].velocity);
		_vitems[i].sprite.move(_vitems[i].velocity);
		_vitems[i].text.move(_vitems[i].velocity);
	     	_vitems[i].description.move(_vitems[i].velocity);

		//es lag am origin, wenn schwert von unten links gekommen ist, hat es die obere rechte kante nicht erwischt (origin)
		if (_vitems[i].rect.getGlobalBounds().contains((sf::Vector2f(playerpos.x+10,playerpos.y+15))) && _vitems[i].flying)
		{
			_vitems[i].destroy = true;

			printf("collision\n\n");
		}


		if (_vitems[i].flying) {
			_vitems[i].velocity = getVelocityToTarget(playerpos, _vitems[i].rect.getPosition(),elapsed);
			_vitems[i].rect.setSize(sf::Vector2f(50, 50));


			printf("itemsposxy: %f / %f\nplayerposxy: %f / %f\n", _vitems[i].rect.getPosition().x, _vitems[i].rect.getPosition().y, playerpos.x, playerpos.y);

		}
		

		//wenn item auf boden und mauszeiger drüber
		if (_vitems[i].rect.getGlobalBounds().contains(sf::Vector2f(mousepos)))
		{
			_vitems[i].rect.setSize(sf::Vector2f(210,80));
			_vitems[i].hovered = true;
			


		}
		else {
			_vitems[i].rect.setSize(sf::Vector2f(50, 50)); // brauch ich damit kollidiert werden kann
			_vitems[i].hovered = false;

		}




	}

}

void Items::getklick(sf::Vector2i mousepos)
{

	for (std::size_t i = 0; i < _vitems.size(); ++i)
	{

		if (_vitems[i].rect.getGlobalBounds().contains(sf::Vector2f(mousepos))&&_vitems[i].id!=70)
		{
			_vitems[i].flying=true;
		}
	}
}

//clear ground iutem verktor and put it in the players inventory!
void Items::clear_item_vector()
{
	for (int i = 0; i < _vitems.size(); i++) {

		if (_vitems[i].destroy==true) {
			_vitems[i].rect.setSize(sf::Vector2f(32, 32));



			if (_inventory_items.size() < 30) {

				_inventory_items.push_back(_vitems[i]);
				_vitems.erase(_vitems.begin() + i);
			}
			else {
				_vitems[i].destroy = false;
				_vitems[i].flying = false;
				_vitems[i].velocity = sf::Vector2f(0, 0);

			}


		
			
			printf("item zerstört!\n");
		}

	}

	//hier wird nichts gelöscht wenn inventar voll ist,
	//dies bitte noch ändern

	/*hier dann eventuell bevor gelöscht wird dem spieler 
	ins inventar das item kopieren, falls inventar voll ist, wird item nicht zersstört
	und es werden nur die bolls geändert damit es nicht mehr hinterherfliegt.*/

}

void Items::clear_inventory()
{
	for (std::size_t i = 0; i < _inventory_items.size(); ++i)
	{

		if (_inventory_items[i].for_sale) {

			int price = (_inventory_items[i].dmg + _inventory_items[i].def * _inventory_items[i].krit);
			price /=3;

			printf("waffe wurde für den preis: %d verkauft \n", price);
			//alte int vektor mit preisen die erwirtschaftet wurden
			//muss neu implementiert werden :/
			_vselled_items.push_back(price);
			_inventory_items.erase(_inventory_items.begin() + i);

		}

	}

}

//top ist ein irect, grüne sind 0+1, 24+1,48+1
void Items::clear_money_vector()
{
	for (int i = 0; i < vmoney.size(); i++) {

		if (vmoney[i].destroy == true) {
				
			int money = vmoney[i].irect.top+1;

			vmoney.erase(vmoney.begin() + i);
			_vselled_items.push_back(money);
		
		}

	}

}

int Items::get_dmg_from_eq()
{

	int dmg = 0;

	for (std::size_t i = 0; i < _equip_items.size(); ++i)
	{
		//printf("damage from eq: %d\n", _equip_items[i].dmg);
		dmg += _equip_items[i].dmg;

	}

	//printf("damage returned: %d\n", dmg);
	return dmg;



}

//macht den string der im equip menue angezeigt wird - playerstats + eq stats
std::string Items::get_eq_stats_as_string(Attributs &atribs)//struct
{
	int def = atribs.getdefense();
	int atk = atribs.getdmg();
	
	int _iq = atribs.getiq();
	int krit = atribs.getkrit();

	std::string buffer = "\t  Statuswerte\nAtk:   ";
	buffer += std::to_string(atk);

	if (atk <= 9)buffer += "    ";
	if (atk <= 99 && def > 9)buffer += "  ";
	if (atk <= 999 && def >99)buffer += " ";

	buffer += "\tInt: ";
	buffer += std::to_string(_iq);
	buffer += "\nDef:   ";
	buffer += std::to_string(def);

	if (def <= 9)buffer += "    ";
	if (def <= 99 && def > 9)buffer += "  ";
	if (def <= 999 && def >99)buffer += " ";

	
	buffer += "\tKrit:   ";
	buffer += std::to_string(krit);


	return buffer;
	
}

//für item description string, nicht für euqip menue!!!
std::string Items::get_description_string(std::string art,int atk, int def, int speed, int _iq)
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



sf::Vector2f Items::getVelocityToTarget(const sf::Vector2f &targetPos,
	const	sf::Vector2f &itempos, sf::Time &elapsed)
{

	sf::Vector2f velocity;
	sf::Vector2f dir;


	dir.x = (targetPos.x - itempos.x);
	dir.y = (targetPos.y - itempos.y);

	float factor = sqrt(128/((dir.x*dir.x) + (dir.y*dir.y)));

	
	velocity.x = (dir.x *factor);
	velocity.y = (dir.y *factor);

	return velocity;
}

void Items::equip_item(Item & item)
{

	if (item.type == Equip_Type::Sword) {
		_sword = item.id;
	
	}


	for (std::size_t i = 0; i < _equip_items.size(); ++i)
	{
		

		if (_equip_items[i].type == item.type) {
			_equip_items.erase(_equip_items.begin() + i);
			printf("itemgelöschjht aus euqipwindow");
			
		}

	}

		_equip_items.push_back(item);

}

int Items::get_equipped_sword()
{
	
	return _sword;

}

void Items::initScreenDimension(sf::Vector2i screenD)
{
	screenDimension = screenD;
}




/*

alternativfe draw funktion, anstatt jedem item ein sprite mitzugeben würde das intrect ausreichen
allerdings müsste ich dann immer intrect einstellen und etposition machen

void Items::draw_inventory(sf::RenderTarget & target)
{
target.draw(s_inventory);

for (std::size_t i = 0; i < _inventory_items.size(); ++i)
{

s_itemsprite.setTextureRect(_inventory_items[i].irect);
s_itemsprite.setPosition(_inventory_items[i].rect.getPosition());
target.draw(s_itemsprite);

if (_inventory_items[i].hovered) {
target.draw(_inventory_items[i].rect);
target.draw(_inventory_items[i].text);
target.draw(_inventory_items[i].description); // schwierig eventuell irgend nach innen verschieben

}

}


}






*/