#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Character;

namespace BulletOwner
{
	enum Owner { Allied, Enemy };
}

class EntityData
{
public:
	EntityData() {};

	sf::Time deltaTime;
	sf::Vector2f mouse_pos_view;
	std::vector<sf::FloatRect> walls;
    std::vector<std::shared_ptr<Character>> * enemies;
	std::shared_ptr<Character> player;
	std::shared_ptr<Character> boss;
};

class BoostPos {

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

	virtual void update(std::shared_ptr<EntityData> entitydata) = 0;
	void render(std::shared_ptr<sf::RenderWindow> target);

	bool isAlive();

	bool isCollideWall();
	bool isCollideEnemy();

	sf::Vector2f getPosition();
	sf::RectangleShape getHitBox();
	bool getAlive();

protected:

	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv);

	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape hit_box;
	sf::Vector2f out_mtv;

	bool alive;

	bool collideWall;
	bool collideEnemy;

	int mov_speed;
	int mov_speed_default;
};
