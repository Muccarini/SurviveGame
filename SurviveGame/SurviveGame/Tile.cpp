 #include "Tile.h"

Tile::Tile(float x, float y, float gride_size_f, sf::Texture& txt) : textures(txt)
{

	rect_shape.width = gride_size_f;
	rect_shape.height = gride_size_f;
	rect_shape.top = 0;
	rect_shape.left = 0;

	this->textures = txt;

	this->shape.setSize(sf::Vector2f(gride_size_f, gride_size_f));
	this->shape.setPosition(x, y);

	this->shape.setTextureRect(sf::IntRect(0,0,32,32));
	this->shape.setTexture(&txt);
}


Tile::~Tile()
{

}



void Tile::update()
{
}



void Tile::render(sf::RenderTarget & target)
{
	target.draw(shape);
}
