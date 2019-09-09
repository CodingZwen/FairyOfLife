#include "Weather.h"



Weather::Weather(unsigned int count):
	m_particles(count),
	m_vertices(sf::Points, count),
	m_lifetime(sf::seconds(10)),
	m_emitter(0, 0)
{

	LoadShader();
	clock.restart();

}


Weather::~Weather()
{
}




void Weather::update(sf::Time elapsed, const sf::RectangleShape & rect)
{

	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			resetParticle(i);

		// update the position of the corresponding vertex
		if (p.lifetime > sf::seconds(5)) {
			m_vertices[i].position += p.velocity * elapsed.asSeconds();
		}

		if (p.lifetime < sf::seconds(5)) {
			//p.onground = true;

			//war player, alle schneflocken wurden gelöschtr
			if (rect.getGlobalBounds().contains(m_vertices[i].position)) {

				p.lifetime = sf::Time::Zero;
			}


		}


		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
		//m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		m_vertices[i].color.a = 255;
	}
}

void Weather::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;
	
	// draw the vertex array
	target.draw(m_vertices, states);
	
}



void  Weather::resetParticle(std::size_t index)
{
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % 360) * 3.14f / 180.f;
	float speed = (std::rand() % 50) + 50.f;
	m_particles[index].velocity = sf::Vector2f(10, speed / 100 * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 10000) + 9000);

	

	// reset the position of the corresponding vertex
	m_vertices[index].position = m_emitter;
}

void Weather::LoadShader()
{
	shader = new sf::Shader();


	if (!shader->loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\ShaderStuff\\SnowShader.frag", sf::Shader::Fragment))
	{
		printf("snowshaader  nicht erfolgreich\n");
	}

	texShaderSnow.create(1280,720);
	sprShaderSnow.setTexture(texShaderSnow.getTexture());

}
