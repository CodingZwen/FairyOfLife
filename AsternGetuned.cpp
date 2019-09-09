#include "AsternGetuned.h"



float AsternGetuned::distance(sNode * a, sNode * b)
{
	//fluglinie
	return sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}

int AsternGetuned::heuristic(sNode * a, sNode * b)
{
	return distance(a, b);
}

void AsternGetuned::solveWithThread()
{
	
}

void AsternGetuned::setNodeObstacle(int x, int y)
{
	nodes[y * nMapWidth + x].bObstacle = true;
}

void AsternGetuned::setNodeNotObstacle(int x, int y)
{
	nodes[y * nMapWidth + x].bObstacle = false;
}

void AsternGetuned::heapify(std::vector<sNode*>& list, int n, int i)
{
	int largest = i; // Initialize largest as root , largest = i, i ist haelfte vom array -1 -> 2 1 0
	int l = 2 * i + 1; // left = 2*i + 1 , 2*2 +1 = 5, 2*1 +1 =3, 2 0 + 1 =1; -> 5 3 1
	int r = 2 * i + 2; // right = 2*i + 2 , 2*2+2 = 6, 2*1+2=4, 2*0+2 =2;	   -> 6 4 2


	// If left child is larger than root 
	//5,3,1 < 6 && arr[5,3,1] > arr[2,1,0]
	if (l < n && list[l]->fGlobalGoal > list[largest]->fGlobalGoal)
		largest = l;

	// If right child is larger than largest so far 
	//6,4,2 < 6 && arr[6,4,2] > arr[2,1,0]
	if (r < n && list[r]->fGlobalGoal > list[largest]->fGlobalGoal)
		largest = r;

	// If largest is not root 
	if (largest != i) {
		std::swap(list[i], list[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(list, n, largest);
	}
}

void AsternGetuned::heapSort(std::vector<sNode*>& list, int n)
{
	for (int i = n * 0.5 - 1; i >= 0; i--)
		heapify(list, n, i); // params: array,6,2 | 1 | 0 bzw mitte vom array und dann wird runtergezaehlt

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--) {
		// Move current root to end 
		std::swap(list[0], list[i]);

		// call max heapify on the reduced heap 
		heapify(list, i, 0);
	}
}

void AsternGetuned::reset()
{
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			nodes[y*nMapWidth + x].bVisited = false;
			nodes[y*nMapWidth + x].fGlobalGoal = INFINITY;
			nodes[y*nMapWidth + x].fLocalGoal = INFINITY;
			nodes[y*nMapWidth + x].parent = nullptr;	// No parents
		}


	listNotTestedNodes.clear();
	vecNotTestedNodes.clear();

}

bool AsternGetuned::init(unsigned int mapWidth, unsigned int mapHeight,Tilemap_with_Collision &t)
{
	nMapWidth=mapWidth;
	nMapHeight=mapHeight;

	nodes = new sNode[nMapWidth * nMapHeight];
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			//0*40+0=0
			//1*40+0=40
			nodes[y * nMapWidth + x].x = x; // ...because we give each node its own coordinates
			nodes[y * nMapWidth + x].y = y;
						
			nodes[y * nMapWidth + x].bObstacle = t.returncoll_binary(y * nMapWidth + x);
			
			nodes[y * nMapWidth + x].parent = nullptr;
			nodes[y * nMapWidth + x].bVisited = false;
		}

	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			if (y > 0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
			if (y < nMapHeight - 1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
			if (x > 0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
			if (x < nMapWidth - 1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);

			// We can also connect diagonally
			/*if (y>0 && x>0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
			if (y<nMapHeight-1 && x>0)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
			if (y>0 && x<nMapWidth-1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
			if (y<nMapHeight - 1 && x<nMapWidth-1)
				nodes[y*nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
			*/
		}

	//evtl * 0.5
	nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
	nodeZiel = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth - 2];
	return true;
}

void AsternGetuned::resetObstacles(Tilemap_with_Collision & t)
{
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
		
			nodes[y * nMapWidth + x].bObstacle  = t.returncoll_binary(y * nMapWidth + x);

		}
}

