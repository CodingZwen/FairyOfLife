#pragma once
#include <SFML\Graphics.hpp>

#include <vector>

//muss noch durch entitiy angepasst werden
enum class Fairy_Type { FIRE_FAIRY, ICE_FAIRY };

class Fairy  
{
public:
	Fairy(Fairy_Type type);
	Fairy();
	~Fairy();

	void Update(sf::Time elapsed,sf::Vector2f);
	void draw(sf::RenderTarget &target);
	void set_near_player(sf::Vector2f playerpos);
	void fly_around();
	void random_attack();

	//hier mus ich in entitiys umwandeln
	//void get_colliding(std::vector<Projectile*> projectiles);

	void set_pos_random();
	void set_pos(sf::Vector2f pos) {
		rect.setPosition(pos);
	}

	void check_out_of_window_and_reset();

	sf::RectangleShape rect;
	sf::Texture *texture;
	sf::Sprite sprite;



	sf::Time tempElapsedTime;

	bool player_is_moving = true;
	bool want_to_attack = false;
	bool got_attacked = false;


	int speed = 2;
	int direction = 1;
	int frames = 0;
	int frame = 0;
	int framewidth = 0;

	sf::Vector2f velocity;

};

