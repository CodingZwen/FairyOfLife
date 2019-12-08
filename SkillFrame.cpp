#include "SkillFrame.h"



SkillFrame::SkillFrame()
{
}


SkillFrame::~SkillFrame()
{
}

void SkillFrame::draw(sf::RenderTarget & t)
{
	int tu, tv;
	

	//leiste unten 
	for (int x = 0; x < 5; x++) {

		tu = zauber[x] % (240 / 48); // x 1  
		tv = zauber[x] / (240 / 48); //  y 2 

		sprSkillset.setPosition(sf::Vector2f((viewPos->x - 110) + (x * 48), viewPos->y + 238));

		sprSkillset.setTextureRect(sf::IntRect(tu * 48, tv * 48, 48, 48));
		t.draw(sprSkillset);
	}




	t.draw(sprDragDrop);

	showSkillMenue ? drawSkillMenue(t) : false;

}

void SkillFrame::drawSkillMenue(sf::RenderTarget & t)
{
	t.draw(sprSkillMenue);
	
	for (unsigned int i = 0; i < vSkillMenueElements.size(); i++) {
		t.draw(vSkillMenueElements[i]);
	}
}

void SkillFrame::update(sf::Vector2f &mousepos)
{
	sprSkillMenue.setPosition(sf::Vector2f(viewPos->x - 350, viewPos->y - 250));

	for (int i = 0; i < 15; i++) {

		int tu = i % 6;
		int tv = i / 6;

		vSkillMenueElements[i].setPosition((sprSkillMenue.getPosition().x + 10) + (tu * 50), (sprSkillMenue.getPosition().y + 80) + (tv * 130));
	}

	for (int s = 0; s < 5; s++) {
		_skillgetter[s].setPosition((viewPos->x - 110) + (s * 48), viewPos->y + 238);

	}

	
	sprDragDrop.setPosition(mousepos);
}

void SkillFrame::changeSkills(int pos, int spellid)
{
	if (!bDragDropHaveSpell)return;

	if (pos >= 5 || spellid > 15) {
		printf("soviele skills hat die leiste garnicht!\n");
	}
	else {

		zauber[pos] = spellid;
	}
}

void SkillFrame::getChoosenSkill()
{
	choosenspell = setDragDropSprite();
}

void SkillFrame::putSkillinBar()
{
	//0-4						//0-11
	changeSkills(getCollidingSkillBarSlotDragDrop(), choosenspell);
	CleanDragDrop();
}



void SkillFrame::init(AssetManager *AM, sf::Vector2f &viewpos)
{
	viewPos = &viewpos;
	sprSkillMenue.setTexture(AM->GetTexture("skillmenueframe"));
	sprSkillset.setTexture(AM->GetTexture("skillbarframe"));

	initDragDropSprites(AM);


	for (int i = 0; i < 5; i++) {

		_skillgetter[i].setSize(sf::Vector2f(50, 50));
		_skillgetter[i].setFillColor(sf::Color(255, 0, 0, 200));

	}

}

void SkillFrame::initDragDropSprites(AssetManager * AM)
{
	sf::Sprite sp;
	sp.setTexture(AM->GetTexture("skillmenueSpellSprites"));
	//48, 192
	int tilesize = 48;
	int pixelwidth_tileset = 192;

	for (int i = 0; i < 15; i++) {

		int tu = i % (pixelwidth_tileset / tilesize);
		int tv = i / (pixelwidth_tileset / tilesize);

		sp.setTextureRect(sf::IntRect(tu * tilesize, tv * tilesize, tilesize, tilesize));

		sp.setPosition(i * 50.f, 0);

		vSkillMenueElements.push_back(sp);

	}

}

 int SkillFrame::getSkillslot(unsigned int slot)
{
	if (slot > 4)return -1;

	return zauber[slot];

}

 int SkillFrame::getCollidingSkillBarSlotDragDrop()
 {
	 for (int i = 0; i < 5; i++) {

		 if (_skillgetter[i].getGlobalBounds().contains(sprDragDrop.getPosition().x, sprDragDrop.getPosition().y)) {
			 printf("erfolgreich kollidiert mit feld: %d\n", i);
			 return i;

		 }

	 }

	 return 8;
 }


int SkillFrame::setDragDropSprite()
{
	int spellid = 0;

	for (unsigned int i = 0; i < vSkillMenueElements.size(); i++) {

		if (vSkillMenueElements[i].getGlobalBounds().contains(sprDragDrop.getPosition().x, sprDragDrop.getPosition().y)) {

			sprDragDrop = vSkillMenueElements[i];
			bDragDropHaveSpell = true;
			return i;
		}

	}
	bDragDropHaveSpell = false;
	return 0;
}
