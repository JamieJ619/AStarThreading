#pragma once
#include "Tile.h"
#include <vector>
#include <map>

class AStar
{
	struct Data
	{
		bool m_open;
		bool m_close;
		Tile * m_previous;
		int m_fCost;
		int m_gCost;
		Data(bool open = false, bool close = false, int fCost = std::numeric_limits<int>::max(),  int gCost = std::numeric_limits<int>::max(), Tile * previous = 0)
		: m_open(open)
		, m_close(close)
		, m_previous(previous)
		, m_fCost(fCost)
		, m_gCost(gCost)
		{
			
		}
	};
public:
	AStar(int rowSize, int numOfTiles);
	~AStar();

	int calculateHeuristic(Tile* p_prevNode, Tile* p_currNode);
	int calculateNeighbourIndex(Tile* p_currNode, int p_id);
	std::vector<SDL_Point> search(std::vector<Tile*>*tiles, int startID, int endID);


private:
	std::vector<SDL_Point> createPath(Tile* start, Tile* goal, std::map<Tile*, Data> * tileData);
	int m_neighbourTile[4];
	int m_numOfTiles;
	int m_rowSize;
	const int COST = 25;

	class NodeSearchCostComparer 
	{
	public:
		bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
			return p1.first > p2.first;
		}
	};

};

