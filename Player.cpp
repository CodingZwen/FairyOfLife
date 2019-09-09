#include "Player.h"



Player::Player(sf::Vector2f spawnpos, sf::Texture const  *texture, sf::Texture const * weaponTexture)
{

	initStats();

	playerweapon = new PlayerWeapon(weaponTexture);

	setKeys(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Space);

	direction = 2;
	

	initAnimations(texture);
	animatedSprite.setPosition(spawnpos);

	//animatedSprite.setPosition(spawnpos);
	//achtung initalisiert animation ptr von movement class
	createMovementComponent(100.f, 30.f, 15.f);
	

}

Player::~Player()
{
	if (playerweapon)delete playerweapon;
}

void Player::initAnimations(const sf::Texture *texture)
{

	int spritex = 32;
	int spritey = 48;

	animatedSprite.insertAnimation(sf::IntRect(0, 0, spritex, spritey), 5,* texture,"WALKING_UP");
	animatedSprite.insertAnimation(sf::IntRect(0, 48, spritex, spritey), 5,* texture, "WALKING_DOWN");

	animatedSprite.insertAnimation(sf::IntRect(0, 48 * 2, spritex, spritey), 5,* texture, "WALKING_LEFT");
	animatedSprite.insertAnimation(sf::IntRect(0, 48 * 3, spritex, spritey), 5,* texture, "WALKING_RIGHT");


	animatedSprite.insertAnimation(sf::IntRect(0, 48*4, spritex, spritey), 5,* texture, "STANDING_UP");
	animatedSprite.insertAnimation(sf::IntRect(0, 48*5, spritex, spritey), 5,* texture, "STANDING_DOWN");

	animatedSprite.insertAnimation(sf::IntRect(0, 48 * 6, spritex, spritey), 5,* texture, "STANDING_LEFT");
	animatedSprite.insertAnimation(sf::IntRect(0, 48 * 7, spritex, spritey), 5,* texture, "STANDING_RIGHT");
	animatedSprite.insertAnimation(sf::IntRect(0, 48 * 8, spritex, spritey), 5,* texture, "STANDING_AFK");
	animatedSprite.insertAnimation(sf::IntRect(0, 48 * 9, spritex, spritey), 5, *texture, "DEATHANIMATION");


	animatedSprite.setFrameTime(sf::seconds(0.2));

}


void Player::move(const float dir_x, const float dir_y, const float & dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);//xetzt bewegung fest

		printf("x: %d \n", dir_x);
	}
}

