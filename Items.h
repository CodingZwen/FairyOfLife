#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <math.h>
#include <string>

#include <chrono>
#include "AssetManager.h"
#include "Item.h"
#include "Attributs.h"

class Game;


struct Diamond {

	sf::RectangleShape rect;
	sf::IntRect irect;
	bool destroy, flying;
	sf::Vector2f velocity;
	bool hovered=false;

};


//rect groeser als das sprite machen dann kann man noch 
//text einfuegen
class Items
{

public:
	Items();
	~Items();

	void initSprites(AssetManager &am);

	bool loaditem(sf::Vector2f itempos, int itemnr, int Rarity=0);
	void draw(sf::RenderTarget &target);
	void draw_inventory(sf::RenderTarget &target);
	void draw_euqip(sf::RenderTarget &target);

	void draw_diamonds(sf::RenderTarget &target);

	bool load_diamond(sf::Vector2f pos,unsigned int  color);
	void animate_diamonds(sf::Time _elapsed);
	void diamond_all(sf::Vector2i mousepos, sf::Vector2f playerpos, sf::Time _elapsed);


	void update_diamonds(sf::Vector2i mousepos, sf::Vector2f playerpos);
	void update_equip(sf::Vector2i mousepos, sf::Vector2f playerpos);
	void update_inventory(sf::Time elapsed, sf::Vector2i mousepos, sf::Vector2f playerpos);
	void update(sf::Time elapsed,sf::Vector2i mousepos, sf::Vector2f playerpos, Attributs &atribs);

	std::vector<std::vector<float>> getItemStats();

	//nimmt attrib struct von spieler und errechnet aus der struct funktion
	//den string der für euqip anzeige benötigt wird
	std::string get_eq_stats_as_string(Attributs &atribs);

	//aktuliasiert von spieler das attribstruct bzw setzt die eqstats
	void playerstats_inkrement_from_equ(Attributs &atribs);



	void getklick(sf::Vector2i mousepos);
	void clear_item_vector();
	void clear_inventory();
	void clear_money_vector();
	int get_dmg_from_eq();

	

	//für item initalisierung
	std::string get_description_string(std::string art,int atk, int def, int speed, int iq);

	

	void left_klick() {
		_clicked = true;
	}


	void right_klick() {
		_rclicked = true;
		
	}

	void StartStopSelling() { _selling = !_selling; }
	bool is_selling() { return _selling; }



	sf::Vector2f getVelocityToTarget(const	sf::Vector2f &targetPos,
		const sf::Vector2f &itempos, sf::Time &elapsed);

	void equip_item(Item &item);
	int get_equipped_sword();
	bool got_money() { return _vselled_items.size() > 0 ? true : false ; }


	int get_earned_money() {

		int money =_vselled_items.at(0);
		_vselled_items.erase(_vselled_items.begin());
		return money;
	}

	void initScreenDimension(sf::Vector2i screenD);

private:

	sf::Vector2i screenDimension;
	
	sf::Sprite s_inventory;
	sf::Sprite s_itemsprite;
	sf::Sprite s_diamonds;
	sf::Sprite s_objectsprite;
	sf::Sprite s_equip;
	
	//charequip

	sf::Text t_stats;
	std::string s_stats;

	//diamonds bzw money

	sf::Time elapsed;

	int frame = 0, frames = 6;

	sf::Font font;

	//hier werden items zum ersten mal initalisiert und
	//aus diesem vektor heraus gezeichnet wenn sie aufm boden liegen
	std::vector<Item> _vitems;

	//Items die gesammelt wurden und im inventar liegen
	std::vector<Item> _inventory_items;
	
	//Ausgerüstete Items des Chars
	std::vector<Item> _equip_items;


	std::vector<sf::RectangleShape> _equiprects;

	//hier werden die preise der verkauften gegenständen abgeholt
	std::vector<int> _vselled_items;

	//testmoney
	std::vector<Diamond> vmoney;

	int _sword;
	int _tilesize;
	int _tilesizewidth_px;
	int saled_item_price = 0;
	bool _clicked = false;
	bool _rclicked = false;

	bool _selling = false;
};



/*klasse machen, die funktion übergeben und prüfen ob
enum schon vorhanden ist wenn ja ersestzen

oder poss anhand der enums setzen

*/