#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

class Character;

class EntityData
{
public:
	EntityData() {};

	sf::Time deltaTime;
	sf::Vector2f mouse_pos_view; //da provare senza puntatore come deltaTime quest'ultimo da mettere come data member in state.h
	std::vector<sf::FloatRect> walls;
    std::vector<std::shared_ptr<Character>> * enemies;
	std::shared_ptr<Character> target;
};


class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(std::shared_ptr<EntityData> entitydata) = 0;
	void render(std::shared_ptr<sf::RenderWindow> target);

	bool isAlive();
	void setAlive(bool boolean);

	bool isCollideWall();
	bool isCollideEnemy();

	sf::Vector2f getPosition();
	sf::RectangleShape getHitBox();

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
	int mov_speed_max;
};
