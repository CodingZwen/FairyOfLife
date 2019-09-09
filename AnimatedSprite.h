#pragma once
#include "Animation_extended.h"
#include <iostream>
class AnimatedSprite : public sf::Drawable, public sf::Transformable
{

	bool firstanimationdone = false;

public:

	sf::Transform myTransform;

	//explicite konstruktoiren müssen immer mit klammer aufgerufen werden
	explicit AnimatedSprite(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);

	void update(sf::Time deltaTime);
	void setAnimation(const Animation_extended& animation);
	void setFrameTime(sf::Time time);
	void play();
	void play(const Animation_extended& animation);
	void pause();
	void stop();
	void setLooped(bool looped);
	void setColor(const sf::Color& color);
	const Animation_extended* getAnimation() const;
	const void setTexture(sf::Texture &spriteSheet);
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;
	bool isLooped() const;
	bool isPlaying() const;
	bool firstAnimationDone() { return firstanimationdone; }
	sf::Time getFrameTime() const;
	void setFrame(std::size_t newFrame, bool resetTime = true);
	void setRot(float rotation);


	//void playOnceAnddoNextAnimation();

	//own
	void setCurrentAnimation(std::string animationName);
	void insertAnimation(sf::IntRect StartRect, unsigned int Amount, const sf::Texture& texture,std::string nameOfAnimation);
	unsigned int getAnimationAmount();

private:
	std::map<std::string, Animation_extended> AnimationPool;
	const Animation_extended* m_animation;


	sf::Time m_frameTime;
	sf::Time m_currentTime;
	std::size_t m_currentFrame;
	bool m_isPaused;
	bool m_isLooped;

	//diese texture wird immer gesetzt und in der draw funktion verwendet
	//Texture kommt vom m_animation pointer
	const sf::Texture* m_texture;
	sf::Vertex m_vertices[4];



	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};

