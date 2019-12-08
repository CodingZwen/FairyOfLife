#include "PlayerFrame.h"



PlayerFrame::PlayerFrame()
{
}


PlayerFrame::~PlayerFrame()
{
}

void PlayerFrame::init( AssetManager * AM, const SoundHandler * sh)
{
	initHpBar();
	initManaBar();
	initXpBar();

	sprPlayerframe.setTexture(AM->GetTexture("playerframe"));
	sprPlayerframe.setTextureRect(sf::IntRect(0, 0, 224, 96));
	sprPlayerframe.setPosition(0, 0);

	initTexts(AM);
}

void PlayerFrame::initHpBar()
{

	_hp.setPointCount(4);
	_hp.setPoint(0, sf::Vector2f(9, 0));
	_hp.setPoint(1, sf::Vector2f(140, 0));
	_hp.setPoint(2, sf::Vector2f(158, 19));
	_hp.setPoint(3, sf::Vector2f(28, 19));

	_hp.setFillColor(sf::Color(202, 19, 19, 120));
	_hp.setOutlineThickness(-2);
	_hp.setOutlineColor(sf::Color(247, 37, 37));
	hpsize = 119;
}

void PlayerFrame::initManaBar()
{
	_mana.setPointCount(4);
	_mana.setPoint(0, sf::Vector2f(26, 0));
	_mana.setPoint(1, sf::Vector2f(155, 0));
	_mana.setPoint(2, sf::Vector2f(143, 11));
	_mana.setPoint(3, sf::Vector2f(15, 11));

	_mana.setFillColor(sf::Color(0, 0, 240, 120));
	_mana.setOutlineThickness(-2);
	_mana.setOutlineColor(sf::Color(37, 37, 240));
	manasize = 130;
}

void PlayerFrame::initXpBar()
{
		
	xp = sf::VertexArray(sf::TriangleStrip, 10);
	   
	xp[0].color = sf::Color(255, 110, 110, 55);
	xp[1].color = sf::Color(255, 50, 110, 55);

	xp[2].color = sf::Color(175, 255, 50, 55);
	xp[3].color = sf::Color(175, 255, 50, 55);

	xp[4].color = sf::Color(30, 30, 255, 55);
	xp[5].color = sf::Color(30, 30, 255, 55);

	xp[6].color = sf::Color(110, 212, 255, 55);
	xp[7].color = sf::Color(110, 212, 255, 55);

	xp[8].color = sf::Color(255, 77, 182, 55);
	xp[9].color = sf::Color(255, 77, 182, 55);

}

void PlayerFrame::initStamina()
{
	_ausdauer.setSize(sf::Vector2f(90, 16));
	_ausdauer.setFillColor(sf::Color(0, 220, 0, 120));
}

void PlayerFrame::initTexts(AssetManager *AM)
{
	levelstring = "Lv: 1";
	lvtxt.setFont(*AM->ptr_GetFont("font"));
	lvtxt.setPosition(0, 0);
	lvtxt.setCharacterSize(14);
	lvtxt.setFillColor(sf::Color(40, 40, 40));
	lvtxt.setOutlineColor(sf::Color::White);
	lvtxt.setOutlineThickness(1);
	lvtxt.setString(levelstring);


	txtHp.setFont(*AM->ptr_GetFont("font"));
	txtHp.setPosition(0, 0);
	txtHp.setCharacterSize(12);
	txtHp.setFillColor(sf::Color(40, 40, 40));
	txtHp.setOutlineColor(sf::Color::White);
	txtHp.setOutlineThickness(1);
	txtHp.setString("");

	txtMana.setFont(*AM->ptr_GetFont("font"));
	txtMana.setPosition(0, 0);
	txtMana.setCharacterSize(12);
	txtMana.setFillColor(sf::Color(40, 40, 40));
	txtMana.setOutlineColor(sf::Color::White);
	txtMana.setOutlineThickness(1);
	txtMana.setString("54654");




}

void PlayerFrame::draw(sf::RenderTarget & target)
{
	target.draw(xp);

	target.draw(sprPlayerframe);
	target.draw(_hp);
	target.draw(_mana);
	target.draw(_ausdauer);
	target.draw(lvtxt);
	target.draw(txtHp);
	target.draw(txtMana);
}

