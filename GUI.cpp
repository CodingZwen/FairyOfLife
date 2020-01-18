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
	
	target.draw(txtMoney);
	target.draw(smoney);

	
	playerframe.draw(target);
	skillframe.draw(target);
	optionframe->draw(target);
}

void GUI::update(sf::Vector2f const & _viewPos, sf::Time elapsed, sf::Vector2f &mousepos)
{
	viewPos = _viewPos;


	update_money(elapsed);
	
	skillframe.update(mousepos);
	playerframe.update(_viewPos, elapsed, ptrplayer); //playerframe

	txtMoney.setPosition(viewPos.x - 455, viewPos.y + 245);
	smoney.setPosition(viewPos.x - 485, viewPos.y + 255);


	optionframe->update(mousepos);

}

void GUI::init(AssetManager *AM, SoundHandler *sh,
	Player *player, sf::RenderTarget &t, FileMaker &fm, Game &g)
{
	ptrplayer = player;
	ptrSoundhandler = sh;

	txtMoney.setFont(*AM->ptr_GetFont("font"));
	initTxtMoney();
	smoney.setTexture(AM->GetTexture("diamondanimation"));
	string_money = "0";


	   
	setKeys(sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3,
		sf::Keyboard::Num4, sf::Keyboard::Num5);

	setKeys_second(sf::Keyboard::Numpad1, sf::Keyboard::Numpad2, sf::Keyboard::Numpad3,
		sf::Keyboard::Numpad4, sf::Keyboard::Numpad5);


	skillframe.init(AM, viewPos);
	playerframe.init(AM, sh);



	optionframe = make_shared<OptionsFrame>();

	optionframe->init(&AM->GetTexture("optionframe"),t,fm,
		AM->ptr_GetFont("font"));
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
		return skillframe.getSkillslot(0);

	}

	else if (sf::Keyboard::isKeyPressed(_k2) || sf::Keyboard::isKeyPressed(_k7)) {

		return skillframe.getSkillslot(1);
	}

	else if (sf::Keyboard::isKeyPressed(_k3) || sf::Keyboard::isKeyPressed(_k8)) {

		return skillframe.getSkillslot(2);

	}

	else if (sf::Keyboard::isKeyPressed(_k4) || sf::Keyboard::isKeyPressed(_k9)) {

		return skillframe.getSkillslot(3);

	}

	else if (sf::Keyboard::isKeyPressed(_k5) || sf::Keyboard::isKeyPressed(_k10)) {

		return skillframe.getSkillslot(4);
	}
	else {

		//printf("kein gültiger knopf!\n");
		return 66;
	}
}

void GUI::PickNewSkill()
{
	skillframe.getChoosenSkill();
}

void GUI::SetNewSkill()
{
	skillframe.putSkillinBar();
}

void GUI::toggleSkillmenue()
{
	skillframe.ToggleSkillMenue();
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

OptionsFrame * GUI::getOptionframe() const
{
	return optionframe.get();
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


