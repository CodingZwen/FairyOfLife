#include "NPC_Handler.h"



NPC_Handler::NPC_Handler()
{
	texture_loaded = false;
}


NPC_Handler::~NPC_Handler()
{
}

void NPC_Handler::init_textures()
{
	

	sf::Texture texture;


	if (!texture.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\npc_Assets\\npc1.png")) {
		printf("fehler bveimn laden der feuerball texture!\n");
	}
	else {
		printf("erfolgreich\n");
	}

	npc_textures.push_back(texture);

	
	if (!texture.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\npc_Assets\\npc2.png")) {
		printf("fehler bveimn laden der feuerball texture!\n");
	}
	else {
		printf("erfolgreich\n");
	}

	npc_textures.push_back(texture);



	if (!texture.loadFromFile("Spiel_Projekt_Protectyourisle_Assets\\npc_Assets\\npc3.png")) {
		printf("fehler bveimn laden der feuerball texture!\n");
	}
	else {
		printf("erfolgreich\n");
	}

	npc_textures.push_back(texture);


	if (npc_textures.size() > 0) {

		texture_loaded = true;
		printf("npcs geladen : %d \n", npc_textures.size());

	}else {
	
		printf("texturevector konnte nicht geladen werden \n");
		texture_loaded = false;
	}


}

bool NPC_Handler::init_npcs(int count, sf::Vector2f spawnpos)
{

	if (!texture_loaded)return false;

	if (count < 0 || count > 100) { count = 20; }

	npccount = count;
	int textures = (npc_textures.size()-1);
		
	for (int i = 0; i < count; i++) {

		//erzeugt zufalls zahl zwischen 0 und texturvektorgrose um dann eine der sich im
		//vecktor befindenden texture zu laden
		int random = (0 + (rand() % (int)(textures - 0 + 1)));

		if (random > textures) { printf("zufallszahl zu hoch\n"); return false; }

		NPC npc(npc_textures.at(random),24,32,2);
		npc.set_rect_to_area(spawnpos, 10);
		vnpc.push_back(npc);

		}
	
	
			
	
	return true;

}

void NPC_Handler::update(sf::Time elapsed)
{
	
	for (int i = 0; i < vnpc.size(); i++) {
			vnpc[i].update(elapsed);
	
	}
}

void NPC_Handler::draw(sf::RenderTarget & target)
{
	for (int i = 0; i < vnpc.size(); i++) {
		vnpc[i].draw(target);

	}
}


/*
void NPC_Handler::collide(Tilemap & map)
{


	sf::Vector2f rect;


	for (int i = 0; i < vnpc.size(); i++) {
		rect = vnpc[i].get_npc_rect().getPosition();


		int x = (((rect.x)) / 32);
		int y = (((rect.y) + 6) / 32); //es lag am float, die kommazahlen haben durch die multiplikation zuviel verhoben.

		int x2 = (((rect.x) + 20) / 32);
		int y2 = (((rect.y) + 6) / 32);

		int x3 = (((rect.x)) / 32);
		int y3 = (((rect.y) + 37) / 32); //es lag am float, die kommazahlen haben durch die multiplikation zuviel verhoben.

		int x4 = (((rect.x) + 20) / 32); //kante unten
		int y4 = (((rect.y) + 37) / 32);

		y *= map.get_mapwidth(); //feldbreite
		y2 *= map.get_mapwidth(); //feldbreite
		y3 *= map.get_mapwidth();
		y4 *= map.get_mapwidth();

		int ergebnis = (x + y);
		int ergebnis2 = (x2 + y2);
		int ergebnis3 = (x3 + y3);
		int ergebnis4 = (x4 + y4);




		bool kollidiert = map.returncoll_binary(ergebnis);
		bool kollidiert2 = map.returncoll_binary(ergebnis2);
		bool kollidiert3 = map.returncoll_binary(ergebnis3);
		bool kollidiert4 = map.returncoll_binary(ergebnis4);




		if (kollidiert || kollidiert2 || kollidiert3 || kollidiert4) {
		
			vnpc[i].set_rect_pos(vnpc[i].get_old_pos());
			
		}


	}


}
*/