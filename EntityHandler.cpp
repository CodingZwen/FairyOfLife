#include "EntityHandler.h"



EntityHandler::EntityHandler()
{
}


EntityHandler::~EntityHandler()
{

	if (sBullet) delete sBullet;
	if (sFireBullet) delete sFireBullet;
	if (IceOrb) delete IceOrb;
	if (AWeaponset) delete AWeaponset;





}


void EntityHandler::connectToAssets(AssetManager  & Amanager)
{
	ptrAssetManager = &Amanager;

	//Golem = new Animation(Amanager.GetTexture("golem"), 0, 1, 32, 32, 3, 0.08);
	//Golem->norot();

	//Fireboss = new Animation(Amanager.GetTexture("Fireboss"), 0, 1, 128, 160, 5, 0.08);
	////Fireboss->norot();

	//Tree = new Animation(Amanager.GetTexture("baum"), 0, 1, 32, 32, 7, 0.3);
	//Tree->norot();
	//Tree->set_animrow(4);
	//treespawnsound.setBuffer(*Amanager.ptr_GetSound("treesound"));

	//sBullet = new Animation(Amanager.GetTexture("eisball2"), 0, 0, 32, 64, 16, 0.8);
	//sFireBullet = new Animation(Amanager.GetTexture("feuerball"), 0, 0, 32, 32, 3, .5);

	//IceOrb = new Animation(Amanager.GetTexture("iceorb"), 0, 0, 32, 32, 5, 0.8);
	//AWeaponset = new Animation(Amanager.GetTexture("weaponset"), 0, 1, 32, 32, 1, 0.00);




	wp = new PlayerWeapon(&ptrAssetManager->GetTexture("weaponset"));
	wp->change_weapon(2);
	



	treespawnsound.setVolume(5.5);

	//achtung mapgroesse kann sich ändern dann ist rip
	asterngetuned.init(ptrTileMapWithCollision->get_map_width(), ptrTileMapWithCollision->get_map_height(), *ptrTileMapWithCollision);


	

}

void EntityHandler::pop_entity(Entity * en)
{
	entities.push_back(en);
}

void EntityHandler::PopRaven(int xpos, int ypos)
{


	Raven* raven = new Raven(sf::Vector2f(xpos, ypos), &ptrAssetManager->GetTexture("raven"));
	raven->ptrAstern = &this->asterngetuned;
	raven->set_ptr_to_list(&entities);
	entities.push_back(raven);

}

//po wird vorher gecheckt
void EntityHandler::PopTree(int posx,int posy)
{
	BaumGegner* b = new BaumGegner(sf::Vector2f(0,0), &ptrAssetManager->GetTexture("baum"));

	b->movementComponent->setPosition(sf::Vector2f(posx, posy));
	b->ptrAstern = &this->asterngetuned;
	this->ptr_soundhandler->playSound("treesound");
	entities.push_back(b);

}

void EntityHandler::PopCat(int xpos, int ypos)
{
	
	Cat* cat = new Cat(sf::Vector2f(xpos, ypos), &ptrAssetManager->GetTexture("cat"));
	cat->ptrAstern = &this->asterngetuned;
	entities.push_back(cat);
}

void EntityHandler::PopButterfly(int xpos, int ypos)
{
	Schmetterling* sm = new Schmetterling(sf::Vector2f(xpos,ypos), &ptrAssetManager->GetTexture("butterfly"));
	entities.push_back(sm);
}

void EntityHandler::PopAlotOfButterflys(sf::Vector2f screenDimension)
{
	int randomx=0;
	int randomy=0;

	for (int i = 0; i < 500; i++) {
		

		randomx = rand() % (int)screenDimension.x + 100;
		randomy = rand() % (int)screenDimension.y + 70;
		
		if(i%2)	PopButterfly(randomx, randomy);
		else 	PopCat(randomx, randomy);

		randomx = rand() % (int)screenDimension.x + 100;
		randomy = rand() % (int)screenDimension.y + 70;
		
		PopRaven(randomx, randomy);

		//randomx = rand() % (int)screenDimension.x + 100;
		//randomy = rand() % (int)screenDimension.y + 70;
		//PopCat(randomx, randomy);

	}


	//for (int i = 0; i < 100; i++) {


	//		PopCat(500, 700);

	//	

	//}


}

void EntityHandler::PopGolem(int xpos, int ypos)
{
	SteinGolem* b = new SteinGolem(sf::Vector2f(xpos,ypos),&ptrAssetManager->GetTexture("golem"));
	b->ptrAstern = &this->asterngetuned;
	entities.push_back(b);
}

void EntityHandler::PopFireboss(int xpos, int ypos)
{
	/*FireBoss* b = new FireBoss();
	b->settings(*Fireboss, xpos, ypos, 0, 90);
	b->init();
	b->ptrAstern = &this->asterngetuned;
	b->setOrigin();
	entities.push_back(b);*/

}

