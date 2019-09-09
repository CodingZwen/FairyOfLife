#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "NPC.h"


class NPC_Handler
{




public:
	NPC_Handler();
	~NPC_Handler();

	void init_textures();
	bool init_npcs(int count, sf::Vector2f spawnpos);

	void update(sf::Time elapsed);
	void draw(sf::RenderTarget &target);


	//hier einfach neue maü übergeben sollte reichen
	//void collide(Tilemap &map);


private :

	int npccount;
	bool texture_loaded;
	 
	//texture wegmachen und übergeben und npc von entity erben assen
	std::vector<sf::Texture> npc_textures;
	std::vector<NPC> vnpc;
	



};

