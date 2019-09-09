#pragma once
#include <list>
#include <vector>
#include "Tilemap_with_Collision.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <thread>
class AsternGetuned
{

private : 

	bool searching = false;
	bool drawing = 0;
	bool limited = false;
	unsigned int limit = 0;
	sf::Uint8 alphaColor=50;

	struct sNode
	{
		bool bObstacle = false;			// Is the node an obstruction?
		bool bVisited = false;			// Have we searched this node before?
		float fGlobalGoal;				// Distance to goal so far
		float fLocalGoal;				// Distance to goal if we took the alternative route
		int x;							// Nodes position in 2D space
		int y;
		std::vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent;					// Node connecting to this node that offers shortest parent
	};

	float distance(sNode* a, sNode *b);
	int heuristic(sNode* a, sNode *b);

	void reset();
	
	//erstellt ein komplettes Arrays nodes
	sNode *nodes = nullptr;
	int nMapWidth = 0;
	int nMapHeight = 0;

	sNode *nodeStart = nullptr;
	sNode *nodeZiel = nullptr;

	sNode *nodeCurrent;
	std::list<sNode*> listNotTestedNodes;
	std::vector<sNode*> vecNotTestedNodes;



	Tilemap_with_Collision *ptrTilemap;

	int getIndexOfBestNode(std::vector<sNode*> &nodes);


public:
	AsternGetuned();
	~AsternGetuned();

	std::vector<sf::Vector2i> feedEnemyWithWaypointsVector();
	std::list<sf::Vector2i> feedEnemyWithWaypointsList();
	bool init(unsigned int mapWidth, unsigned int mapHeight, Tilemap_with_Collision &t);
	void resetObstacles(Tilemap_with_Collision &t);
	void draw(sf::RenderTarget &t);
	void initSearch(int startx, int starty, int targetx, int targety);
	bool solve();
	std::vector<sf::Vector2i> solveWithVector();
	void run(int iterations);
	void solveWithThread();

	void setNodeObstacle(int x, int y);
	void setNodeNotObstacle(int x, int y);


	//heapshit


	void heapify(std::vector<sNode*> &list, int n, int i);
	void heapSort(std::vector<sNode*> &list, int n);
	


	
};

