#include "GUI.h"

/*gui ist 
xp anzeige hp anzeige mana anzeige
geld anzeige
skillbar unten anzeige


*/

GUI::GUI()
{
	viewPos = sf::Vector2f(0, 0);
}


GUI::~GUI()
{
}


//skillbar unten
void GUI::draw(sf::RenderTarget & target)
{
	int tu, tv;
	//sf::Vector2i window = target.mapPixelToCoords();

	for (int x = 0; x < 5; x++) {

		 tu = zauber[x] % (240 / 48); // x 1  
		 tv = zauber[x] / (240 / 48); //  y 2 

		 s_skillset.setPosition(sf::Vector2f((viewPos.x - 110) + (x * 48), viewPos.y + 238));

		s_skillset.setTextureRect(sf::IntRect(tu * 48, tv * 48, 48, 48));
		target.draw(s_skillset);
	}

	
	target.draw(xp);


	target.draw(sprPlayerframe);
	target.draw(_hp);
	target.draw(_mana);
	//target.draw(_ausdauer);
	target.draw(txtMoney);
	target.draw(lvtxt);
	target.draw(smoney);
	target.draw(txtHp);
	target.draw(txtMana);

	showSkillMenue ? drawSkillMenue(target) : false;


}


//hier war hp etc als parameter, aber am besten nicht die ganze zeit
//übergeben sondern einma´l ändern bzw eine funktion schreiben die dass entsprechend ändert
//und diese dan nauch nur aufrufen wenn werte geändert werden
void GUI::update(sf::Vector2f const & _viewPos, sf::Time elapsed, sf::Vector2f mousepos)
{
	update_money(elapsed);
	sprSkillMenue.setPosition(sf::Vector2f(_viewPos.x - 350, _viewPos.y - 250));
	updateSkillMenueSprites(_viewPos);

	
	//hier vielleicht window übergeben und anhand den zahlen 
	//die posis setzen
	viewPos = _viewPos;

	sprPlayerframe.setPosition(viewPos.x - 500, viewPos.y - 300); //sprite von lebensanzeige obenlinks
	
	setvertexpos(viewPos);
	
	_hp.setPosition(viewPos.x - 441, viewPos.y - 274);
	_mana.setPosition(viewPos.x - 439, viewPos.y - 248);
	_ausdauer.setPosition(viewPos.x - 405, viewPos.y - 240);
	txtMoney.setPosition(viewPos.x - 455, viewPos.y + 245);
	lvtxt.setPosition(viewPos.x - 470, viewPos.y - 260);

	smoney.setPosition(viewPos.x - 485, viewPos.y + 255);
	txtHp.setPosition(viewPos.x - 392, viewPos.y - 271);
	txtMana.setPosition(viewPos.x - 392, viewPos.y - 251);

	sprDragDrop.setPosition(mousepos);


}

void GUI::init(AssetManager *AM, SoundHandler *sh)
{

	ptrSoundhandler = sh;
	initHpVertices();
    initManaVertices();
	initXPVertices();

	
	sprPlayerframe.setTexture(AM->GetTexture("playerframe"));
	sprPlayerframe.setTextureRect(sf::IntRect(0, 0, 224, 96));
	sprPlayerframe.setPosition(0, 0);
	
	txtMoney.setFont(*AM->ptr_GetFont("font"));
	initTxtMoney();
	
	sprSkillMenue.setTexture(AM->GetTexture("skillmenueframe"));
	
	initSkillMenueElements(AM);

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

	



	s_skillset.setTexture(AM->GetTexture("skillbarframe"));
	smoney.setTexture(AM->GetTexture("diamondanimation"));
	

	setKeys(sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3,
	     	sf::Keyboard::Num4, sf::Keyboard::Num5);

	setKeys_second(sf::Keyboard::Numpad1, sf::Keyboard::Numpad2, sf::Keyboard::Numpad3,
	    	sf::Keyboard::Numpad4, sf::Keyboard::Numpad5);


	string_money = "0";

	

	for (int i = 0; i < 5; i++) {

		_skillgetter[i].setFillColor(sf::Color(100, 100, 100, 100));
		_skillgetter[i].setSize(sf::Vector2f(50, 50));
		_skillgetter[i].setFillColor(sf::Color(255, 0, 0, 200));



	}


}


