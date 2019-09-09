#include "PlayerWeapon.h"



PlayerWeapon::PlayerWeapon(const sf::Texture *texture)
{
	name = "playerweapon";
	offsetangle = 45;
	offset = sf::Vector2f(0, 0);
	attackoffset = sf::Vector2f(0, 0);
	currentattackdir = 3;
	anim.init(texture,0, 0, 32, 32);
	collRect.height = 40;
	collRect.width = 40;

}


PlayerWeapon::~PlayerWeapon()
{
}

void PlayerWeapon::update(sf::Time _elapsed, sf::Vector2f ownerpos,float angle)
{
	attackTimer +=_elapsed;
	this->anim.setRotation(angle+offsetangle);
	

	if (attack) {

		switch (currentattackdir)
		{

		case 0: break;
		case 1: hitup(_elapsed); break;
		case 2: hitdown(_elapsed); break;
		case 3: hitleft(_elapsed); break;
		case 4: hitright(_elapsed); break;
		default: break;


		}

		

		if (elapsed.asSeconds() > 0.8) {

			attack = false;
			swing = false;
			elapsed = elapsed.Zero;
			attackoffset.x = 0;
			attackoffset.y = 0;
			offsetangle = 45;
		}

	}

	//movementcomponment setposition
	currentPosition.x = ownerpos.x+offset.x + attackoffset.x;
	currentPosition.y = ownerpos.y+offset.y + attackoffset.y;
	collRect.top = currentPosition.y-16;
	collRect.left = currentPosition.x-16;

	anim.update(elapsed, currentPosition);


	//std::cout << "colum: " << anim.column << " row: " << anim.currentrow << "Frame: " << anim.Frame << " Frames: " << anim.Frames << std::endl;
}

void PlayerWeapon::draw(sf::RenderWindow & window)
{
	anim.draw(window);
}

void PlayerWeapon::update_offset(int playerdirection)
{

	switch (playerdirection) {

	case 0: break;
	case 1: offset.x = 24; offset.y = 10; break; //up
	case 2: offset.x = 10; offset.y = 46; break;			//runter					//runter
	case 3: offset.x = 0; offset.y = 32; break;	//links							//links
	case 4: offset.x = 32; offset.y = 36; break; //rechts 
	default:break;

	}

}

void PlayerWeapon::change_weapon(int id)
{
	if (id > 9)return;

	anim.set_animcolumn(id);


}

void PlayerWeapon::hitleft(sf::Time _elapsed)
{
	elapsed += _elapsed;
	float timeFactor = _elapsed.asSeconds();

	


	//if (elapsed.asSeconds() > 1) {
	if (elapsed.asSeconds() > 0.4) {

		swing = true;
		offsetangle -= 360 * timeFactor;


		attackoffset.x -= 20.0*timeFactor;
		attackoffset.y += 80.*timeFactor;



	}
	else {
		offsetangle += 360 * timeFactor;


		attackoffset.x += 20.0*timeFactor;
		attackoffset.y -= 80.*timeFactor;

	}
	


}

void PlayerWeapon::hitdown(sf::Time _elapsed)
{

	elapsed += _elapsed;
	float timeFactor = _elapsed.asSeconds();




	//if (elapsed.asSeconds() > 1) {
	if (elapsed.asSeconds() > 0.4) {

		swing = true;
		offsetangle += 360 * timeFactor;


		attackoffset.x -= 40.0*timeFactor;
		attackoffset.y += 80.*timeFactor;



	}
	else {
		offsetangle -= 360 * timeFactor;


		attackoffset.x += 40.0*timeFactor;
		attackoffset.y -= 80.*timeFactor;

	}


}

void PlayerWeapon::hitright(sf::Time _elapsed)
{

	elapsed += _elapsed;
	float timeFactor = _elapsed.asSeconds();




	//if (elapsed.asSeconds() > 1) {
	if (elapsed.asSeconds() > 0.4) {

		swing = true;
		offsetangle += 360 * timeFactor;


		attackoffset.x += 20.0*timeFactor;
		attackoffset.y += 80.*timeFactor;



	}
	else {
		offsetangle -= 360 * timeFactor;


		attackoffset.x -= 20.0*timeFactor;
		attackoffset.y -= 80.*timeFactor;

	}




}

void PlayerWeapon::hitup(sf::Time _elapsed)
{
	elapsed += _elapsed;
	float timeFactor = _elapsed.asSeconds();




	//if (elapsed.asSeconds() > 1) {
	if (elapsed.asSeconds() > 0.4) {

		swing = true;
		offsetangle += 360 * timeFactor;


		attackoffset.x += 60.0*timeFactor;
		attackoffset.y -= 20.*timeFactor;



	}
	else {
		offsetangle -= 360 * timeFactor;


		attackoffset.x -= 60.0*timeFactor;
		attackoffset.y += 20.*timeFactor;

	}


}


//hier entweder texthandler mit param übergeben oder
//playerwapon irgndwie in entitiy handler schieben

//wird gerade nicht verwendet



/*
bewegungsvarfiante:

if (attack) {

elapsed += _elapsed;
attackoffset.x = 20;
attackoffset.y = -10;
offsetangle++;



//if (elapsed.asSeconds() > 1) { //für vertsion mit nur pätzen von schwerrt und ohne inkrementierung oben
if (offsetangle>90) {

attackoffset.x = -20;
attackoffset.y = -10;


}


if (elapsed.asSeconds() > 2) {

attack = false;
elapsed = elapsed.Zero;
attackoffset.x = 0;
attackoffset.y = 0;
offsetangle = 45;
}

}



x = ownerpos.x+offset.x + attackoffset.x;
y = ownerpos.y+offset.y + attackoffset.x;



*/


//gute variante nach unten gucken
/*
attackoffset.x = -12;
attackoffset.y = 32;
offsetangle++;
*/





/*



if (attack) {

elapsed += _elapsed;

offsetangle-=9;


attackoffset.x +=1.0;
attackoffset.y -=1.2;


//if (elapsed.asSeconds() > 1) {
if (elapsed.asSeconds() > 0.4) {


offsetangle += 18;
attackoffset.x -= 2.8;
attackoffset.y += 3.4;


}


if (elapsed.asSeconds() > 0.6) {

attack = false;
elapsed = elapsed.Zero;
attackoffset.x = 0;
attackoffset.y = 0;
offsetangle = 45;
}

}



x = ownerpos.x+offset.x + attackoffset.x;
y = ownerpos.y+offset.y + attackoffset.y;

*/