bool AsternGetuned::solve()
{


	//solange openlist nicht leer ist und derzeitige note nicht ziel ist
	while(!listNotTestedNodes.empty() && nodeCurrent != nodeZiel)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
	{
		listNotTestedNodes.sort([&](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });
		


		//wenn openlist nicht leer und und billigstens bereits besucht dann objekt rausmachen
		//liste wird davor sortier siehe oben
		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
		{
			
			
			listNotTestedNodes.pop_front();
		}

	
		//wenn openlist leer dann raus hier 
		if (listNotTestedNodes.empty())
		{
			printf("openlist ist leer, kein weg gefunden!beende solve");
			return false;
		}




		//hol mir das erste bzw, billigste und setze es auf besucht
		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true;


		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
		{

			// ... and only if the neighbour is not visited and is 
					// not an obstacle, add it to openlist List
			if (!nodeNeighbour->bVisited && !nodeNeighbour->bObstacle)
				listNotTestedNodes.push_back(nodeNeighbour);

			// Calculate the neighbours potential lowest parent distance
			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorithm, so it knows if its getting better or worse. At some
				// point the algo will realise this path is worse and abandon it, and then go
				// and search along the next best path.
				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeZiel);
			}
		}

		if (nodeCurrent == nodeZiel) {

			printf("ziel gefunden\n");

		}
		
		
	}
	
	return true;
}

std::vector<sf::Vector2i> AsternGetuned::solveWithVector()
{
	

	//solange openlist nicht leer ist und derzeitige note nicht ziel ist
	while (!vecNotTestedNodes.empty() && nodeCurrent != nodeZiel)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
	{
		//vecNotTestedNodes.sort([&](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });
		heapSort(vecNotTestedNodes, vecNotTestedNodes.size());


		//wenn openlist nicht leer und und billigstens bereits besucht dann objekt rausmachen
		while (!vecNotTestedNodes.empty() && vecNotTestedNodes.front()->bVisited)
		{
			//printf("am löchen\n");
			vecNotTestedNodes.erase(vecNotTestedNodes.begin());
		}


		//wenn openlist leer dann raus hier 
		if (vecNotTestedNodes.empty())
		{
			printf("openlist ist leer, kein weg gefunden!beende solve");
			
		}




		//hol mir das erste bzw, billigste und setze es auf besucht
		nodeCurrent = vecNotTestedNodes.front();
		nodeCurrent->bVisited = true;


		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
		{

			// ... and only if the neighbour is not visited and is 
					// not an obstacle, add it to openlist List
			if (!nodeNeighbour->bVisited && !nodeNeighbour->bObstacle)
				vecNotTestedNodes.push_back(nodeNeighbour);

			// Calculate the neighbours potential lowest parent distance
			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

				// The best path length to the neighbour being tested has changed, so
				// update the neighbour's score. The heuristic is used to globally bias
				// the path algorithm, so it knows if its getting better or worse. At some
				// point the algo will realise this path is worse and abandon it, and then go
				// and search along the next best path.
				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeZiel);
			}
		}

		if (nodeCurrent == nodeZiel) {

			std::vector<sf::Vector2i> l;


			if (nodeZiel != nullptr)
			{
				//printf("zielvorhanden x: %d | y: %d\n", nodeZiel->x, nodeZiel->y);;

				//nächster punkt von startpunkt
				//in while wird sich dann richtung ziel gehangelt
				sNode *p = nodeZiel;
				//l.push_front(sf::Vector2i(p->x*32 , p->y*32 ));

				while (p->parent != nullptr)
				{
					l.push_back(sf::Vector2i(p->x * 32, p->y * 32));
					p = p->parent;				//davor * 32 

					//printf("targetx: %d, targety: %d\n", p->x, p->y);

				}
				//system("pause");
			}
			/*
			list <sf::Vector2i>::iterator it;
			it = l.begin();
			for (; it != l.end();it++)
			{
				cout << it->x << " : " << it->y << endl;
			}
			system("pause");

			*/
			return l;
			

		}
		
	}



	
}


void AsternGetuned::run(int iterations)
{
	for (int i = 0; i < iterations; i++) {
		solve();
	}
}

void AsternGetuned::initSearch(int startx, int starty, int targetx, int targety)
{


	if ((startx >= 0 && startx < nMapWidth) && (targetx >= 0 && targetx < nMapWidth))
		if ((starty >= 0 && starty < nMapHeight)&& (targety >= 0 && targety < nMapHeight))
		{
			 
				reset();
				nodeStart = &nodes[starty * nMapWidth + startx];
				nodeZiel = &nodes[targety * nMapWidth + targetx];
				nodeCurrent = nodeStart;
				nodeStart->fLocalGoal = 0.0f;
				nodeStart->fGlobalGoal = heuristic(nodeStart, nodeZiel);
				
				//if(!nodeStart->bObstacle)
				listNotTestedNodes.push_back(nodeStart);
			
		}
}

