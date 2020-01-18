#pragma once
#include "Entity.h"
#include <list>
#include "SteinGolem.h"
#include "BaumGegner.h"
#include "Items.h"
#include "Player.h"
#include "TextHandler.h"
#include "AssetManager.h"
#include "PlayerWeapon.h"
#include "Tilemap_with_Collision.h"

#include "AsternGetuned.h"
#include "MagickBlizzard.h"
#include "MagickBullet.h"
#include "MagickIceOrb.h"
#include "FireBoss.h"
#include "SoundHandler.h"
#include "Schmetterling.h"
#include "Cat.h"
#include "Raven.h"
#define MAXENEMYS 5
#define RESPAWNTIME 1
class EntityHandler 
{
	bool IceOrbAvtive;
	unsigned int SpawnModi = 0;
	//TODO
	enum class ESpawnModi { NOOBS, ANDERENOOBS };

	AssetManager *ptrAssetManager = nullptr;

public:
	EntityHandler();
	~EntityHandler();

	void pop_entity(Entity *en);
	void PopRaven(int xpos, int ypos);
	void PopTree(int xpos,int ypos);
	void PopCat(int xpos, int ypos);
	void PopButterfly(int xpos, int ypos);
	void PopAlotOfButterflys(sf::Vector2f screenDimension);
	void PopGolem(int xpos, int ypos);
	void PopFireboss(int xpos, int ypos);
	void PopMagickBullet(int xpos, int ypos, float AngleToTarget,int atk);
	void PopFireBullet(int xpos, int ypos, float AngleToTarget, int atk,int dir);


	void changeSpawnModi(int modi);

	void killAllEntitys();
	void popIceOrb(unsigned int iq, unsigned int posx, unsigned int posy);
	void update(Items &items, sf::Time _elapsed, sf::Vector2f const playerpos);
	void collide(sf::Time elapsed);
		
	void drawbehindplayer(sf::RenderWindow &window);
	void drawinfrontplayer(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	void init_player_ptr(std::shared_ptr<Player> &ptrplayer) { ptr_player = ptrplayer; }
	void isCollide_with_player();

	int get_xp_from_enemys();

	void connect_to_texthandler(TextHandler &_th);
	void connect_to_SoundHandler(SoundHandler &_sh);


	void connectToAssets(AssetManager  &Amanager);

	//brauche dann hier animation um enemys zu erstellen
	void check_for_new_enemys(Tilemap_with_Collision &tm, sf::Time elapsed);

	std::list<Entity*> entities;
	//std::list<Enemy*> enemys;
	std::vector<int> vxp;

	std::shared_ptr<Player> ptr_player;
	TextHandler* ptr_texthandler;
	SoundHandler * ptr_soundhandler;
	Tilemap_with_Collision *ptrTileMapWithCollision;
	
	sf::Time respawn_Timer;

	PlayerWeapon* wp;
	//
	Animation *Golem;
	Animation *Tree;
	Animation *Fireboss;
	Animation *AWeaponset;
	Animation *sBullet;
	Animation *sFireBullet;




	Animation *IceOrb;
	Animation *Blizzard;

	MagickBullet *b;
	MagickIceOrb *ptrIceOrb;
	MagickBlizzard *mb;

	sf::Sound treespawnsound;
	
	AsternGetuned asterngetuned;

};

