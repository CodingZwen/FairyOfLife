#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <sstream>

//drop zufallszahl abhängig von spieler maschen
//damit seltenere sache im verhaeltnis droppen koennen
	
enum class Rarity {WHITE,GREEN,BLUE,
PURPLE,GOLD,GREY};

enum EquipType { Weapon, Shield,
Head, Chest, Boots, 
Amulet, Ring1,Ring2  };

struct Stats {
	int atk = 0;
	int def = 0;
	int speed = 0;
	int iq = 0;
	float krit = 0.f;
	
	Stats& operator=(const Stats &right)
	{
		atk = right.atk;
		def = right.def;
		speed = right.def;
		iq = right.iq;
		krit = right.krit;

		return *this;
	}
	
};

class Item
{
	//its possible to have two same ids
	//with different stats currently
	//its basically the number of the field
	//on the spritesheet
	
	Stats stats;
	unsigned int id;
	sf::Sprite itemSprite;
	sf::RectangleShape rect;
	sf::RectangleShape textBackground;
	sf::Text itemName;
	sf::Text itemDescription; //stats etc
	bool havetarget = false;
	bool showdescription = false;
	bool todestroy = false;
	bool tosell = false;
	bool equipped = false;

	sf::Vector2f velocity;
	float textboxoffset = 40;

public:
	EquipType type;
	Rarity rarity;
	

	explicit Item(unsigned int ID, 	
		int atk, int def,
		int speed, int iq, float krit,Rarity rarity,
		sf::Vector2f spawnPos,	sf::Sprite &spr,sf::Font *font);

	Item();
	~Item();


	void update(sf::Time elapsed, sf::FloatRect player, sf::Vector2i mousepos);
	void draw(sf::RenderTarget &target);

	Item& operator= (const Item left);

	void drawDescription(sf::RenderTarget &target);
	void drawOnlySprite(sf::RenderTarget &target);

	static  std::string get_description_string(std::string art, int atk, int def, int speed, int iq);
	sf::Vector2f getVelocityToTarget(const sf::Vector2f &targetPos);


	bool sprIsHovered(sf::Vector2i const mousepos);
	bool descriptrectIsHovered(sf::Vector2i const mousepos);
	bool isdestroyable() { return todestroy; }
	bool issellable() { return tosell; }
	void setPosition(sf::Vector2f pos);
	void setVelocity(sf::Vector2f velo);
	void setVelocityToTarget(sf::Vector2f Targetpos);

	sf::Sprite &getSprite();
	const Stats &getStats();
	const unsigned int &getid() { return id; }

	void destroy() { todestroy = true; }
	void setnotdestroy() { todestroy = false; }
	void setsellable() { tosell = true; }
	void activatetarget() { havetarget = true; }

	void setItemRarity(const char *weaponrarity);


	void setWeaponType(const char *weapontype);


	   
	void turnofftarget();
	void descriptionON();
	void descriptionOFF();



	template<typename T>
	T getName() {
		return T;
	}

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

	void setID(int ID);


	 std::string getItemasString();
	 std::vector<float> getItemStats();


};



