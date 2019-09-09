#include "Entity.h"




Entity::Entity()
{
	life = true;

}


Entity::~Entity()
{
}


void Entity::WatchAndFollow(sf::Time _elapsed, sf::Vector2f target,float followResetTime)
{


	if (!collide) {


		if (!havetarget) {

			elapsed += _elapsed;

			if (this->movementComponent->getDistanceToTarget(target) < 200)
			{
				havetarget = 1;
				
			}

		}
		else if (havetarget)
		{

			elapsed += _elapsed;
			if (elapsed.asMilliseconds() > followResetTime) {
				elapsed = elapsed.Zero;

				//initalisiert wegpunktliste
				findWay(target);
			}

			//bewegt movementcomponent nach listenende
			follow(elapsed);

		}
	}
	else {
		movementComponent->setOldPosition();
		collide = false;
	}
}


void Entity::FollowAndAttackEnemy(sf::Time _elapsed, sf::Vector2f player, float followResetTime)
{

	elapsed += _elapsed;

	if (!collide) {



		
		 if (!havetarget)
		 {

			
			if (elapsed.asMilliseconds() > followResetTime) {
				elapsed = elapsed.Zero;


				findWay(player);
				//printf("versucht player zu finden :x %f y: %f\n", player.x, player.y);
			}

			follow(elapsed);
			search_for_target_in_list();

		 }
		 else if(havetarget && ptrTargetEntity) {

			 if (elapsed.asMilliseconds() > followResetTime) {
				 elapsed = elapsed.Zero;


				 findWay(ptrTargetEntity->movementComponent->getPosition());

				 sf::Vector2f enemypos = ptrTargetEntity->movementComponent->getPosition();
				// printf("versucht gegner zu finden :x %f y: %f\n", enemypos.x, enemypos.y);
			 }

			
			 follow(elapsed);

		 }
	}
	else {
		movementComponent->setOldPosition();
		collide = false;
	}

}

bool Entity::findWay(sf::Vector2f target)
{
    ptrAstern->initSearch(((movementComponent->getPosition().x) / 32), ((movementComponent->getPosition().y) / 32), ((target.x ) / 32), ((target.y) / 32));
	if (ptrAstern->solve()) {
		waypointsList = ptrAstern->feedEnemyWithWaypointsList();
		
		return true;
	}

	havetarget = false;
	return false;
}

void Entity::follow(sf::Time _elapsed,  unsigned int offset)
{
	if (waypointsList.size() > offset)
	{

		sf::Vector2i currentTarget = waypointsList.back();
		int x = movementComponent->getPosition().x;
		int y = movementComponent->getPosition().y;

		sf::FloatRect collrect = sf::FloatRect(currentTarget.x, currentTarget.y, 32, 32);

		if (x < currentTarget.x)
		{
			moveRight(_elapsed);

		}
		else if (x > currentTarget.x)
		{
			moveLeft(_elapsed);

		}
		if (y < currentTarget.y)  moveDown(_elapsed);
		else if (y > currentTarget.y)  moveUp(_elapsed);


		if (collrect.intersects(animatedSprite.getGlobalBounds()))
		{

			waypointsList.pop_back();
		}

		/*if(target.x > x)	animatedSprite.setCurrentAnimation("RUNNING_RIGHT");
		else 	animatedSprite.setCurrentAnimation("RUNNING_LEFT");*/

	}

}



void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float decelaration)
{
	this->movementComponent = std::make_shared<MovementComponent>(animatedSprite, maxVelocity, acceleration, decelaration);

}


bool Entity::is_attackable()
{
	if (invicibletimer > 0.5f) {
		invicibletimer = 0;
		return true;
	}
	else {
		return false;
	}
}

bool Entity::is_attacking()
{
	if (attacktimer > 0.5f) {
		attacktimer = 0;
		return true;
	}
	else {
		return false;
	}

}

bool Entity::isAlive()
{
	return life;
}

void Entity::kill()
{
	life = false;
}


void Entity::createAnimation(sf::Texture & spriteSheet)
{

}


const sf::Vector2f & Entity::getPosition()
{
	return this->movementComponent->getPosition();
}

