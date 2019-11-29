#include "Button.h"



Button::Button()
{
}


Button::~Button()
{
}

void Button::setText(const std::string path, const std::string string, sf::Color color, const float character_size, const sf::Vector2f pos)
{
	this->font.loadFromFile(path);
	this->text.setFont(this->font);
	this->text.setString(string);
	this->text.setFillColor(color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(pos);

	right_scale.x = this->text.getScale().x, 
    right_scale.y = this->text.getScale().y;
	right_color   = this->text.getFillColor();
}

void Button::setBox(const sf::Vector2f size, const sf::Color outline_color, const float thickness, const sf::Color fill_color, const sf::Vector2f pos)
{
	this->box.setSize(size);
	this->box.setOutlineColor(outline_color);
	this->box.setOutlineThickness(thickness);
	this->box.setFillColor(fill_color);
	this->box.setPosition(pos);
}

bool Button::isHover(const sf::Vector2f mouse_pos_view)
{
	if (box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_view)))
		return true;
	else
		return false;
}

bool Button::isActive(const sf::Vector2f mouse_pos_view)
{
	if (isHover(mouse_pos_view) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	else
		return false;
}

void Button::buttonAnimation()  //TODO FIX IT!
{
	if (right_color == this->text.getFillColor() || right_scale == this->text.getScale())
	{
		text.setScale(text.getScale().x * 1.1, text.getScale().y * 1.1);
		text.setFillColor(sf::Color::White);
	}
}

void Button::setStandard()
{
	text.setScale(right_scale);
	text.setFillColor(right_color);
}


void Button::draw(std::shared_ptr<sf::RenderWindow> target)
{
	target->draw(this->text);
	//target->draw(this->box);
}
