#include "Attributs.h"



Attributs::Attributs()
{
	initStats();
}


Attributs::~Attributs()
{
}

void Attributs::update(float dt)
{
	regTimeBuffer += dt;

	if (currentHp < 0)kill();

	if (regTimeBuffer > 1.f)
	{
		if(currentMana<getMaxMana())currentMana+=manareg;
		if (currentHp < getMaxHp())
		{
			currentHp += hpreg;
			takendmg -= hpreg;
		}

		regTimeBuffer = 0;
		
	}
}

const unsigned short  Attributs::getHpAsPercent()
{
	//50hp -> 100 / 50 = 2 -> 1hp = 2% -> 2*currenthp = xx% life
	short OneHpPercent = 100 / getMaxHp();
	short currentPercent = currentHp * OneHpPercent;
	return currentPercent;
}

void Attributs::LevelUp()
{
	atk += 5;
	def += 3;
	iq += 3;
	krit += .5f;
	hp += 100;
	entitylevel++;
	takendmg = 0;
	currentMana = getMaxMana();
	currentHp = getMaxHp();


	if (casttime > 0.1f)
		casttime -= 0.1f;

}

void Attributs::hurt(const unsigned short damage)
{
	currentHp -= damage;
	takendmg += damage;
	if (currentHp < 0)isdead = true;

}

void Attributs::drainMana(unsigned short cost)
{
	if (cost < currentMana)
		currentMana -= cost;
	else;
}

void Attributs::initStats()
{
	atk = 5;
	def = 5;
	iq = 5;
	casttime  = 1.f;
	krit = 1.f;
	hp = 100;
	currentHp = hp;
}

void Attributs::setEquipStats(unsigned short _atk, unsigned short _def, unsigned short _iq, float _crit, unsigned short _hp)
{
	eqatk = _atk;
	eqdef = _def;

	eqiq = _iq;
	eqkrit = _crit;
	eqhp = _hp;


}

void Attributs::setStats(unsigned short _level,unsigned short _atk, unsigned short _def, unsigned short _iq, float _crit, unsigned short _hp,bool heal)
{

	atk = _atk;
	def = _def;
	entitylevel = _level;

	iq = _iq;
	krit = _crit;
	hp = _hp;
	
	if (heal)
	{
		currentHp = hp;
		currentMana = getMaxMana();
	}


}

bool Attributs::getxp_andlvup(short _xp)
{
		erfahrung += _xp;
		if (erfahrung > entitylevel * 100) { LevelUp(); erfahrung = 0; return true; }

		return false;	
}

const unsigned short Attributs::getxpaspercent()
{
	//printf("erfahrung: %d : level: %d\n ", erfahrung, entitylevel);
	return erfahrung / entitylevel;
}
