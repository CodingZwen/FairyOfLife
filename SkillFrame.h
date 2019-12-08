#pragma once
#include "AssetManager.h"


class SkillFrame
{
	int zauber[5] = { 0,14,8,13,10 };
	int choosenspell = 0;
	bool bDragDropHaveSpell;
	bool showSkillMenue = false;

	sf::Sprite sprSkillset; // unten skillbar
	sf::Sprite sprSkillMenue; // skillauswahl
	sf::Sprite sprDragDrop; //

	std::vector<sf::Sprite> vSkillMenueElements; //für anzeige auf auswahl
	sf::RectangleShape _skillgetter[5];


	sf::Vector2f *viewPos; //points to viewpos of gui

	void CleanDragDrop() { sf::Sprite spr; sprDragDrop = spr; bDragDropHaveSpell = false; }


public:
	SkillFrame();
	~SkillFrame();

	void draw(sf::RenderTarget &t);
	void drawSkillMenue(sf::RenderTarget &t);
	void update(sf::Vector2f &mousepos);
	void changeSkills(int pos, int spellid);
	void getChoosenSkill();
	void putSkillinBar();

	void init(AssetManager *AM,sf::Vector2f &viewpos);
	void initDragDropSprites(AssetManager *AM);

	int getSkillslot(unsigned int slot);
	int getCollidingSkillBarSlotDragDrop();

	void ToggleSkillMenue() { showSkillMenue = !showSkillMenue; }


	int setDragDropSprite();
};

