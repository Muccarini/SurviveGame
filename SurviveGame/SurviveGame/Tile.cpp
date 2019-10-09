 #include "Tile.h"

Tile::Tile(float x, float y, float gride_size_f, sf::Texture& txt, int t_type) : textures(txt)
{
	if(t_type == 3)
	{
		shape.setOutlineColor(sf::Color::Magenta);
		shape.setOutlineThickness(3.f);
	}

	rect_shape.width = gride_size_f;
	rect_shape.height = gride_size_f;
	rect_shape.top = 0;
	rect_shape.left = 0;

	this->textures = txt;

	this->shape.setSize(sf::Vector2f(gride_size_f, gride_size_f));
	this->shape.setPosition(x, y);

	this->shape.setTexture(&txt);
	sf::Vector2u pos_in_texture;
	
	int n = (txt.getSize().x / static_cast <unsigned>(gride_size_f));
	int i=0;
	int j = t_type % n;

	while(t_type > n)
	{
		t_type -= (txt.getSize().x / static_cast <unsigned>(gride_size_f));
		i++;
	}

	if (i >= 1)
		j -= 1;

	pos_in_texture = sf::Vector2u(j * gride_size_f, i * gride_size_f);
	this->shape.setTextureRect(sf::IntRect(pos_in_texture.x, pos_in_texture.y, 64, 64));
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
