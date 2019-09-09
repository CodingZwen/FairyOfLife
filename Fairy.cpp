#include "Fairy.h"

#include <iostream>


Fairy::Fairy(Fairy_Type type)
{
	frames = 10;
	frame = 0;
	framewidth = 32;

	texture = new sf::Texture;

	switch (type) {
	case Fairy_Type::FIRE_FAIRY:



		if (!texture->loadFromFile("fairy1.png")) {
			printf("fehler bveimn laden der feuerball texture!\n");

		}
		else {
			printf("erfolgreich\n");
		}break;

	case Fairy_Type::ICE_FAIRY:


		if (!texture->loadFromFile("fairy_ice.png")) {
			printf("fehler bveimn laden der feuerball texture!\n");

		}
		else {
			printf("erfolgreich\n");
		}break;


	default: break;

	}

	sprite.setTexture(*texture);
	sprite.setPosition(200, 500);
	rect.setPosition(200, 500);




}

Fairy::Fairy()
{

	printf("standard feenkonstruktor aufgerufen\n");


}

Fairy::~Fairy()
{

}

void Fairy::Update(sf::Time elapsed, sf::Vector2f pos)
{
	


}

void Fairy::draw(sf::RenderTarget &target)
{



	target.draw(sprite);
	//target.draw(rect);
}

void Fairy::set_near_player(sf::Vector2f playerpos)
{
	if (player_is_moving) {
		rect.setPosition(playerpos.x - 32, playerpos.y - 16);
	}
	else {
		fly_around();
	}

	random_attack();


}

void Fairy::fly_around()
{


	if (direction == 1)
	{
		rect.move(0, -speed);
		velocity = sf::Vector2f(0, -speed);

	}
	else if (direction == 2)
	{
		rect.move(0, speed);
		velocity = sf::Vector2f(0, speed);


	}
	else if (direction == 3)
	{

		rect.move(-speed, 0);
		velocity = sf::Vector2f(-speed, 0);

	}
	else if (direction == 4)
	{

		rect.move(speed, 0.f);
		velocity = sf::Vector2f(speed, 0.f);

	}
	else {
	
		rect.move(velocity);
	}

	sprite.setPosition(rect.getPosition());
	direction = rand() % 32 + 1;


}

void Fairy::random_attack()
{
	int attackrandom = rand() % 50 + 1;

	if (attackrandom == 5) {
		want_to_attack = true;
	}

}



/*
void Fairy::get_colliding(std::vector<Projectile*> projectiles)
{
	//printf("das ist projektil size: %d\n", projectiles.size());
	for (int i = 0; i < projectiles.size(); ++i) {
		if (projectiles[i]->rect.getGlobalBounds().intersects(rect.getGlobalBounds())) {
			printf("fee wird angegriffen");
		}


	}

}
*/

void Fairy::set_pos_random()
{
	int x = rand() % 1000 + 1;
	int y = rand() % 700 + 1;

	rect.setPosition(sf::Vector2f(x, y));

}

void Fairy::check_out_of_window_and_reset()
{
	if (rect.getPosition().x < -30 || rect.getPosition().x > 1300 || rect.getPosition().y < -30 || rect.getPosition().y > 750) {

		rect.setPosition((rand() % 1200 + 1), (rand() % 700 + 1));

	}

}