void GUI::setKeys(sf::Keyboard::Key k1, sf::Keyboard::Key k2, sf::Keyboard::Key k3, sf::Keyboard::Key k4, sf::Keyboard::Key k5)
{

	_k1 = k1;
	_k2 = k2;
	_k3 = k3;
	_k4 = k4;
	_k5 = k5;


}

int GUI::return_choosen_spell()
{
	if (sf::Keyboard::isKeyPressed(_k1) || sf::Keyboard::isKeyPressed(_k6)) {

		//printf("zauber 1 kommt ::%d\n", zauber[0]);
		return zauber[0];

	}

	else if (sf::Keyboard::isKeyPressed(_k2) || sf::Keyboard::isKeyPressed(_k7)) {

		return zauber[1];

	}

	else if (sf::Keyboard::isKeyPressed(_k3) || sf::Keyboard::isKeyPressed(_k8)) {

		return zauber[2];

	}

	else if (sf::Keyboard::isKeyPressed(_k4) || sf::Keyboard::isKeyPressed(_k9)) {

		return zauber[3];

	}

	else if (sf::Keyboard::isKeyPressed(_k5) || sf::Keyboard::isKeyPressed(_k10)) {

		return zauber[4];

	}
	else {

		//printf("kein gültiger knopf!\n");
		return 66;
	}
}

void GUI::setKeys_second(sf::Keyboard::Key k6, sf::Keyboard::Key k7, sf::Keyboard::Key k8, sf::Keyboard::Key k9, sf::Keyboard::Key k10)
{
	_k6 = k6;
	_k7 = k7;
	_k8 = k8;
	_k9 = k9;
	_k10 = k10;
}

void GUI::update_money(sf::Time elapsed)
{
	_elapsed += elapsed; //zählt mit wieviel zeit vergangen ist

	if (_elapsed.asSeconds() > 0.11) { //wenn halbe sekundew vorbei springen wir ein frame
		if (frame < frames - 1)
		{
			frame++;
		}
		else {
			frame = 0;
		}

		_elapsed = _elapsed.Zero;
		smoney.setTextureRect(sf::IntRect(24 * frame, 0, 24, 24));

	}

	


}

void GUI::give_money(int _money)
{
	money += _money;
	txtMoney.setString(std::to_string(money));
	ptrSoundhandler->playSound("Kachingsound");

}

void GUI::reduce_hp_bar(int dmg, int hp)
{
	
	float ergebnis2 = hpsize / hp*dmg;
	//ergebnis2 *= einprozent;
	

	//printf("das ist ergebnis zwei: %.5f", ergebnis2);

	//_hp.setScale(sf::Vector2f((_hp.getScale().x - ergebnis2), _hp.getScale().y));

	_hp.setPoint(1, sf::Vector2f(140-ergebnis2, 0));
	_hp.setPoint(2, sf::Vector2f(158- ergebnis2, 19));
	

}
void GUI::reduce_mana_bar(int usedmana, int mp)
{
	//mana =100 benutzes mana = 20 mana size=200
	//-> 200 / 100 = 2 * 20 = 40 -> 40 pixel werden jetzt von max groese abgezogen
	//130 / 1000 * 900
	float ergebnis2 = manasize / mp * usedmana;

	_mana.setPoint(1, sf::Vector2f(155 - ergebnis2, 0));
	_mana.setPoint(2, sf::Vector2f(143 - ergebnis2, 11));

}

void GUI::reduce_mana_bar_alt(int currentMp, int Maxmp)
{
	//mana = 100 benutzes 

	float ergebnis = manasize / Maxmp * currentMp;
	float ergebnis2 = manasize - ergebnis;

	_mana.setPoint(1, sf::Vector2f(155 - ergebnis2, 0));
	_mana.setPoint(2, sf::Vector2f(143 - ergebnis2, 11));

}

void GUI::initHpVertices()
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

void GUI::initManaVertices()
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

void GUI::setvertexpos(sf::Vector2f pos)
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

void GUI::fillxpbar(int percent)
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

void GUI::setHpString(unsigned int takendmg, unsigned int maxhp)
{
	string str = std::to_string(takendmg);
	str += " / ";
	str += std::to_string(maxhp);
	txtHp.setString(str);
}

void GUI::setManaString(unsigned int drownmana, unsigned int maxmana)
{
	string str = std::to_string(drownmana);
	str += " / ";
	str += std::to_string(maxmana);
	txtMana.setString(str);
}

