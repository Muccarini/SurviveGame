 #include "Tile.h"



Tile::Tile()
{
}

Tile::Tile(float x, float y, float gride_size_f, sf::VertexArray texture_area, sf::Texture txt)
{
	//	devo fare il draw di tile_vertex quindi devo per forza averlo in tileMap e utilizzare la funzione
	//	draw su quello un'unica volta e non ogni volta che disegno un tile ( dovrebbe pure pesare meno 
	//	a livello di operazioni in memoria del computer)

	//rect_shape.width = gride_size_f;
	//rect_shape.height = gride_size_f;
	//rect_shape.top = 20;//textures.getSize().x % rect_shape.width;
	//rect_shape.left = 32;//textures.getSize().y % rect_shape.height;

	this->texture_vertex = texture_area;
	this->textures = txt;

	this->shape.setSize(sf::Vector2f(gride_size_f, gride_size_f));
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineThickness(0.5f);
	this->shape.setOutlineColor(sf::Color::Red);
	this->shape.setPosition(x, y);

	//sprite.setTexture(textures);
	//sprite.setTextureRect(rect_shape);
	//sprite.setPosition(x, y);

}


Tile::~Tile()
{

}



void Tile::update()
{
}



void Tile::render(sf::RenderTarget & target)
{
	//target.draw(this->shape);
	target.draw(shape);
}
