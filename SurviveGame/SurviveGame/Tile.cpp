#include "Tile.h"



Tile::Tile()
{
}

Tile::Tile(float x, float y, float gride_size_f)
{
	this->shape.setSize(sf::Vector2f(gride_size_f, gride_size_f));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(x, y);
}


Tile::~Tile()
{

}



void Tile::update()
{
}

void Tile::render(sf::RenderTarget & target)
{
	target.draw(this->shape);
}
