#pragma once
#include "SingleText.h"
class DamageText : public SingleText
{


	void update(sf::Time elapsed, sf::Vector2f pos)override;
	void draw(sf::RenderTarget &t)override;



public:
	DamageText();
	~DamageText();



};

