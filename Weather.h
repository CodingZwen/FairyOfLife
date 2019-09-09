#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class Weather : public sf::Transformable , public sf::Drawable
{
public:

	Weather(unsigned int count);
	~Weather();


	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
	}

	void update(sf::Time elapsed, const  sf::RectangleShape &rect);

private : 

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		bool onground = false;
	};

	void resetParticle(std::size_t index);
	void LoadShader();
	

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;

	sf::Sprite sprShaderSnow;
	sf::RenderTexture texShaderSnow;
	sf::Shader *shader;
	sf::Clock clock;

};

