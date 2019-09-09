#include "Tilemap_with_Collision.h"

//draw experiment in layer1 vorhanden

Tilemap_with_Collision::Tilemap_with_Collision(Map & map)
{
	
	ptrCurrentMap = &map;
	m_tilesize = 32;
	load_from_map();
	InitShaderShit();
	
}

Tilemap_with_Collision::Tilemap_with_Collision()
{
	m_tilesize = 32;
	animationcount = 0;

}



Tilemap_with_Collision::~Tilemap_with_Collision()
{
	//brauch ich nicht da der pointer auf den speicherbereich von
	//map zeigt und der wird intern von map gelöscht
	//wenn ich hier ptr auch lösche, dann double free
	//if (ptr_binary_map_array != NULL)delete[] ptr_binary_map_array;

}


void Tilemap_with_Collision::draw_layer1(sf::RenderWindow & target)
{
	float f = 0;
	watershader->setUniform("time", timer.getElapsedTime().asSeconds());
	watershader->setUniform("level", f);


	states.texture = &tWatertile;
	states.shader = watershader;
	target.draw(VAWater, states);

	target.draw(Vertexmap1, ptrCurrentMap->get_texture());



}

void Tilemap_with_Collision::draw_layer2(sf::RenderWindow & target)
{
	target.draw(Vertexmap2, ptrCurrentMap->get_texture());

}

void Tilemap_with_Collision::draw_VertexMap(sf::RenderWindow & target)
{
	target.draw(Vertexmap1, ptrCurrentMap->get_texture());
	target.draw(Vertexmap2, ptrCurrentMap->get_texture());
}

bool Tilemap_with_Collision::load_from_map()
{
	
	unsigned int tileSize = 32;
	Vertexmap1.setPrimitiveType(sf::Quads);
	Vertexmap1.resize(ptrCurrentMap->get_width() * ptrCurrentMap->get_height() * 4);
	Vertexmap2.setPrimitiveType(sf::Quads);
	Vertexmap2.resize(ptrCurrentMap->get_width() * ptrCurrentMap->get_height() * 4);
	VAWater.setPrimitiveType(sf::Quads);
	VAWater.resize(ptrCurrentMap->get_width() * ptrCurrentMap->get_height() * 4);



	for (unsigned int i = 0; i < ptrCurrentMap->get_width(); ++i)
		for (unsigned int j = 0; j < ptrCurrentMap->get_height(); ++j)
		{


			// get the current tile number
			int FieldNumber = i + j * ptrCurrentMap->get_width();
			int tileNumber = ptrCurrentMap->first_layer(FieldNumber);
			tileNumber--;
			int tu = tileNumber % (ptrCurrentMap->get_texture()->getSize().x / 32);
			int tv = tileNumber / (ptrCurrentMap->get_texture()->getSize().x / 32);
			sf::Vertex* quad = &Vertexmap1[(FieldNumber) * 4];


			if (!ptrCurrentMap->animation_tile(i + j * ptrCurrentMap->get_width()))
			{
				// find its position in the tileset texture
				

				// get a pointer to the current tile's quad
				

				// define its 4 corners
				quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
				quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
				quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
				quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
				quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);

			}
			else
			{
				
				quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
				quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
				quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
				quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

				// define its 4 texture coordinates
				quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
				quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);


				sf::Vertex* Wquad = &VAWater[(FieldNumber) * 4];

				// define its 4 corners
				Wquad[0].position = sf::Vector2f(i * (tileSize), j * (tileSize));
				Wquad[1].position = sf::Vector2f((i + 1) *(tileSize), j *(tileSize));
				Wquad[2].position = sf::Vector2f((i + 1) *(tileSize), (j + 1) *(tileSize));
				Wquad[3].position = sf::Vector2f(i * (tileSize), (j + 1) * (tileSize));

				// define its 4 texture coordinates
				Wquad[0].texCoords = sf::Vector2f(0, 0);
				Wquad[1].texCoords = sf::Vector2f(tileSize, 0);
				Wquad[2].texCoords = sf::Vector2f(tileSize, tileSize);
				Wquad[3].texCoords = sf::Vector2f(0, tileSize);


			}

			//second layer
			tileNumber = ptrCurrentMap->second_layer(i + j * ptrCurrentMap->get_width());
			tileNumber--;

			// find its position in the tileset texture
			 tu = tileNumber % (ptrCurrentMap->get_texture()->getSize().x / 32);
			 tv = tileNumber / (ptrCurrentMap->get_texture()->getSize().x / 32);

			// get a pointer to the current tile's quad
			quad = &Vertexmap2[(i + j * ptrCurrentMap->get_width()) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
			quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
			quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
			quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);





		}
		
	return true;

}


