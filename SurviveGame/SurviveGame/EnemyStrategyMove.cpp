#include "EnemyStrategyMove.h"

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

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

inline double heuristic(GridLocation a, GridLocation b) 
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


EnemyStrategyMove::~EnemyStrategyMove()
{
}

void EnemyStrategyMove::move(sf::Time deltatime, sf::Sprite & _sprite, const float mov_speed)
{

}

bool EnemyStrategyMove::pathFinder(GridNode grid, GridLocation start, GridLocation goal, std::unordered_map<GridLocation, GridLocation>& came_from, std::unordered_map<GridLocation, double>& cost_so_far)
{
	
  PriorityQueue<GridLocation, double> frontier;
  frontier.put(start, 0);

  came_from[start] = start;
  cost_so_far[start] = 0;
  
  while (!frontier.empty()) {
	  GridLocation current = frontier.get();

    if (current == goal) {
      break;
    }

    for (GridLocation next : grid.neighbors(current)) {
      double new_cost = cost_so_far[current] + grid.cost(current, next);
      if (cost_so_far.find(next) == cost_so_far.end()
          || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        double priority = new_cost + heuristic(next, goal);
        frontier.put(next, priority);
        came_from[next] = current;
      }
    }
  }
}
