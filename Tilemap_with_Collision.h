#pragma once
#include "Map.h"


using namespace std;

class Tilemap_with_Collision
{
public:

	//pfad tileset, kachelgroesse pixel , breite in pixel von tileset
	
	Tilemap_with_Collision(Map &map);
	Tilemap_with_Collision();
	~Tilemap_with_Collision();

	//all layers and hole map
	void draw_layer1(sf::RenderWindow & target);
	void draw_layer2(sf::RenderWindow & target);
	
	void draw_VertexMap(sf::RenderWindow &target);
	bool load_from_map();

	
	void setBlack();
	void updateAlpha();
	//da ja nicht soviele tile im zweiten sind können wir ruhig hier alles zeichen theoretisch??
	//void draw_layer2_x(sf::RenderWindow & target, sf::Time elapsed);

	void set_map(Map &map);

	int size() { return sizeof(*this); }

	//bool returncoll_binary(int n) { return _map[n] >> 22&1;}
	bool returncoll_binary(int n) { return ptrCurrentMap->collision_tile(n); }
	
	int get_map_width() { return ptrCurrentMap->get_width(); }
	int get_map_height() { return ptrCurrentMap->get_height(); }

	

	//errechnet auss der position und der jeweiligen, da derzeitige feld
	bool collide_engine(sf::Vector2f const & objectpos, sf::Vector2f offset, unsigned int tileSize=32);
	bool fieldIsValid(int x, int y);

	//gibt derzeitiges feld zurück aber aufpassen! je nachdem welche kante des rects berechnet wird
	//das soll heißen fuß unbten rechts ist evtl anderes feld als kopf oben links
	//eventuell ungenaue da ich float in int umwandle
	unsigned int current_field(sf::Vector2f const &coords);
	
	
	void InitShaderShit();
	//unbedingt noch verfschieben
	void inkrementDarkness();
	void inkrementLight();

	sf::Sprite getMinimap();
	sf::CircleShape getMiniMapasCircle(); //template??
	void initMiniMap();

private:

	short alpha = 255;
	short color = 255;

	sf::Time tempelapsed;
	sf::Clock uhr;

	Map *ptrCurrentMap;

	sf::VertexArray Vertexmap1;
	sf::VertexArray Vertexmap2;
	

	sf::Clock timer;
	sf::VertexArray VAWater;
	sf::Texture tWatertile;
	sf::Shader *watershader;
	sf::RenderStates states;
	sf::Texture distortionMap;

	//minimap
	sf::RenderTexture minimap;
	sf::CircleShape minimapCircle;
	sf::CircleShape minimapBackground;
	
	
	

};

