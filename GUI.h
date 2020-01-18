#pragma once
#include "Entity.h"
#include "AssetManager.h"
#include "SoundHandler.h"
#include "PlayerFrame.h"
#include "Player.h"
#include "SkillFrame.h"
#include "OptionsFrame.h"
class GUI
{
	SoundHandler *ptrSoundhandler;
	Player *ptrplayer = 0;
	sf::Keyboard::Key _k1, _k2, _k3, _k4, _k5, _k6, _k7, _k8, _k9, _k10;
	sf::Vector2f viewPos;
	std::shared_ptr<OptionsFrame> optionframe;
	
public:
	GUI();
	~GUI();
	
	int return_choosen_spell();
	void PickNewSkill();
	void SetNewSkill();
	void toggleSkillmenue();

	void init(AssetManager *AM, SoundHandler *sh,
		Player *player, sf::RenderTarget &t, FileMaker &fm, Game &g);

	void draw(sf::RenderTarget& target);
	void update(sf::Vector2f const &viewPos, sf::Time elapsed,sf::Vector2f &mousepos);
	

	void setKeys(sf::Keyboard::Key k1, sf::Keyboard::Key k2, sf::Keyboard::Key k3, sf::Keyboard::Key k4, sf::Keyboard::Key k5);
	void setKeys_second(sf::Keyboard::Key k6, sf::Keyboard::Key k7, sf::Keyboard::Key k8, sf::Keyboard::Key k9, sf::Keyboard::Key k10);

	void update_money(sf::Time elapsed);
	void give_money(int _money);
	const unsigned int getmoney() const {  return money; }

	OptionsFrame *getOptionframe() const;
	
	   	 
private:

	void initTxtMoney();
	sf::Text txtMoney;
	
	//money muss noch als klasse erstellt werden
	int frame, frames=6,money=0;
	std::string string_money;
	sf::Sprite smoney;
	sf::Time _elapsed;

	PlayerFrame playerframe;
	SkillFrame skillframe;

};