void Tilemap_with_Collision::setBlack()
{
	alpha = 20;
	updateAlpha();
}

void Tilemap_with_Collision::updateAlpha()
{

	for (unsigned int i = 0; i < ptrCurrentMap->get_width(); ++i)
		for (unsigned int j = 0; j < ptrCurrentMap->get_height(); ++j)
		{

			int FieldNumber = i + j * ptrCurrentMap->get_width();
			int tileNumber = ptrCurrentMap->first_layer(FieldNumber);
			tileNumber--;
			int tu = tileNumber % (ptrCurrentMap->get_texture()->getSize().x / 32);
			int tv = tileNumber / (ptrCurrentMap->get_texture()->getSize().x / 32);
			sf::Vertex* quad = &Vertexmap1[(FieldNumber) * 4];

			

			quad[0].color = sf::Color(color, color, color, alpha);
			quad[1].color = sf::Color(color, color, color, alpha);
			quad[2].color = sf::Color(color, color, color, alpha);
			quad[3].color = sf::Color(color, color, color, alpha);

			


		}

	
}

void Tilemap_with_Collision::set_map(Map  &  map)
{

	ptrCurrentMap = &map;
//	m_tileset_sprite.setTexture(*ptrCurrentMap->get_texture());
	load_from_map();
	
}




bool Tilemap_with_Collision::collide_engine(sf::Vector2f const & objectpos,sf::Vector2f offset,unsigned int tileSize)
{

	int x = (((objectpos.x)+ offset.x) / tileSize);
	int y = (((objectpos.y) + offset.y) / tileSize); //es lag am float, die kommazahlen haben durch die multiplikation zuviel verhoben.

	y *= ptrCurrentMap->get_width(); //feldbreite
	
	
	return returncoll_binary(x+y);
}
				//25 , 32 oder sowas
bool Tilemap_with_Collision::fieldIsValid(int x, int y)
{

	y *= ptrCurrentMap->get_width(); //feldbreite	

	//printf("zurückgegebenes feld: %d ::\n", x + y);

	return !returncoll_binary(x+y);



	
}

unsigned int Tilemap_with_Collision::current_field(sf::Vector2f const & coords)
{
	
	int x = (((coords.x)) / 32);
	int y = (((coords.y) + 6) / 32); 

	y *= ptrCurrentMap->get_width(); //feldbreite	

	int ergebnis = (x + y);

	return ergebnis;

}



void Tilemap_with_Collision::InitShaderShit()
{
	distortionMap.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\ShaderStuff\\noiseWater.png") ? printf("erfolgreich") : printf("distortionMapT nicht erfolgreich\n");
	distortionMap.setRepeated(true);
	watershader = new sf::Shader();

	if (!watershader->loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\ShaderStuff\\watershader.frag.txt", sf::Shader::Fragment))
	{
		printf("watershader nicht erfolgreich\n");
	}
	else
	{
		printf("watershader  erfolgreich\n");
	}

	watershader->setUniform("distortionMapTexture", distortionMap);


	tWatertile.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\ShaderStuff\\watertile4.png") ? printf("erfolgreich") : printf("distortionMapT nicht erfolgreich\n");

}

void Tilemap_with_Collision::inkrementDarkness()
{
	if (alpha > 1)
	{
		alpha--;
		updateAlpha();
	}
}

void Tilemap_with_Collision::inkrementLight()
{
	if (alpha < 255)
	{
		alpha++;
		updateAlpha();
	}
}




//array beschreibung:
// 00000000| 0 | 0 | 000000 0000 0 | 000 00000000
//	animtion /ja/nein   | collide ja/nein	|  tilsetkachel für deko() auch bis 11tes  |   tilesetkachel() bis 11tes bit
//für 23 bit stelle setzen |4194304 , 4194303 zum & um die ersten 11 stellen zu bekommen




//wird grade nicht benutzt, war auch die version in dem ich die tmx datei
//in eine txt datei umgewandelt habe und aufgeräumt habe und dann noch
//zum erkennen der arrays ein # setzen musste. ist scheise kann eigentlich gelöscht werden
