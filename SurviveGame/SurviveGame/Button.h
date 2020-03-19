#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button

{
public:
	Button();
	~Button();

	void setText(const std::string path, const std::string string, const sf::Color color, const float size, const sf::Vector2f pos);
	void setBox(const sf::Vector2f size, const sf::Color color, const float thickness, const sf::Color fill_color, const sf::Vector2f pos, sf::Texture* txt = NULL);

	sf::RectangleShape getBox();
	void draw(std::shared_ptr<sf::RenderWindow> target);

	bool isHover(const sf::Vector2f mouse_pos_view);
	bool isActive(const sf::Vector2f mouse_pos_view);

	void buttonAnimation();
	void setStandard();

private:
	sf::Font font;
	sf::Text text;

	sf::RectangleShape box;

	sf::Vector2f right_scale;
	sf::Color right_color;
};

