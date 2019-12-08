#include "NPC.h"




NPC::NPC(sf::Texture & texture, int pixelwidth, int pixelheight, int speed)
{

	sprite.setTexture(texture);

	rect.setSize(sf::Vector2f(pixelwidth, pixelheight));
	sprite.setTextureRect(sf::IntRect(0, 0, pixelwidth, pixelheight));
	rect.setPosition(100,100);

	sprite.setScale(1.5, 1.5);


	_speed = speed;
	_animation_row = 0;
	_animation_column = 0;
	_direction = 2;
	_directioncounter = 0;
	_pxwidth = pixelwidth;
	_pxheight = pixelheight;
	Bcolliding = false;


}

NPC::NPC()
{
}


NPC::~NPC()
{
}

void NPC::update(sf::Time elapsed)
{
	_elapsed += elapsed;
	old_pos = rect.getPosition();
	

	if (Bcolliding)
	{
		


	}else {
		//enum class eAnimation { WALKUP, WALKRIGHT, WALKDOWN, WALKLEFT };
		switch (_direction)
		{
		case 1: walk_up();  break;
		case 2: walk_right(); break;
		case 3: walk_down();  break;
		case 4: walk_left();  break;
		default:break;
		}
		
	}

	animate(_direction);


	if (_elapsed.asSeconds() > 0.29)
	{
		_elapsed = _elapsed.Zero;
		_animation_column++;
	
		if (_animation_column >= 3) { _animation_column = 0; }

	}



	_directioncounter++; //damit sich gegner nicht so schnell bewegen und ständig die directionm wechseln
	if (_directioncounter >= 30) { //erst nach 20 durchläufen wird überlegt die richtung zu ändern 
		_direction = rand() % 7 + 1;

		_directioncounter = 0;
	}

	sprite.setPosition(rect.getPosition());
	

}

void NPC::draw(sf::RenderTarget & target)
{
	target.draw(sprite);
}

void NPC::set_rect_pos(sf::Vector2f const & pos)
{
	rect.setPosition(pos);
}

void NPC::animate(int anim)
{


	switch (anim)
	{
	case 1:

			
			_animation_row = (int)eAnimation::WALKUP;
	    	sprite.setTextureRect(sf::IntRect(_animation_column * _pxwidth, _animation_row*_pxheight, _pxwidth, _pxheight)); break;

	case 2:

		_animation_row = (int)eAnimation::WALKRIGHT;
		sprite.setTextureRect(sf::IntRect(_animation_column * _pxwidth, _animation_row*_pxheight, _pxwidth, _pxheight)); break;


	case 3:

		_animation_row = (int)eAnimation::WALKDOWN;
		sprite.setTextureRect(sf::IntRect(_animation_column * _pxwidth, _animation_row*_pxheight, _pxwidth, _pxheight)); break;


	case 4:
		_animation_row = (int)eAnimation::WALKLEFT;
		sprite.setTextureRect(sf::IntRect(_animation_column * _pxwidth, _animation_row*_pxheight, _pxwidth, _pxheight)); break;


	default:  break;
	}


}

void NPC::walk_up()
{
	rect.move(0, -_speed);
}

void NPC::walk_down()
{

	rect.move(0, _speed);
}

void NPC::walk_left()
{
	rect.move(-_speed,0);
}

void NPC::walk_right()
{

	rect.move(_speed, 0);
}

void NPC::set_rect_to_area(sf::Vector2f const & pos, int fieldsize)
{
	sf::Vector2f finalpos;

	int _fieldsize = fieldsize * 32;



	int x1 = (pos.x - _fieldsize);
	int x2 = (pos.x + _fieldsize);

	//printf("das ist x1: %d : und x2 %d\n", x1, x2);

	int y1 = pos.y - fieldsize * 32;
	int y2 = pos.y + fieldsize * 32;


	printf("es wird jetzt eine zufdallszahlzwischen %d  und %d germacht \n", y1, y2);

	finalpos.x = ((rand() % x2) + x1);
	finalpos.y = ((rand() % y2) + y1);


	finalpos.x = (x1 + (rand() % (int)(x2 - x1 + 1)));
	finalpos.y = (y1 + (rand() % (int)(y2 - y1 + 1)));


	rect.setPosition(finalpos);

	printf("gegner wurde an pos gesetzt: %f : %f\n", finalpos.x, finalpos.y);
}
