#pragma once


#include <memory>
#include "Entity.h"
#include "PlayerWeapon.h"
# define M_PI       3.14159265358979323846

/*evtl einfach einen item vektor hier reinmachen 
der ueber eine funktion items mit pushback reinmacht und schaut
ob iventar voll ist, dann noch eine funktion die den müll anzeigt und
evtl einen bool auf inventar aktiviert setzt*/


//später implementieren


class Player : public Entity
{


public:


	PlayerWeapon *playerweapon;
	Player(sf::Vector2f spawnpos, sf::Texture const *_playertex, sf::Texture const *weaponTexture);
	virtual ~Player();

	void initAnimations(const sf::Texture *tex);
	void move(const float dir_x, const float dir_y, const float &dt);


	void Attack() { playerweapon->start_attack();
	playerweapon->currentattackdir = direction;
	}

	void update(sf::Time elapsed, sf::Vector2f ownerPos) ;
	void setKeys(sf::Keyboard::Key u, sf::Keyboard::Key d, sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key s);
	void draw(sf::RenderWindow& target) ;

	void setplayerpos(sf::Vector2f const pos);
	void hurt(int dmg);
	bool got_dmg() { return Bgotdmg; }


	


	bool is_attacking();

	sf::Vector2f getviewsetoff(sf::Vector2f playerpos, int mapwidth,int mapheight);
	sf::Vector2f getviewsetoff_right(sf::Vector2f playerpos, int mapwidth, int mapheight);
	
	sf::Time _elapsed;


	float getAngleToTarget(sf::Vector2f target);


	//1up,2daown,3left,4right
	int returnplayer_direction() {	return direction;	}


	bool CanSpell();
	bool HaveEnoughMana(unsigned const int spellcost);
	void ResetCastTimer() { CastTimer = CastTimer.Zero; };
	void initStats();

	float angleForWeapon = 0;
	
private:

	bool isdefending = false;
	bool Bgotdmg = false;
	bool drawWeaponBehind = false;

	//im prinzip pointer dem man tastne zu weisen kann
	sf::Keyboard::Key kUp, kDown, kLeft, kRight, kShoot;


	sf::Time blinktimer;
	sf::Time CastTimer;
	
	
};