void Player::update(sf::Time elapsed, sf::Vector2f ownerPos)
{

	_elapsed += elapsed;
	CastTimer += elapsed;
	haventMoved = true;

	if (attributs.isalive())
	{

		attributs.update(elapsed.asSeconds());

		if (!playerweapon->attack) {




		  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			&& (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		  {

			moveNE(elapsed);

		  }
			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				&& (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			{
				moveNW(elapsed);

			}


			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)|| sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				&& (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
			{
				moveSE(elapsed);
				
			}

			else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				&& (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			{
				moveSW(elapsed);

			}

		

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				moveUp(elapsed);

			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{

				moveDown(elapsed);
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{

				moveLeft(elapsed);


			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{

				moveRight(elapsed);
			}
		}

		if (haventMoved)
		{
			switch (direction) {
			case 2:

				if (movementComponent->isAFK()) {
					animatedSprite.setCurrentAnimation("STANDING_AFK");
				}
				else {
					animatedSprite.setCurrentAnimation("STANDING_DOWN");
				}break;
			case 1: animatedSprite.setCurrentAnimation("STANDING_UP"); break;
			case 3: animatedSprite.setCurrentAnimation("STANDING_LEFT"); break;
			case 4: animatedSprite.setCurrentAnimation("STANDING_RIGHT"); break;
			default:break;

			}
		}
		else
		{
			switch (direction)
			{
			case 1: animatedSprite.setCurrentAnimation("WALKING_UP");
				angleForWeapon = 270;

				break;
			case 2:	animatedSprite.setCurrentAnimation("WALKING_DOWN");
				angleForWeapon = 90;

				break;
			case 3: animatedSprite.setCurrentAnimation("WALKING_LEFT");
				angleForWeapon = 180;

				break;
			case 4: animatedSprite.setCurrentAnimation("WALKING_RIGHT");
				angleForWeapon = 0;

				break;
			default:  animatedSprite.setCurrentAnimation("DEATHANIMATION"); break;
			}
		}

		drawWeaponBehind = (direction == 1)?  true : false;



		if (playerweapon)
		{
			playerweapon->update(elapsed, movementComponent->getPosition(), angleForWeapon);
			playerweapon->update_offset(direction);
		}

	}
	else {
	animatedSprite.setCurrentAnimation("DEATHANIMATION");
	animatedSprite.setLooped(0);
	
	}

	animatedSprite.update(elapsed);
	movementComponent->update(elapsed.asSeconds());

}



void Player::setKeys(sf::Keyboard::Key u, sf::Keyboard::Key d, sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key s)
{
	kUp = u;
	kDown = d;
	kLeft = l;
	kRight = r;
	kShoot = s;
}

void Player::draw(sf::RenderWindow & target)
{

	if (drawWeaponBehind)
	{
		

		if (playerweapon)
			playerweapon->draw(target);

		target.draw(animatedSprite);

	}
	else
	{
		target.draw(animatedSprite);

		if (playerweapon)
			playerweapon->draw(target);

	}


}



//diese funktion scheint iwie zugriffsverletzungen zu machen....
void Player::setplayerpos(sf::Vector2f const pos)
{
//	rect.setPosition(sf::Vector2f(pos));
	movementComponent->setPosition(pos);
	
}

void Player::hurt(int dmg)
{
	//hp-=dmg;
	Bgotdmg = true;
	//printf("Spieler hat noch %d HP\n", playerstats.hp- playerstats.takendmg);
	attributs.hurt(dmg);

}



bool Player::is_attacking()
{
	return 1;
}

sf::Vector2f Player::getviewsetoff(sf::Vector2f playerpos, int mapwidth, int mapheight)
{
	sf::Vector2f buffer;
	buffer.x = playerpos.x;
	buffer.y = playerpos.y;
	buffer.x /= 32;
	buffer.y /= 32;

	//kante 5x 32 
	buffer.x -= 17;
	buffer.y -= 15;

	if (buffer.x < 0)buffer.x = 0;
	if (buffer.x > mapwidth)buffer.x = mapwidth;


	if (buffer.y < 0)buffer.y = 0;
	if (buffer.y > mapheight)buffer.y = mapheight;

	return buffer;
}

sf::Vector2f Player::getviewsetoff_right(sf::Vector2f playerpos, int mapwidth, int mapheight)
{
	sf::Vector2f buffer;
	buffer.x = playerpos.x;
	buffer.y = playerpos.y;
	buffer.x /= 32;
	buffer.y /= 32;

	//kante 5x 32 
	buffer.x += 17; //17
	buffer.y += 15; //15

	if (buffer.x < 0)buffer.x = 0;
	if (buffer.x > mapwidth)buffer.x = mapwidth;


	if (buffer.y < 0)buffer.y = 0;
	if (buffer.y > mapheight)buffer.y = mapheight;


	return buffer;
}

float Player::getAngleToTarget(sf::Vector2f target)
{

	float a = atan2(target.y - movementComponent->getPosition().y, target.x - movementComponent->getPosition().x);

	a *= (180.f / M_PI);

	//	if (a < 0)a += 360;

	return a;
}


bool Player::CanSpell()
{
	if (CastTimer.asSeconds() > attributs.getCastTime()) 	return true;
	else return false;

}

bool Player::HaveEnoughMana(unsigned const int spellcost)
{

	if (spellcost < attributs.getCurrentMana())return  true;
	else return false;
}

void Player::initStats()
{
	attributs.setCastTime(0.8f);
	attributs.setStats(1,5, 5, 20, 1.f, 200);
	attributs.setEquipStats(0, 0, 0, 0,0);


}




/*


		if (noKeyWasPressed)
		{

			switch (direction) {
			case 2:
				blinktimer += elapsed;

				if (blinktimer.asSeconds() > 5) {
					animatedSprite.setCurrentAnimation("STANDING_AFK");

					if (blinktimer.asSeconds() > 7) {
						blinktimer = blinktimer.Zero;
					}
				}
				else {
					animatedSprite.setCurrentAnimation("STANDING_DOWN");
				}break;
			case 1: animatedSprite.setCurrentAnimation("STANDING_UP"); break;
			case 3: animatedSprite.setCurrentAnimation("STANDING_LEFT"); break;
			case 4: animatedSprite.setCurrentAnimation("STANDING_RIGHT"); break;
			default:break;

			}



		}
		else
		{

			switch (direction)
			{
			case 1: animatedSprite.setCurrentAnimation("WALKING_UP"); break;
			case 2:	animatedSprite.setCurrentAnimation("WALKING_DOWN"); break;
			case 3: animatedSprite.setCurrentAnimation("WALKING_LEFT"); break;
			case 4: animatedSprite.setCurrentAnimation("WALKING_RIGHT"); break;
			default:break;
			}

		}



*/