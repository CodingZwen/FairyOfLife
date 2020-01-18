#pragma once
#include <string>
#include "Animation.h"
#include "Items.h"
#include "AsternGetuned.h"
#include "Attributs.h"
#include "AnimatedSprite.h"
#include "MovementComponent.h"
#include "MiniHpbar.h"

//entitys bis jetzt: magickbullet, enemy , weapon-> der aber extra
//gespeichert unter pointer
class Entity
{
protected:
	AnimatedSprite animatedSprite;
	MiniHpbar hpbar;
	Entity *ptrTargetEntity = nullptr;
	bool life;
	bool attacking;
	bool behindplayer;

	std::string name;
	
	unsigned int direction;

public:
	void setbehindplayer() { behindplayer = true; }
	void setinfrontplayer() { behindplayer = false; }
	bool isbehindplayer() { return behindplayer; }

	void setPositionAgainstPlayer(sf::Vector2f playerpos);

	bool canDrop = true;
	int id = 0;
	std::string &getname() { return name; }
	Entity();
	virtual ~Entity();

	void setName(std::string name);

	bool havetarget = false;
	std::shared_ptr<MovementComponent> movementComponent;
	AsternGetuned *ptrAstern = nullptr;
	Attributs attributs;

	//evtl in no richtung eingeschlagen oder so machen
	bool haventMoved = true;

	float attacktimer;
	float invicibletimer;
	bool collide =false;
	sf::Time elapsed;

	std::list<Entity*> *ptr_entitylist = nullptr;
	std::list<sf::Vector2f> waypointsToTarget;


	static bool isCollide(Entity *a, Entity *b);
	static bool isCollideBetter(Entity *a, Entity *b);

	const sf::Vector2f &getPosition();

	//wird von den kindern geerbt die dann entsprechend x und y handeln
	virtual void Entity::update(sf::Time _elapsed,sf::Vector2f ownerpos) = 0;
	virtual void draw(sf::RenderWindow &window);
	//virtual void Entity::update_rect(int something) = 0;
	void createMovementComponent(const float maxVelocity, const float acceleration, const float decelaration);

	
	bool is_attackable();
	bool is_attacking();
	bool isAlive();

	void kill();

	void set_ptr_to_list(std::list<Entity*> *entitylist);
	
	void createAnimation(sf::Texture &spriteSheet);
	
	//set mouse pos
	void smp(sf::Vector2f pos) { _mousepos = pos; }
	bool reachedWaypoint(sf::Vector2f pos);

	void resetTarget();
	void setTarget(Entity * en);
	void cleanTargets();
	void search_for_target_in_list();

	void WatchAndFollow(sf::Time _elapsed, sf::Vector2f playerpos, float followResetTime=3800.f);
	void FollowAndAttackEnemy(sf::Time _elapsed, sf::Vector2f playerpos, float followResetTime = 800.f);
	bool findWay(sf::Vector2f target); //feeds wayointslist
	void follow(sf::Time elapsed,  unsigned int offset = 0);

	void moveUp(sf::Time elapsed);
	void moveDown(sf::Time elapsed);
	void moveLeft(sf::Time elapsed);
	void moveRight(sf::Time elapsed);


	void moveNW(sf::Time elapsed);
	void moveNE(sf::Time elapsed);
	void moveSW(sf::Time elapsed);
	void moveSE(sf::Time elapsed);


	static float  RADIANT; 
	static int WIDTH;
	static int HEIGHT;


	sf::Vector2f _mousepos;

	std::list<sf::Vector2i> waypointsList;
	list <sf::Vector2i> ::iterator waypointIt;
	unsigned int currentWayPoint = 0;
	


};

