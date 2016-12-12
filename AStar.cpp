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

int AStar::calculateHeuristic(Tile * p_goalTile, Tile * p_currTile)
{

	int xDiff = std::max(p_goalTile->getPosition().x - p_currTile->getPosition().x, p_currTile->getPosition().x - p_goalTile->getPosition().x);
	int yDiff = std::max(p_goalTile->getPosition().y - p_currTile->getPosition().y, p_currTile->getPosition().y - p_goalTile->getPosition().y);

	return xDiff + yDiff;
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
	std::map<Tile*, Data> m_tileData;


	Tile* start = tiles->at(startID);
	Tile* goal = tiles->at(endID);

	if (start != 0 && goal != 0)
	{
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, NodeSearchCostComparer> openset;
		m_tileData[start].m_gCost = 0;
		m_tileData[start].m_fCost = calculateHeuristic(start, goal);
		m_tileData[start].m_open = true;

		openset.push(std::pair<int, int>(m_tileData[start].m_fCost, startID));

		int previousCost = 0;

		while (openset.size() != 0)
		{
			Tile* current = tiles->at(openset.top().second);
			openset.pop();
			if (current == goal)
			{
				return createPath(goal, start, &m_tileData);
			}
			m_tileData[current].m_open = false;
			m_tileData[current].m_close = true;

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

				if (neighbour == 0 || m_tileData[neighbour].m_close
					|| neighbour == m_tileData[current].m_previous
					|| neighbour->getIsWall())
				{
					continue;
				}
				int tenativeGCost = m_tileData[current].m_gCost + COST;
				if (tenativeGCost <= m_tileData[neighbour].m_gCost)
				{
					m_tileData[neighbour].m_previous = current;
					m_tileData[neighbour].m_gCost = tenativeGCost;
					m_tileData[neighbour].m_fCost = (m_tileData[neighbour].m_gCost / 2) + calculateHeuristic(neighbour, goal);
				}

				if (m_tileData[neighbour].m_open == false)
				{
					// TILE CHECKED
					neighbour->setTileTypeID(3);
					m_tileData[neighbour].m_open = true;
					openset.push(std::pair<int, int>(m_tileData[neighbour].m_fCost, neighbourIndex));
				}
				previousCost = tenativeGCost;
			}
		}
	}
	return std::vector<SDL_Point>();
}

std::vector<SDL_Point> AStar::createPath(Tile * goal, Tile * start, std::map<Tile*, Data> * tileData)
{
	std::vector<SDL_Point> path;
	for (Tile* previous = goal; previous != 0; previous = tileData->at(previous).m_previous)
	{
		previous->setTileTypeID(2);
		path.push_back(previous->getPosition());
	}
	path.push_back(start->getPosition());
	
	return path;
}
