#include "AStar.h"
#include <queue>


AStar::AStar(int p_rowSize, int p_numOfTiles)
	: m_rowSize(p_rowSize),
	m_numOfTiles(p_numOfTiles)
{
	m_neighbourTile[0] = -1;
	m_neighbourTile[1] = 1;
	m_neighbourTile[2] = -m_rowSize;
	m_neighbourTile[3] = m_rowSize;
}


AStar::~AStar()
{
}

int AStar::calculateHeuristic(Tile * p_prevNode, Tile * p_currNode)
{
	int x = abs((p_currNode->getPosition().x - p_prevNode->getPosition().x) + (p_currNode->getPosition().y - p_prevNode->getPosition().y));
	return x;
}

int AStar::calculateNeighbourIndex(Tile * p_currNode, int p_id)
{
	int index = p_currNode->getID() + m_neighbourTile[p_id];

	if (p_id == 0 && index % m_rowSize == 0
		|| p_id == 1 && index % m_rowSize == m_rowSize - 1
		|| index < 0 || index > m_numOfTiles - 1)
	{
		return -1;
	}

	return index;
}

std::vector<SDL_Point> AStar::search(std::vector<Tile*>* tiles, int startID, int endID)
{
	Tile* start = tiles->at(startID);
	Tile* goal = tiles->at(endID);

	if (start != 0 && goal != 0)
	{
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, NodeSearchCostComparer> openset;
		start->setGCost(0);
		start->setFCost(calculateHeuristic(start, goal));
		start->setOpen(true);
		openset.push(std::pair<int, int>(start->getFCost(), startID));

		int previousCost = 0;

		while (openset.size() != 0)
		{
			Tile* current = tiles->at(openset.top().second);
			openset.pop();
			if (current == goal)
			{
				return createPath(goal, start);
			}
			current->setOpen(false);
			current->setClose(true);

			for (int i = 0; i < 4; i++)
			{
				int neighbourIndex = calculateNeighbourIndex(current, i);

				Tile* neighbour;
				if (neighbourIndex == -1)
				{
					neighbour = 0;
				}
				else
				{
					neighbour = tiles->at(neighbourIndex);
				}

				if (neighbour == 0 || neighbour->getClose()
					|| neighbour == current->getPrevTile()
					|| neighbour->getIsWall() == true)
				{
					continue;
				}
				int tenativeGCost = current->getGCost() + COST;
				if (tenativeGCost <= neighbour->getGCost())
				{
					neighbour->setPrevTile(current);
					neighbour->setGCost(tenativeGCost);
					neighbour->setFCost(neighbour->getGCost() + calculateHeuristic(neighbour, goal));
				}

				if (neighbour->getOpen() == false)
				{
					// TILE CHECKED
					neighbour->setTileTypeID(3);
					neighbour->setOpen(true);
					openset.push(std::pair<int, int>(neighbour->getFCost(), neighbourIndex));
				}
				previousCost = tenativeGCost;
			}
			//if (openset.size() == 0)
			//	//std::cout << "Couldn't find path." << std::endl;
		}
	}
	return std::vector<SDL_Point>();
}

std::vector<SDL_Point> AStar::createPath(Tile * goal, Tile * start)
{
	std::vector<SDL_Point> path;
	for (Tile* previous = goal; previous->getPrevTile() != 0; previous = previous->getPrevTile())
	{
		previous->setTileTypeID(2);
		path.push_back(previous->getPosition());
	}
	path.push_back(start->getPosition());
	
	return path;
}
