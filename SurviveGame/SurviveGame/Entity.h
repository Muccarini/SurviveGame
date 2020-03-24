#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"

namespace BulletOwner
{
	enum Owner { Player, Boss, Pet };
}

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void render(std::shared_ptr<sf::RenderWindow> target);

	sf::Vector2f getPosition();
	void         setPosition(sf::Vector2f pos);

	sf::RectangleShape getHitBox();

	GridLocation getGridPos();
	void         setGridPosition(float tilesize);

	void  setMoveSpeed(float mov_speed);
	float getMovSpeed();
	void  setMoveSpeedDef(float mov_speed_def);
	float getMovSpeedDef();

protected:
	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *vec);

	sf::Sprite sprite;
	sf::RectangleShape hit_box;

	GridLocation gridpos;

	float mov_speed;
	float mov_speed_default;
};