void Entity::draw(sf::RenderWindow &window)
{

	hpbar.draw(window);

}




//wirdzurzeit nicht verwendet =???
bool Entity::reachedWaypoint(sf::Vector2f pos)
{

	//printf("distance : %f\n", movementComponent->getDistanceToTarget(pos));

	if (movementComponent->getDistanceToTarget(pos) < 12.0f && currentWayPoint < waypointsList.size()-1) {
		++currentWayPoint;


		return true;
	}
	return false;
}


void Entity::set_ptr_to_list(std::list<Entity*>*entitylist)
{
	ptr_entitylist = entitylist;
}

void Entity::resetTarget()
{
	ptrTargetEntity = nullptr;
}

void Entity::setTarget( Entity * en)
{
	ptrTargetEntity = en;
}

void Entity::cleanTargets()
{
	if (ptrTargetEntity)
	{

		ptrTargetEntity->resetTarget();
	}
}

void Entity::search_for_target_in_list()
{
	if (ptr_entitylist && !havetarget)
	{
		for (auto b : *ptr_entitylist) {
			if (b->id == 3 || b->id == 99)
			{
				ptrTargetEntity = b;

				if (ptrTargetEntity->movementComponent->getDistanceToTarget(movementComponent->getPosition()) < 70)
				{


					havetarget = true;
					ptrTargetEntity->setTarget(this);
					
					//printf("gegner gefunden distance: %f\n", ptrTargetEntity->movementComponent->getDistanceToTarget(movementComponent->getPosition()));
					return;
				}
			}
		}

	}
}


void Entity::moveUp(sf::Time elapsed)
{

	direction = 1;
	haventMoved = false;
	movementComponent->move(0, -1, elapsed.asSeconds());


}

void Entity::moveDown(sf::Time elapsed)
{
	direction = 2;
	haventMoved = false;
	movementComponent->move(0, 1, elapsed.asSeconds());
}

void Entity::moveLeft(sf::Time elapsed)
{
	haventMoved = false;
	direction = 3;

	//rotation = 250;
	movementComponent->move(-1, 0, elapsed.asSeconds());
	/*angle = 180;*/
}

void Entity::moveRight(sf::Time elapsed)
{
	haventMoved = false;
	direction = 4;
	/*rotation = 30;*/
	movementComponent->move(1, 0, elapsed.asSeconds());


	/*angle = 0;*/

}

void Entity::moveNW(sf::Time elapsed)
{
	direction = 1;
	haventMoved = false;
	//angle = 270;
	movementComponent->move(-0.8f, -.4, elapsed.asSeconds());


}

void Entity::moveNE(sf::Time elapsed)
{
	direction = 1;
	/*rotation = 30;
*/
	haventMoved = false;
	//angle = 270;

	movementComponent->move(0.8, -0.4, elapsed.asSeconds());


}

void Entity::moveSW(sf::Time elapsed)
{
	direction = 2;
	haventMoved = false;
	//angle = 90;
	movementComponent->move(-0.8, 0.4, elapsed.asSeconds());

}

void Entity::moveSE(sf::Time elapsed)
{

	direction = 2;
	haventMoved = false;
	movementComponent->move(0.8, 0.4, elapsed.asSeconds());

}


bool Entity::isCollide(Entity *a, Entity *b) {

	return (b->movementComponent->getPosition().x -
		a->movementComponent->getPosition().x)*
		(b->movementComponent->getPosition().x -
			a->movementComponent->getPosition().x) +
		(b->movementComponent->getPosition().y -
			a->movementComponent->getPosition().y)*
			(b->movementComponent->getPosition().y -
				a->movementComponent->getPosition().y) <
		(a->movementComponent->getRadius() + b->movementComponent->getRadius())*
		(a->movementComponent->getRadius() + b->movementComponent->getRadius());

}

bool Entity::isCollideBetter(Entity * a, Entity * b)
{

	return a->movementComponent->getGlobalBounds().intersects(b->movementComponent->getGlobalBounds());

}


float Entity::RADIANT = 0.017453f;
int Entity::WIDTH = 1280;
int Entity::HEIGHT = 720;