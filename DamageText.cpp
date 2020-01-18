#include "DamageText.h"



void DamageText::update(sf::Time elapsed, sf::Vector2f pos)
{
	_elapsed += elapsed;


	dx = cos(angle*RADIANT) * speed; //bei 0 also nach rechts kommt hier cos =1 raus
	dy = sin(angle*RADIANT) * speed; //hier kommt bei angle 0, also sin 0 = 0 raus deswegen nach rechts
	text.move(dx, dy);

	angle += 3.01f;

	if (angle > 110) {
		destroy = true;
	}

	//printf("damataext update angle:%f \n", angle);


}

void DamageText::draw(sf::RenderTarget & t)
{
	t.draw(text);
}

DamageText::DamageText()
{
	
}


DamageText::~DamageText()
{
}
