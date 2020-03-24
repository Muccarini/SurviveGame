#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button

{
public:
	Button();
	~Button();

	void setText(const std::string& path, const std::string& string, sf::Color color, float character_size, sf::Vector2f pos);
	void setBox(sf::Vector2f size, sf::Color color, float thickness, sf::Color fill_color, sf::Vector2f pos, sf::Texture* txt = NULL);

	sf::RectangleShape getBox();
	void draw(std::shared_ptr<sf::RenderWindow> target);

	bool isHover(sf::Vector2f mouse_pos_view);
	bool isActive(sf::Vector2f mouse_pos_view);

	void buttonAnimation();
	void setStandard();

private:
	sf::Font font;
	sf::Text text;

	sf::RectangleShape box;

	sf::Vector2f right_scale;
	sf::Color right_color;
};

