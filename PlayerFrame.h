#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h" //aus den dingern muss ich unbedingt noch ein singleton mahen
#include "SoundHandler.h"
#include "Player.h"
class PlayerFrame
{

	sf::Font *font;

	float hpsize;
	float manasize;

	sf::Sprite sprPlayerframe;
	sf::Text txtHp;
	sf::Text txtMana;
	sf::Text lvtxt;

	std::string levelstring;

	sf::RectangleShape _ausdauer;
	sf::ConvexShape _hp; //parallelogram
	sf::ConvexShape _mana;//parallelogram
	sf::VertexArray xp; // 10-eck

public:
	PlayerFrame();
	~PlayerFrame();

	//am brauch const return...
	void init(AssetManager *as,const SoundHandler *sh);
	void initHpBar();
	void initManaBar();
	void initXpBar();
	void initStamina();
	void initTexts(AssetManager *as);

	void draw(sf::RenderTarget &t);
	void update(sf::Vector2f const & _viewPos, sf::Time elapsed, Player *player);
	void updateBars( Player *player);


	void reduceMana(int currentMp, int maxMp);
	void reduceHealth(int dmg, int hp);

	void fillXpBar(int percent);


	//kriegti mmer den spieler, vielleicht anders machen mit view oder so
	void setXpBarViewCenter(const sf::Vector2f pos);
	void setHpString(unsigned int takendmg, unsigned int maxhp);
	void setManaString(unsigned int drownmana, unsigned int maxmana);
	void setLevelString(unsigned int level);

};

