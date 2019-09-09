#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <string>
class PlayerWeapon 
{
	//large sausage -> sarge lausage
	std::string name;
	sf::Time elapsed;
	sf::Time attackTimer;
	sf::Vector2f currentPosition;
	sf::FloatRect collRect;
	

public:
	PlayerWeapon(const sf::Texture *texture);
	virtual ~PlayerWeapon();

	enum class hitdirection  { xx,up,down,left,right };

	void update(sf::Time _elapsed, sf::Vector2f ownerpos, float angle=0);
	void draw(sf::RenderWindow &window);
	void hurt(int dmg) {};
	void update_offset(int playerdirection);
	void change_weapon(int id);
	void start_attack() { attack = true; }
	void set_hitdirection(int dir) { if (dir > 4)return; currentattackdir = dir; }

	void hitleft(sf::Time elapsed);
	void hitdown(sf::Time elapsed);
	void hitright(sf::Time elapsed);
	void hitup(sf::Time elapsed);
		
	sf::FloatRect getCollRect() {return collRect;}

	bool attack;
	bool swing;
	int currentattackdir;

	Animation anim;
	


	float offsetangle;
	sf::Vector2f offset;
	sf::Vector2f attackoffset;

};

