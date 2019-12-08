#include "Enemy.h"



Enemy::Enemy()
{
	
	
}

Enemy::~Enemy()
{
}


void Enemy::set_Spawn_Area(sf::Vector2i const & pos, int fieldsize)
{
	

		//printf("das ist x1: %f : und x2 %f\n", pos.x, pos.y);

		sf::Vector2i finalpos;

		int _fieldsize = fieldsize * 32;
		int x1 = (pos.x - _fieldsize);
		int x2 = (pos.x + _fieldsize);

		//printf("das ist x1: %d : und x2 %d\n", x1, x2);

		int y1 = pos.y - fieldsize * 32;
		int y2 = pos.y + fieldsize * 32;


		//printf("es wird jetzt eine zufdallszahlzwischen %d  und %d germacht \n", y1, y2);

		finalpos.x = ((rand() % x2) + x1);
		finalpos.y = ((rand() % y2) + y1);


		finalpos.x = (x1 + (rand() % (x2 - x1 + 1)));
		finalpos.y = (y1 + (rand() % (y2 - y1 + 1)));


		float  x = static_cast<float>(finalpos.x);
		float  y = static_cast<float>(finalpos.y);

		movementComponent->setPosition(sf::Vector2f(x, y));


		//printf("gegner wurde an pos gesetzt: %f : %f\n", finalpos.x, finalpos.y);

		//eventuell noch kartenmaﬂe mitgeben damit wenn
		//spawn z.b in der ecke ist, damit gegner nich im schwarzen spawnen


	


}



/*
alte version ohne angle miteinberechnung beim animation draw


if (angle < (-80)) {
anim.set_animrow(3);
}

if (angle > (-45) && angle < 45 || angle > 300) {
anim.set_animrow(2);
}

if (angle >(45) && angle < 135) {
anim.set_animrow(0);
}

if (angle >(135) && angle < 225) {
anim.set_animrow(1);
}

if (angle >(225) && angle < 315) {
anim.set_animrow(3);
}

*/




/*

	if (angle < (-80)) {
		anim.set_animrow(3);
	}

	else if (angle > (-45) && angle < 45 || angle > 300) {
		anim.set_animrow(2);
	}

	else if (angle >(45) && angle < 135) {
		anim.set_animrow(0);
	}

	else if (angle >(135) && angle < 225) {
		anim.set_animrow(2);
	}

	else if (angle >(225) && angle < 315) {
		anim.set_animrow(3);
	}

	if (speed > 0)anim.start();
	else  anim.stop();


	_____
	hp -= dmg;


	float ergebnis = 32;
	ergebnis /= 100;
	ergebnis *= dmg;

	hpSize.x -= ergebnis;

	if (hp < 0)life = false;

	anim.rect.setSize(hpSize);



*/



