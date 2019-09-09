#pragma once
#include <stdlib.h>
#include <stdio.h>

class Attributs
{

private : 
	short atk, eqatk=0;
	short def, eqdef=0;
	float casttime;
	
	float krit, eqkrit;
	short iq, eqiq = 0;
	short hp, eqhp = 0;
	short erfahrung;
	short entitylevel;
	short takendmg = 0;
	//i need float here because of manareg..
	unsigned short currentMana = 0;
	short currentHp = 0;

	bool isdead = false;

	float manareg = 1.f;
	float hpreg = 1.f;
	float regTimeBuffer = 0;

public:
	Attributs();
	~Attributs();
		
	    void update(float dt);
		
		void kill() { isdead = true; takendmg = hp; }
		void LevelUp();
		void hurt(const unsigned short damage);
		void drainMana(unsigned short cost);
		void initStats();
		bool isalive() { return !isdead; }
		
		bool getxp_andlvup(short _xp);
		//const doenst matter?
		const unsigned short  getHpAsPercent();
		const unsigned short getTakenDmg() { return takendmg; }
		const unsigned short get_level() { return entitylevel; }
		const unsigned short getdmg() { return atk + eqatk; }
		const unsigned short getdefense() { return def + eqdef; }
		const unsigned short getMaxHp() { return hp + eqhp; }
		const unsigned short getMaxMana() { return(iq + eqiq) * 5; }
		const unsigned short getCurrentMana() { return currentMana; }
		const unsigned short getiq() { return iq + eqiq; }
		const unsigned short getxpaspercent();
		const float getCastTime()const { return casttime; }
		const float getManareg() { return manareg; }
		float getkrit() { return krit + eqkrit; }	
 
		void setAtk(short _atk)	{	atk = _atk;	}
		void setEqAtk(short _eqatk) { eqatk = _eqatk; }
		void setHp(short _hp) { hp = _hp; currentHp = _hp; }
		//stats from equipped item 
		void setEquipStats(unsigned short _atk, unsigned short _def, unsigned short _iq, float _crit, unsigned short _hp);
		//set normal stats,also inits currentmana
		void setStats(unsigned short _level, unsigned short _atk, unsigned short _def, unsigned short _iq, float _crit, unsigned short _hp, bool heal = true);
		void setCastTime(float castTime) { this->casttime = castTime; }

};



