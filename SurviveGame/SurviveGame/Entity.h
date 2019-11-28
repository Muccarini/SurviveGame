#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(const sf::Time deltaTime) = 0;
	virtual void render(std::shared_ptr<sf::RenderWindow> target) = 0;

	bool isAlive();
	void setAlive(bool boolean);

	sf::Vector2f getPosition();

protected:
	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv);

	sf::Sprite sprite;
	sf::Vector2f texture;
	sf::RectangleShape hit_box;
	sf::Vector2f out_mtv;

	bool alive;
};

