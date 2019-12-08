#pragma once
#include <vector>
#include <SFML\Graphics.hpp>



//das ist eine animation
//davon werden mehrer erstellt

class Animation_extended
{
public:

	Animation_extended();
	~Animation_extended();

	void addFrame(sf::IntRect rect);
	void addAllFrames(sf::IntRect StartRect, unsigned int Amount, const sf::Texture& texture);
	void setSpriteSheet(const sf::Texture& texture);
	
	const sf::Texture* getSpriteSheet() const;
	
	//framecount
	size_t getSize() const;
	const sf::IntRect& getFrame(size_t n) const;



private :

	std::vector<sf::IntRect> m_frames;
	const sf::Texture* m_texture;

};

