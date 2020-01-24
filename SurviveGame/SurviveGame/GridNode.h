#pragma once
#include <queue>
#include <unordered_map>
#include <array>

struct GridLocation
{
	int x, y;
	bool walkable = true;

	inline bool isEqual(const GridLocation& second)
	{
		return (this->x == second.x && this->y == second.y && this->walkable == second.walkable);
	}

	inline bool operator<(const GridLocation& sc)
	{
	}
};

namespace std {
	/* implement hash function so we can put GridLocation into an unordered_set */
	template <> struct hash<GridLocation> {
		typedef GridLocation argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const GridLocation& id) const noexcept {
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}

class GridNode
{
public:
	GridNode(int width, int height);
	virtual ~GridNode() {};

	void initGrid(std::vector<GridLocation> obstacles);

	std::vector< std::vector<GridLocation> > getGrid();

	std::vector<GridLocation> neighbors(GridLocation id) const;

	int cost(GridLocation start, GridLocation goal);
	
protected:

	std::vector< std::vector<GridLocation> > grid;

	std::array<GridLocation, 4> DIRS;

	int width, height;

	bool in_bounds(GridLocation id) const;
	
};