void EntityHandler::PopMagickBullet(int xpos, int ypos, float AngleToTarget, int atk)
{


	MagickBullet* bullet = new MagickBullet(atk, AngleToTarget, sf::Vector2f(xpos,ypos), &ptrAssetManager->GetTexture("eisball2"));
	entities.push_back(bullet);
	
}

void EntityHandler::PopFireBullet(int xpos, int ypos, float AngleToTarget, int atk, int dir)
{

	MagickBullet* bullet = new MagickBullet(atk, AngleToTarget, sf::Vector2f(xpos, ypos), &ptrAssetManager->GetTexture("feuerball"));
	entities.push_back(bullet);
}

void EntityHandler::changeSpawnModi(int modi)
{
	SpawnModi = modi;
}

void EntityHandler::killAllEntitys()
{
	for (auto i = entities.begin(); i != entities.end();i++) {

		Entity *e = *i;

		if (e->id != 7)
			e->kill();
		   e->canDrop = false;

		//i++ !?
		}

}

void EntityHandler::popIceOrb(unsigned int iq,unsigned int posx, unsigned int posy)
{

	if (!ptrIceOrb) {
		ptrIceOrb = new MagickIceOrb(iq,10,nullptr, &ptrAssetManager->GetTexture("iceorb"));

		pop_entity(ptrIceOrb);
	}
	
}

void EntityHandler::update(Items & items, sf::Time _elapsed, sf::Vector2f const playerpos)
{

	//wp->set_angle(ptr_player->get_angle());
	wp->update_offset(ptr_player->returnplayer_direction());


	for (auto i = entities.begin(); i != entities.end(); ) {

		Entity *e = *i;
	
		//nocj überarbeiten
		e->update(_elapsed, playerpos);
		//e->anim.update(_elapsed);
	
	
	
			
		if (!e->isAlive())
		{
			if (e->id == 1 || e->id == 3 || e->id == 33) {
				
				if (e->canDrop)
				{
					int random = rand() % 4 + 0;
					//bool success = items.load_diamond(e->movementComponent->getPosition(), random);
					bool success = 0;
					if (!success) {

						if(e->id == 33)success = items.loaditem(e->movementComponent->getPosition(), (rand() % 150),2);
						else
						success = items.loaditem(e->movementComponent->getPosition(), (rand() % 70));
						
					} //0-69 items auf dem waffen asset
					vxp.push_back(50);
				}
			}
			else if (e->id == 32) {
				if (ptrIceOrb)ptrIceOrb = NULL;
			}

			e->cleanTargets();
			i = entities.erase(i);
			delete e;
		}
		else {
		i++;
		}
		
	}


	//asterngetuned.solve();
	collide(_elapsed);
}

void EntityHandler::collide(sf::Time elapsed)
{
	//Entity::Manage_Collide(entities);

	for (auto a : entities) {

		if (a->movementComponent)
		if (ptr_player->movementComponent->getGlobalBounds().intersects(a->movementComponent->getGlobalBounds()) &&( a->id == 3 || a->id == 33 || a->id == 1)&& a->is_attacking()) {
			ptr_player->movementComponent->pushToLeft();
		
			ptr_player->hurt(a->attributs.getdmg());
			ptr_texthandler->popDmg(a->attributs.getdmg(), ptr_player->getPosition(),0);
			

		}

		if ((a->id == 1 || a->id == 3 || a->id == 33))
		{

		 //playerewaponcheck
				
		/*	if(a->movementComponent->getGlobalBounds().intersects(sf::FloatRect(wp->getPosition().x-20,
				wp->getPosition().y-16,36,36)) && wp->swing)
			{

				if (a->is_attackable()) {
					a->attributs.hurt(ptr_player->attributs.getdmg());
					ptr_texthandler->popDmg(ptr_player->attributs.getdmg(),a->getPosition(), 3);
				}
			}*/



			if (a->movementComponent->getGlobalBounds().intersects(ptr_player->playerweapon->getCollRect()) && ptr_player->playerweapon->swing)
			{

				if (a->is_attackable()) {
					a->attributs.hurt(ptr_player->attributs.getdmg());
					ptr_texthandler->popDmg(ptr_player->attributs.getdmg(), a->getPosition(), 3);
				}
			}

		}





		for (auto b : entities) {
		//bullet und baumcolli
			if (a->id == 20 && (b->id == 3 || b->id == 1 || b->id == 33) )
			{
				if (Entity::isCollideBetter(a, b)) {
					//a->life = false; b->life = false;
					//ist virtuelle entitiy class die von enemy hurt benutzt bzw hp anbieht
					b->attributs.hurt(a->attributs.getdmg());
					a->kill();
					ptr_texthandler->popDmg(a->attributs.getdmg(), b->getPosition(),2);
				}
			}

			if (a->id == 8 && (b->id == 3 || b->id == 1 || b->id == 33))
			{
				if (Entity::isCollide(a, b)) {
					//a->life = false; b->life = false;
					//ist virtuelle entitiy class die von enemy hurt benutzt bzw hp anbieht
					if (b->is_attackable()) {
						b->attributs.hurt(a->attributs.getdmg());
						ptr_texthandler->popDmg(a->attributs.getdmg(), b->getPosition(), 2);
					
					}
				}



			}




			if (a->id == 32 &&  b->id == 1)
			{
				if (Entity::isCollide(a, b)) {
					//a->life = false; b->life = false;
					//ist virtuelle entitiy class die von enemy hurt benutzt bzw hp anbieht
					if (b->is_attackable()) {
						ptr_texthandler->popDmg("Immune", a->getPosition(), 3);
					}
				}
			}

			if ((a->id  == 32 &&( b->id == 3 || b->id == 33)))
			{
				if (Entity::isCollideBetter(a, b)) {
					//a->life = false; b->life = false;
					//ist virtuelle entitiy class die von enemy hurt benutzt bzw hp anbieht
					if (b->is_attackable()) {
						b->attributs.hurt(a->attributs.getdmg());
						ptr_texthandler->popDmg(a->attributs.getdmg(), b->getPosition(), 2);
						ptr_soundhandler->playSound("Electrichitsound");
					}
				}
			}
							
		}
	}

}



