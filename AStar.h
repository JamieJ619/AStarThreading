#pragma once
#include "Tile.h"
#include <vector>

class AStar
{
public:
	AStar(int rowSize, int numOfTiles);
	~AStar();

	int calculateHeuristic(Tile* p_prevNode, Tile* p_currNode);
	int calculateNeighbourIndex(Tile* p_currNode, int p_id);
	std::vector<SDL_Point> search(std::vector<Tile*>*tiles, int startID, int endID);


private:
	std::vector<SDL_Point> createPath(Tile* start, Tile* goal);
	int m_neighbourTile[4];
	int m_numOfTiles;
	int m_rowSize;
	const int COST = 1;

	class NodeSearchCostComparer 
	{
	public:
		bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
			return p1.first > p2.first;
		}
	};

};

