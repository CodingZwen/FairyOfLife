#pragma once
#include <stdlib.h>
#include <stdio.h>

class Attributs
{

private : 
	int atk, eqatk=0;
	int def, eqdef=0;
	float casttime;
	
	float krit, eqkrit;
	int iq, eqiq = 0;
	int hp, eqhp = 0;
	int erfahrung;
	int entitylevel;
	int takendmg = 0;

	unsigned int currentMana = 0;
	int currentHp = 0;

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
		void hurt(const unsigned int damage);
		void drainMana(unsigned int cost);
		void initStats();
		bool isalive() { return !isdead; }
		
		bool getxp_andlvup(int _xp);
		//const doenst matter?
		const unsigned int  getHpAsPercent();
		const unsigned int getTakenDmg() { return takendmg; }
		const unsigned int get_level() { return entitylevel; }
		const unsigned int getdmg() { return atk + eqatk; }
		const unsigned int getdefense() { return def + eqdef; }
		const unsigned int getMaxHp() { return hp + eqhp; }
		const unsigned int getMaxMana() { return(iq + eqiq) * 5; }
		const unsigned int getCurrentMana() { return currentMana; }
		const unsigned int getiq() { return iq + eqiq; }
		const unsigned int getxpaspercent();
		const float getCastTime()const { return casttime; }
		const float getManareg() { return manareg; }
		float getkrit() { return krit + eqkrit; }	
 
		void setAtk(int _atk)	{	atk = _atk;	}
		void setEqAtk(int _eqatk) { eqatk = _eqatk; }
		void setHp(int _hp) { hp = _hp; currentHp = _hp; }
		//stats from equipped item 
		void setEquipStats(unsigned int _atk, unsigned int _def, unsigned int _iq, float _crit, unsigned int _hp);
		//set normal stats,also inits currentmana
		void setStats(unsigned int _level, unsigned int _atk, unsigned int _def, unsigned int _iq, float _crit, unsigned int _hp, bool heal = true);
		void setCastTime(float castTime) { this->casttime = castTime; }

};