void EntityHandler::draw(sf::RenderWindow & window)
{
	for (auto i : entities) i->draw(window);


	//sf::RectangleShape shape;
	//shape.setSize(sf::Vector2f(32,32));
	//shape.setPosition(sf::Vector2f(wp->getPosition().x-20, wp->getPosition().y-16 ));
	//shape.setFillColor(sf::Color(0, 255, 0, 150));
	//
	//window.draw(shape);

	//astern.draw_lists(window);
	//asterngetuned.draw(window);
}

void EntityHandler::isCollide_with_player()
{
	
	for (auto a : entities) {
	
		if (ptr_player->movementComponent->getGlobalBounds().contains(a->getPosition())) {
		
		}

	}


}



int EntityHandler::get_xp_from_enemys()
{
	if (vxp.size() > 0) {

		int xp = 0;

		for (auto b : vxp) {
			xp += b;
		}
		vxp.clear();
		return xp;
	}
	else return 0;
}

void EntityHandler::connect_to_texthandler(TextHandler & _th)
{
	
	ptr_texthandler=&_th;
}

void EntityHandler::connect_to_SoundHandler(SoundHandler & _sh)
{
	ptr_soundhandler = &_sh;
}


void EntityHandler::check_for_new_enemys(Tilemap_with_Collision & tm, sf::Time elapsed)
{

	respawn_Timer += elapsed;

	//achtung in entiteis ist auch da cshwert drinnen also ist size immer mindetens 1
	if (respawn_Timer.asSeconds() > RESPAWNTIME && entities.size()<MAXENEMYS) {
		respawn_Timer = respawn_Timer.Zero;

		//finalpos.x = ((rand() % x2) + x1);
		//finalpos.y = ((rand() % y2) + y1);
		int randomx, randomy;

		randomx = rand() % 1000 + 100;
		randomy = rand() % 700 + 70;
			
		

		if (!tm.collide_engine(sf::Vector2f(randomx, randomy),sf::Vector2f(0,0)))
		{
			//PopTree(randomx, randomy);

			switch (SpawnModi)
			{
			case 0: break;
			case 1: PopGolem(randomx, randomy); break;
			case 2: break;
			case 3:PopTree(randomx, randomy); break;
			case 4:PopFireboss(randomx, randomy); printf("was geht"); break;
			default:break;
			}
			

		}

		
	}
}


/*


Enemy* b = new Enemy();
b->settings(*Golem, randomx, randomy, 0, 20);
entities.push_back(b);
*/


/*
respawn_Timer += elapsed;

if (respawn_Timer.asSeconds() > 10) {
respawn_Timer = respawn_Timer.Zero;

//finalpos.x = ((rand() % x2) + x1);
//finalpos.y = ((rand() % y2) + y1);
int randomx, randomy;

for (int i = entities.size(); i <= 10; i++) {

do {
randomx = rand() % 1180;
randomy = rand() % 668;
} while (tm.collide_engine(sf::Vector2f(randomx, randomy)));

BaumGegner* b = new BaumGegner();
b->settings(*Tree, randomx, randomy, 0, 20);
entities.push_back(b);
treespawnsound.play();

}


}



v1 = rand() % 100;         // v1 in the range 0 to 99
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014



*/