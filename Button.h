#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//IDLE IST NOTHING HAPPEN
enum button_states {BTN_IDLE,BTN_HOVER, BTN_ACTIVE};

class Button
{

	short unsigned buttonState;
	sf::RectangleShape shape;
	sf::Font *font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Vector2f viewCenterpos;
	sf::Vector2f offsetviewCenter;

public:
	Button(float x, float y, float width, float height, sf::Font *font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color actoveColor);
	~Button();

	const bool isPressed() const;
 	void update(const sf::Vector2f mousepos);
	void render(sf::RenderTarget* target);
	void setPosition(sf::Vector2f newpos);
	void updatePosition(sf::Vector2f viewcenter);

};

#endif
