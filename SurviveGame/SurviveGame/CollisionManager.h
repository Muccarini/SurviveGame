#ifndef COLLSIONMANAGER_H
#define COLLSIONMANAGER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Entity;
class Character;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	sf::Vector2f isCollideWithWalls(const std::shared_ptr<Entity> entity, std::vector<sf::FloatRect> walls);                  //IL CALCOLO TOTALE DEL DIR SPETTA AL'ENTITY CHE USA IL COLLISION MANAGER E FARCI IL MOVE SOPRA
	sf::Vector2f isCollideWith(const std::shared_ptr<Entity> entity1, const std::shared_ptr<Character> charcters);
	sf::Vector2f isCollideWith(const std::shared_ptr<Entity> entity, const std::vector<std::shared_ptr<Character>> charcter);

private:
	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2);

	sf::Vector2f out_mtv;
};
#endif

