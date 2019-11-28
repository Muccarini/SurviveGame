#pragma once
#include <SFML/Graphics.hpp>

struct EntityData
{
	sf::Time deltaTime;
	sf::Vector2f mouse_pos_view;
	std::vector<sf::FloatRect> walls;
	std::vector<std::shared_ptr<Entity>> enemies;
	std::shared_ptr<Entity> target;
};

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(std::shared_ptr<EntityData> entitydata) = 0;
	/*virtual void render(std::shared_ptr<sf::RenderWindow> target) = 0;*/

	bool isAlive();
	void setAlive(bool boolean);

	sf::Vector2f getPosition();
	sf::RectangleShape getHitBox();

protected:
	std::shared_ptr<EntityData> entitydata;

	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv);

	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape hit_box;
	sf::Vector2f out_mtv;

	bool alive;
};

