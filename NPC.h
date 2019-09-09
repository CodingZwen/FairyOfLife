#include <SFML\Graphics.hpp>
#pragma once


//und muss ich noch von entitiy gescheit erben lassen

//achtung hier ist animationsreihenfolge anders als bei enemy

class NPC
{


	enum class eAnimation { WALKUP, WALKRIGHT, WALKDOWN, WALKLEFT };

public:
	NPC(sf::Texture &texture, int pixelwidth, int pixelheight,int speed);
	NPC();
	~NPC();


	void update(sf::Time elapsed);
	void draw(sf::RenderTarget &target);
	void set_rect_pos(sf::Vector2f const &pos);

	sf::Vector2f get_old_pos() { return old_pos; }

	void animate(int anim);

	void walk_up();
	void walk_down();
	void walk_left();
	void walk_right();
	

	//für npc verteiler
	void set_rect_to_area(sf::Vector2f const &fieldpos, int fieldsize);

	const sf::RectangleShape &get_npc_rect() { return rect; }
	void set_old_pos() { rect.setPosition(old_pos); }
	void set_collide() { Bcolliding = true; }
	void not_collide() { Bcolliding = false; }

private:

	//for animation
	int _pxwidth;
	int _pxheight;
	int _animation_row;
	int _animation_column; //in enemy counterwalking 0-2

	int _speed;
	int _direction;
	int _last_direction;
	int _directioncounter;
	

	bool Bcolliding;
	sf::Vector2f old_pos;

	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Time _elapsed;

};

