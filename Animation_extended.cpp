#include "Animation_extended.h"



Animation_extended::Animation_extended() : m_texture(NULL)
{
}


Animation_extended::~Animation_extended()
{
}

void Animation_extended::addFrame(sf::IntRect rect)
{
	m_frames.push_back(rect);
}

void Animation_extended::addAllFrames(sf::IntRect StartRect, unsigned int Amount, const sf::Texture& texture)
{
	//achtung nur qudratische bilder sind somit möglich
	sf::IntRect rect = StartRect;
	unsigned int frameWidth = rect.width;

	for (int i = 0; i < Amount; i++) {
	
		m_frames.push_back(rect);
		rect.left += frameWidth;
	}

	m_texture = &texture;
}

void Animation_extended::setSpriteSheet(const sf::Texture & texture)
{
	m_texture = &texture;
}

const sf::Texture * Animation_extended::getSpriteSheet() const
{
	return m_texture;
}

std::size_t Animation_extended::getSize() const
{
	return m_frames.size();
}

const sf::IntRect & Animation_extended::getFrame(std::size_t n) const
{
	return m_frames[n];
}
