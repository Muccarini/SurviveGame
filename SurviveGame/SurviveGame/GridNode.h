#pragma once
#include <queue>
#include <unordered_map>
#include <array>
#include <iostream>
struct GridLocation
{
	int x, y;
	bool walkable = true;

	inline bool isEqual(const GridLocation& second)
	{
		return (this->x == second.x && this->y == second.y && this->walkable == second.walkable);
	}

	inline bool operator==(const GridLocation& second) const
	{
		return (this->x == second.x && this->y == second.y);
	}

	inline bool operator!=(const GridLocation& second) const
	{
		return !operator==(second);
	}
	bool operator < (const GridLocation& b) const 
	{
		return std::tie(this->x, this->y) < std::tie(b.x, b.y);
	}

	inline bool operator>(const GridLocation& sc) const
	{
		return !operator<(sc);
	}
};

template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get()
	{
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

template<typename Location>
std::vector<Location> reconstruct_path(
	Location start, Location goal,
	std::unordered_map<Location, Location> came_from
) {
	std::vector<Location> path;
	Location current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}

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

	void setGrid(std::vector< std::vector<GridLocation> > grid);
protected:

	std::vector< std::vector<GridLocation> > grid;

	std::array<GridLocation, 4> DIRS;

	int width, height;

	bool in_bounds(GridLocation id) const;
	
};