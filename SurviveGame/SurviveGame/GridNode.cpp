#include "GridNode.h"

GridNode::GridNode(int width, int height) : width(width), height(height)
{
	DIRS = { GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1} };
}

void GridNode::initGrid(std::vector<GridLocation> obstacles)
{
	this->grid.resize(this->height, std::vector<GridLocation>());
	int k = 0;
	for (auto i = 0; i < grid.size(); i++)
	{
		this->grid[i].resize(this->width);
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			GridLocation node;
			node.x = j;
			node.y = i;
			if (obstacles[k].x == j && obstacles[k].y == i)
			{
				node.walkable = false;
				k++;
			}
			else node.walkable = true;
			this->grid[i][j] = node;
		}
	}
}

std::vector<std::vector<GridLocation>> GridNode::getGrid()
{
	return this->grid;
}

std::vector<GridLocation> GridNode::neighbors(GridLocation id) const
{
	std::vector<GridLocation> results;

	for (GridLocation dir : DIRS) {
		if (this->grid[id.y][id.x].walkable)
		{
			GridLocation next{ id.x + dir.x, id.y + dir.y };
			if (in_bounds(next))
			{
				results.push_back(next);
			}
		}
	}

	//if ((id.x + id.y) % 2 == 0) {
	//	// aesthetic improvement on square grids
	//	std::reverse(results.begin(), results.end());
	//}

	return results;
}

int GridNode::cost(GridLocation start, GridLocation goal)
{
	return abs(start.x - goal.x) + abs(start.y - goal.y);
}

void GridNode::setGrid(std::vector<std::vector<GridLocation>> grid)
{
	this->grid = grid;
}

bool GridNode::in_bounds(GridLocation id) const
{
	return 0 <= id.x && id.x < width
		&& 0 <= id.y && id.y < height;
}