void GUI::drawSkillMenue(sf::RenderTarget & t)
{

	t.draw(sprSkillMenue);

	for (int i = 0; i < vSkillMenueElements.size(); i++) {
		t.draw(vSkillMenueElements[i]);
	}

	/*for (int s = 0; s < 5; s++) {
		t.draw(_skillgetter[s]);
	}
	*/
	t.draw(sprDragDrop);
	
}



void GUI::initXPVertices()
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

void GUI::initStaminaVertices()
{
	_ausdauer.setSize(sf::Vector2f(90, 16));
	_ausdauer.setFillColor(sf::Color(0, 220, 0, 120));
}

void GUI::initTxtMoney()
{
	txtMoney.setPosition(0, 0);
	txtMoney.setString("0");
	txtMoney.setCharacterSize(20);
	txtMoney.setFillColor(sf::Color(5, 186, 246));
	txtMoney.setOutlineColor(sf::Color::White);
	txtMoney.setOutlineThickness(1);

}

void GUI::initSkillMenueElements(AssetManager *AM)
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
	
		sp.setPosition(i * 50, 0);

		vSkillMenueElements.push_back(sp);

	}

}

void GUI::updateSkillMenueSprites(sf::Vector2f viewpos)
{
	for (int i = 0; i < 15; i++) {

		int tu = i % 6;
		int tv = i / 6;
		
		vSkillMenueElements[i].setPosition((sprSkillMenue.getPosition().x + 10) + (tu * 50), (sprSkillMenue.getPosition().y + 80) + (tv * 130));
	
	
	}

	for (int s = 0; s < 5; s++) {
		_skillgetter[s].setPosition((viewPos.x - 110) + (s * 48), viewPos.y + 238);

	}
}

int GUI::getCollidingSkillBarSlotDragDrop()
{
	for (int i = 0; i < 5; i++) {

		if (_skillgetter[i].getGlobalBounds().contains(sprDragDrop.getPosition().x, sprDragDrop.getPosition().y)) {
			printf("erfolgreich kollidiert mit feld: %d\n", i);
			return i;

		}

	}
}


void GUI::change_skills(int pos, int spellid)
{
	//achtung hier war pos 0 wenn ich skill nicht in ein rect gezogen habe, dementsprechend
	//gab es eine zugrifsverletzung
	if (!bDragDropHaveSpell)return;

	if (pos >= 5 || spellid > 15) {
		printf("soviele skills hat die leiste garnicht!\n");
	}
	else {

		zauber[pos] = spellid;
	}
}


int GUI::setDragDropSprite()
{
	int spellid = 0;
	
	for (int i = 0; i < vSkillMenueElements.size(); i++) {

		if (vSkillMenueElements[i].getGlobalBounds().contains(sprDragDrop.getPosition().x, sprDragDrop.getPosition().y)) {

			sprDragDrop = vSkillMenueElements[i];
			bDragDropHaveSpell = true;
			return i;
			
		}
		
	}
	

		
		bDragDropHaveSpell = false;
		return 0;
	


}



/*



xp[0].color = sf::Color(255, 0, 0, 55);
xp[1].color = sf::Color(255,0,0,55);

xp[2].color = sf::Color(0, 255, 0, 55);
xp[3].color = sf::Color(0, 255, 0, 55);

xp[4].color = sf::Color(0, 0, 255, 55);
xp[5].color = sf::Color(0, 0, 255, 55);

xp[6].color = sf::Color(0, 212, 255, 55);
xp[7].color = sf::Color(0, 212, 255, 55);

xp[8].color = sf::Color(255, 0, 182, 55);
xp[9].color = sf::Color(255, 0, 182, 55);



void GUI::reduce_hp_bar(int dmg, int hp)
{

float ergebnis2 = hpsize / hp*dmg;
//ergebnis2 *= einprozent;

//printf("das ist ergebnis zwei: %.5f", ergebnis2);

//_hp.setScale(sf::Vector2f((_hp.getScale().x - ergebnis2), _hp.getScale().y));

_hp.setPoint(1, sf::Vector2f(_hp.getPoint(1).x-ergebnis2, 0));
_hp.setPoint(2, sf::Vector2f(_hp.getPoint(2).x - ergebnis2, 19));

}



*/


