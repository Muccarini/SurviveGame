#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "CollisionManager.h"
#include "TileMap.h"

class Character;
class CollisionManager;

namespace BulletOwner
{
	enum Owner { Player, Boss, Pet };
}

struct BoostPos {

public:
	BoostPos() { pos1_1 = false; pos1_2 = false; pos2_1 = false; pos2_2 = false; };

	bool pos1_1;
	bool pos1_2;
	bool pos2_1;
	bool pos2_2;
};

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void render(std::shared_ptr<sf::RenderWindow> target);

	bool isAlive();
	void setAlive(bool boolean);

	bool isCollide(); 

	sf::Vector2f getPosition();
	void         setPosition(const sf::Vector2f & pos);

	sf::RectangleShape getHitBox();

	GridLocation getGridPos();
	void         setGridPosition(float tilesize);

protected:

	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *vec);

	sf::Sprite sprite;
	sf::RectangleShape hit_box;

	sf::Vector2f vec;

	bool alive;

	bool collide;

	GridLocation gridpos;

	float mov_speed;
	float mov_speed_default;
};
