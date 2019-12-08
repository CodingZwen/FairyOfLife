#include "Items.h"

/*
eventuell fliegen die euqip items ztum player. ich finde die funktio nicht
in der ich das target des items setze
*/


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

	int atk = rand() % 150;
	int dmg = rand() % 150;
	int def = rand() % 150;
	int speed = rand() % 150;
	int iq = rand() % 150;
	float krit = 1.0f;


	Item item(itemnr,atk,def,speed,iq,Rarity::PURPLE,itempos,s_itemsprite,&font);
	
	
	_vitems.push_back(item);

}

//draw the dropped items
void Items::draw(sf::RenderTarget & target)
{
	
	for (std::size_t i = 0; i < _vitems.size(); ++i)
	{

		_vitems[i].draw(target);
		
	}
}

void Items::draw_inventory(sf::RenderTarget & target)
{
	target.draw(s_inventory);

	



	for (std::size_t i = 0; i < _inventory_items.size(); ++i)
	{

		
		_inventory_items[i].drawOnlySprite(target);


	}

	for (std::size_t i = 0; i < _inventory_items.size(); ++i)
	{


		_inventory_items[i].drawDescription(target);


	}


	

}

void Items::draw_euqip(sf::RenderTarget & target)
{
	target.draw(s_equip);
	target.draw(t_stats);

	for (std::size_t i = 0; i < _equip_items.size(); ++i)
	{

	
		_equip_items[i].draw(target);
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
		_equip_items[i].update(elapsed, playerpos, mousepos);

		int tu = i % 2;
		int tv = i / 2;

		_equiprects[i].setPosition(windowpos.x + (tu * 100), windowpos.y + (tv * 58));
	
		
		if (_equip_items[i].type == EquipType::Head) {
			_equip_items[i].setPosition(windowpos);

		}

		if (_equip_items[i].type == EquipType::Chest) {
			_equip_items[i].setPosition(sf::Vector2f(windowpos.x-20, windowpos.y +50));

		}

		if (_equip_items[i].type == EquipType::Boots) {
			_equip_items[i].setPosition(sf::Vector2f(windowpos.x -20 , windowpos.y + 100));

		}

		if (_equip_items[i].type == EquipType::Ring1) {
			_equip_items[i].setPosition(sf::Vector2f(windowpos.x + 113, windowpos.y +50));

		}

		if (_equip_items[i].type == EquipType::Amulet) {
			_equip_items[i].setPosition(sf::Vector2f(windowpos.x + 95, windowpos.y ));

		}

		if (_equip_items[i].type == EquipType::Sword) {
			_equip_items[i].setPosition(sf::Vector2f(windowpos.x + 1, windowpos.y + 190));

		}

		if (_equip_items[i].type == EquipType::Shield) {
			_equip_items[i].setPosition(sf::Vector2f(windowpos.x + 90, windowpos.y + 190));

		}

	

	}



}

void Items::update_inventory(sf::Time elapsed, sf::Vector2i mousepos, sf::Vector2f playerpos)
{

	sf::Vector2f pos = sf::Vector2f((playerpos.x-302),(playerpos.y-112));


	s_inventory.setPosition(sf::Vector2f(pos.x - 15, pos.y - 14));

	for (std::size_t i = 0; i < _inventory_items.size(); ++i)
	{
		int tu = i % 6;
		int tv = i / 6;
		

		_inventory_items[i].update(elapsed,playerpos,mousepos);

		_inventory_items[i].setPosition(sf::Vector2f(pos.x + (tu * 52), pos.y + (tv * 48)));
			

		if (_inventory_items[i].sprIsHovered(mousepos))
		{
	

			if (_clicked) {
				equip_item(_inventory_items[i]);
			
			}


			if (_rclicked) {
				_inventory_items[i].setsellable();
				clear_inventory();

			}

			//am besten nur ssetzen wenn geklickt wird aber dann 
			//kann es sein, das item an spieler vorbeifliegt wenn spieler sich bewegt.


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
		dmg += _equip_items[i].getStats().atk;
		def += _equip_items[i].getStats().def;
		krit += _equip_items[i].getStats().krit;
		intellekt += _equip_items[i].getStats().iq;

	}


	atribs.setEquipStats(dmg, def, intellekt, krit,0);


}

//update the dropped items on the ground
void Items::update(sf::Time elapsed, sf::Vector2i mousepos ,
	sf::Vector2f playerpos, Attributs &atribs)
{
	playerstats_inkrement_from_equ(atribs);
	t_stats.setString(get_eq_stats_as_string(atribs));

	for (std::size_t i = 0; i < _vitems.size(); ++i)
	{
		

		_vitems[i].update(elapsed, playerpos, mousepos);

	}

}

std::vector<std::vector<float>> Items::getItemStats()
{
	std::vector<std::vector<float>> items;

	std::vector<float> buffer;


	for (auto  &w : _inventory_items)
	{
		buffer = w.getItemStats();
		items.push_back(buffer);
	}

	return items;
}

void Items::getklick(sf::Vector2i mousepos)
{

	for (std::size_t i = 0; i < _vitems.size(); ++i)
	{

		if (_vitems[i].getSprite().getGlobalBounds().contains(sf::Vector2f(mousepos)))
		{
			_vitems[i].activatetarget();
		}
	}
}

//clear ground iutem verktor and put it in the players inventory!
void Items::clear_item_vector()
{
	for (int i = 0; i < _vitems.size(); i++) {

		if (_vitems[i].isdestroyable()) {
			



			if (_inventory_items.size() < 30) {

				_inventory_items.push_back(_vitems[i]);
				_vitems.erase(_vitems.begin() + i);
			}
			else {
				_vitems[i].setnotdestroy();
				_vitems[i].turnofftarget();
			

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

		if (_inventory_items[i].issellable()) {

			int price = (_inventory_items[i].getStats().atk + _inventory_items[i].getStats().def * _inventory_items[i].getStats().krit);
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
		dmg += _equip_items[i].getStats().atk;

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

	if (item.type == EquipType::Sword) {
		_sword = item.getid();
	
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




