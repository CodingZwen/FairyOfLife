#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "AssetManager.h"
#include "SoundHandler.h"


class GUI
{


	SoundHandler *ptrSoundhandler;
public:
	GUI();
	~GUI();
	
	void reduce_mana_bar_alt(int currentMp, int Maxmp);
	void draw(sf::RenderTarget& target);
	void update(sf::Vector2f const &viewPos, sf::Time elapsed,sf::Vector2f mousepos);
	void init(AssetManager *AM, SoundHandler *sh);
	void change_skills(int pos, int spellid);
	void setKeys(sf::Keyboard::Key k1, sf::Keyboard::Key k2, sf::Keyboard::Key k3, sf::Keyboard::Key k4, sf::Keyboard::Key k5);
	int return_choosen_spell();
	void setKeys_second(sf::Keyboard::Key k6, sf::Keyboard::Key k7, sf::Keyboard::Key k8, sf::Keyboard::Key k9, sf::Keyboard::Key k10);

	void update_money(sf::Time elapsed);
	void hide_lebensanzeige() { _hp.setScale(0, 0); }

	void give_money(int _money);

	void reduce_hp_bar(int dmg, int hp);
	void reduce_mana_bar(int usedmana, int mp);

	void change_levelstring(int level) {

		levelstring = "Lv: ";
		levelstring += std::to_string(level);
		lvtxt.setString(levelstring);

	}

	int zauber[5] = { 0,14,8,13,10 };


	sf::Keyboard::Key _k1, _k2, _k3, _k4, _k5, _k6, _k7, _k8, _k9, _k10;

	//sf::RectangleShape _hp;




	void setvertexpos(sf::Vector2f pos);

	void fillxpbar(int percent);


	sf::RectangleShape _ausdauer;

	sf::Font font;
	sf::Sprite s_skillset;
	
	sf::Vector2f viewPos;


	void setHpString(unsigned int takendmg, unsigned int maxhp);
	void setManaString(unsigned int drownmana, unsigned int maxmana);


	void ToggleSkillMenue() { showSkillMenue = !showSkillMenue; }


	int getCollidingSkillBarSlotDragDrop(); //getchoosenspell pendant

	int setDragDropSprite();
	void CleanDragDrop() { sf::Sprite spr; sprDragDrop = spr; bDragDropHaveSpell = false; }
private:

	void drawSkillMenue(sf::RenderTarget &t);
	void initHpVertices();
	void initManaVertices();
	void initXPVertices();
	void initStaminaVertices();
	void initTxtMoney();
	void initSkillMenueElements(AssetManager *AM);
	void updateSkillMenueSprites(sf::Vector2f viewpos);

	
	sf::Sprite sprPlayerframe;
	sf::Sprite sprSkillMenue;
	sf::Sprite sprDragDrop;
	
	std::vector<sf::Sprite> vSkillMenueElements;
	sf::RectangleShape _skillgetter[5];

	bool bDragDropHaveSpell = false;
	bool showSkillMenue = false;

	sf::ConvexShape _hp; //parallelogram
	sf::ConvexShape _mana;//parallelogram
	sf::VertexArray xp; // 10-eck
	

	sf::Text txtMoney;
	sf::Text txtHp;
	sf::Text txtMana;

	sf::Text lvtxt;
	std::string levelstring;

	float hpsize;
	float manasize;

	//moneyshit, eventzuell noch in eine einzelne klasse
	//uwamdenln
	int frame, frames=6,money=0;
	std::string string_money;
	sf::Sprite smoney;
	sf::Time _elapsed;

};



/*

if (percent > 100 || percent <1)return;

int xxp = percent;
int zahl = xxp % 10;
int ergebnis = xxp - zahl;
ergebnis /= 10;


for (int i = 0; i < 10; i++) {

xp[i].color.a = 55;
}


for (int i = 0; i < ergebnis; i++) {

xp[i].color.a = 255;
}


*/