void PlayerFrame::update(sf::Vector2f const & _viewPos, sf::Time elapsed, Player *player)
{
	sprPlayerframe.setPosition(_viewPos.x - 500, _viewPos.y - 300); //sprite von lebensanzeige obenlinks
	
	_hp.setPosition(_viewPos.x - 441, _viewPos.y - 274);
	_mana.setPosition(_viewPos.x - 439, _viewPos.y - 248);

	setXpBarViewCenter(_viewPos);

	lvtxt.setPosition(_viewPos.x - 470, _viewPos.y - 260);

	txtHp.setPosition(_viewPos.x - 392, _viewPos.y - 271);
	txtMana.setPosition(_viewPos.x - 392, _viewPos.y - 251);

	updateBars(player);

}

void PlayerFrame::updateBars(Player * player)
{
	if (player->attributs.isalive()) {

		reduceHealth(player->attributs.getTakenDmg(), player->attributs.getMaxHp());
		reduceMana(player->attributs.getCurrentMana(), player->attributs.getMaxMana());

		setHpString(player->attributs.getMaxHp() - player->attributs.getTakenDmg(), player->attributs.getMaxHp());
		setManaString(player->attributs.getCurrentMana(), player->attributs.getMaxMana());

	}
	
}

void PlayerFrame::reduceMana(int currentMp, int maxMp)
{

	float ergebnis = manasize / maxMp * currentMp;
	float ergebnis2 = manasize - ergebnis;

	_mana.setPoint(1, sf::Vector2f(155 - ergebnis2, 0));
	_mana.setPoint(2, sf::Vector2f(143 - ergebnis2, 11));

}

void PlayerFrame::reduceHealth(int dmg, int hp)
{
	float ergebnis2 = hpsize / hp * dmg;
	//ergebnis2 *= einprozent;


	//printf("das ist ergebnis zwei: %.5f", ergebnis2);

	//_hp.setScale(sf::Vector2f((_hp.getScale().x - ergebnis2), _hp.getScale().y));

	_hp.setPoint(1, sf::Vector2f(140 - ergebnis2, 0));
	_hp.setPoint(2, sf::Vector2f(158 - ergebnis2, 19));
}

void PlayerFrame::fillXpBar(int percent)
{
	if (percent > 100 || percent < 1)return;

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

}

void PlayerFrame::setXpBarViewCenter(const sf::Vector2f pos)
{
	sf::Vector2f buffer = pos;
	buffer.x -= 553;
	buffer.y -= 288;

	xp[0].position = sf::Vector2f(buffer.x + 100, buffer.y);
	xp[1].position = sf::Vector2f(buffer.x + 100, buffer.y + 10);
	xp[2].position = sf::Vector2f(buffer.x + 60, buffer.y + 35);
	xp[3].position = sf::Vector2f(buffer.x + 70, buffer.y + 35);
	xp[4].position = sf::Vector2f(buffer.x + 100, buffer.y + 75);
	xp[5].position = sf::Vector2f(buffer.x + 100, buffer.y + 67);
	xp[6].position = sf::Vector2f(buffer.x + 139, buffer.y + 36);
	xp[7].position = sf::Vector2f(buffer.x + 127, buffer.y + 36);
	xp[8].position = sf::Vector2f(buffer.x + 102, buffer.y);
	xp[9].position = sf::Vector2f(buffer.x + 102, buffer.y + 10);

}

void PlayerFrame::setHpString(unsigned int takendmg, unsigned int maxhp)
{
	string str = std::to_string(takendmg);
	str += " / ";
	str += std::to_string(maxhp);
	txtHp.setString(str);
}

void PlayerFrame::setManaString(unsigned int drownmana, unsigned int maxmana)
{
	string str = std::to_string(drownmana);
	str += " / ";
	str += std::to_string(maxmana);
	txtMana.setString(str);
}

void PlayerFrame::setLevelString(unsigned int level)
{
	levelstring = "Lv: ";
	levelstring += std::to_string(level);
	lvtxt.setString(levelstring);

}