void AsternGetuned::draw(sf::RenderTarget & t)
{
	if (drawing)
	{
		sf::RectangleShape obstacle;
		obstacle.setSize(sf::Vector2f(28, 28));
		obstacle.setFillColor(sf::Color(50, 15, 0, alphaColor));


		sf::RectangleShape groundrect;
		groundrect.setSize(sf::Vector2f(28, 28));
		groundrect.setFillColor(sf::Color(0, 0, 0, 0));

		sf::RectangleShape closedlistrect;
		closedlistrect.setSize(sf::Vector2f(28, 28));
		closedlistrect.setFillColor(sf::Color(255, 0, 0, alphaColor));

		sf::RectangleShape startrect;
		startrect.setSize(sf::Vector2f(100, 100));
		startrect.setFillColor(sf::Color::Magenta);


		sf::RectangleShape targetrect;
		targetrect.setSize(sf::Vector2f(100, 100));
		targetrect.setFillColor(sf::Color::White);

		sNode *ptrCurrentNode;

		for (int x = 0; x < nMapWidth; x++)
			for (int y = 0; y < nMapHeight; y++)
			{
				ptrCurrentNode = &nodes[y * nMapWidth + x];



				if (ptrCurrentNode->bObstacle)
				{
					obstacle.setPosition(ptrCurrentNode->x * 32, ptrCurrentNode->y * 32);
					t.draw(obstacle);

				}
				else
				{
					groundrect.setPosition(ptrCurrentNode->x * 32, ptrCurrentNode->y * 32);
					t.draw(groundrect);
				}

				//closedlist?
				if (ptrCurrentNode->bVisited)
				{
					closedlistrect.setPosition(ptrCurrentNode->x * 32, ptrCurrentNode->y * 32);
					t.draw(closedlistrect);
				}



				//ziel
				if (&nodes[y * nMapWidth + x] == nodeZiel)
				{
					targetrect.setPosition(ptrCurrentNode->x * 32, ptrCurrentNode->y * 32);
					//printf("\nzielx: %d ziely: %d\n", ptrCurrentNode->x * 32, ptrCurrentNode->y * 32);

				}

				if (&nodes[y * nMapWidth + x] == nodeStart)
				{
					startrect.setPosition(ptrCurrentNode->x * 32, ptrCurrentNode->y * 32);
				}

			}

		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(28, 28));
		rect.setFillColor(sf::Color(1, 1, 1, 150));

		//weg
		if (nodeZiel != nullptr)
		{
			//printf("zielvorhanden x: %d | y: %d\n", nodeZiel->x, nodeZiel->y);;

			sNode *p = nodeZiel;

			rect.setPosition(p->x * 32, p->y * 32);
			t.draw(rect);
			while (p->parent != nullptr)
			{
				rect.setPosition(p->x * 32, p->y * 32);
				t.draw(rect);
				// Set next node to this node's parent
				p = p->parent;

			}



		}

	}

}

std::vector<sf::Vector2i> AsternGetuned::feedEnemyWithWaypointsVector()
{

	std::vector<sf::Vector2i> l;

	if (nodeZiel != nullptr)
	{
		//printf("zielvorhanden x: %d | y: %d\n", nodeZiel->x, nodeZiel->y);;
		
		//nächster punkt von startpunkt
		//in while wird sich dann richtung ziel gehangelt
		sNode *p = nodeZiel;
		l.push_back(sf::Vector2i(p->x*32, p->y*32));
		
		while (p->parent != nullptr)
		{
		
			p = p->parent;				//davor * 32 
			l.push_back(sf::Vector2i(p->x*32, p->y*32));
			//printf("targetx: %d, targety: %d\n", p->x , p->y);
			
		}
		
	}

	for (int i = 0; i < l.size(); i++) {
	
		//cout << "element: " << i << " mit x:" << l[i].x << " y: " << l[i].y << endl;
	}
	
	return l;
}

std::list<sf::Vector2i> AsternGetuned::feedEnemyWithWaypointsList()
{

	std::list<sf::Vector2i> l;

	if (nodeZiel != nullptr)
	{
		//printf("zielvorhanden x: %d | y: %d\n", nodeZiel->x, nodeZiel->y);;

		//nächster punkt von startpunkt
		//in while wird sich dann richtung ziel gehangelt
		sNode *p = nodeZiel;
		//l.push_front(sf::Vector2i(p->x*32 , p->y*32 ));

		while (p->parent != nullptr)
		{
			l.push_back(sf::Vector2i(p->x * 32, p->y * 32));
			p = p->parent;				//davor * 32 
			
			//printf("targetx: %d, targety: %d\n", p->x, p->y);

		}
		//system("pause");
	}
	/*
	list <sf::Vector2i>::iterator it;
	it = l.begin();
	for (; it != l.end();it++)
	{
		cout << it->x << " : " << it->y << endl;
	}
	system("pause");

	*/
	return l;
}

int AsternGetuned::getIndexOfBestNode(std::vector<sNode*>& nodes)
{
	return 0;
}

AsternGetuned::AsternGetuned()
{

}


AsternGetuned::~AsternGetuned()
{
	if (nodes) {
		delete[] nodes;
	}
}
