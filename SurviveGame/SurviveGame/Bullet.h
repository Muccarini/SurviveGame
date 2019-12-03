#pragma once
#include "Character.h"

class Bullet
{
public:
	Bullet(sf::Texture texture);
	Bullet();
	virtual ~Bullet();

	void update(std::shared_ptr<EntityData> entitydata);
	void render(std::shared_ptr<sf::RenderWindow> target);
	void setDir(sf::Vector2f owner_pos, sf::Vector2f target);

	bool isCollideWall();
	bool isCollideEnemy();

private:

	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv);

	void rotate(sf::Vector2f vec_dir);

	void initSprite();
	void initHitBox();

	void collisionWalls(std::vector<sf::FloatRect> walls);
	void collisionEnemies(std::vector<std::shared_ptr<Character>> enemies);

	sf::Vector2f player_pos;
	sf::Vector2f dir;

	bool collideEnemy;
	bool collideWall;

	sf::Texture texture;
	int mov_speed;
	sf::Sprite sprite;
	sf::RectangleShape hit_box;
	sf::Vector2f out_mtv;
};

