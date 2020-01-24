#pragma once
#include <queue>
#include <unordered_set>
#include <array>

struct GridLocation
{
	int x, y;
	bool walkable = true;

	inline bool operator==()
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
	
protected:

	std::vector< std::vector<GridLocation> > grid;

	std::array<GridLocation, 4> DIRS;

	int width, height;

	bool in_bounds(GridLocation id) const;
	
};