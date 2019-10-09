 #include "Tile.h"

Tile::Tile(float x, float y, float gride_size_f, sf::Texture& txt, int t_type) : textures(txt)
{

	rect_shape.width = gride_size_f;
	rect_shape.height = gride_size_f;
	rect_shape.top = 0;
	rect_shape.left = 0;

	this->textures = txt;

	this->shape.setSize(sf::Vector2f(gride_size_f, gride_size_f));
	this->shape.setPosition(x, y);

	this->shape.setTexture(&txt);
	sf::Vector2u pos_in_texture;
	
	for (int i = 0; i < t_type; i++)
	{
		if ((t_type * gride_size_f) < txt.getSize().x)
		{
			pos_in_texture = sf::Vector2u(t_type * gride_size_f, i);
		}
		else t_type -= (txt.getSize().x / static_cast <unsigned>(gride_size_f));
	}


	this->shape.setTextureRect(sf::IntRect(pos_in_texture.x, pos_in_texture.y, 32, 32));
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
