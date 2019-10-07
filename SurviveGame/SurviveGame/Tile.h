#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


class Tile
{

public:
	Tile();
	Tile(float x, float y, float grideSizeF, sf::VertexArray texture_area, sf::Texture txt);
	virtual ~Tile();

protected:
	sf::RectangleShape shape;
	sf::Texture textures;
	sf::Sprite sprite;
	sf::IntRect rect_shape;
	sf::VertexArray texture_vertex;
private: 
	

public:
	void update();
	void render(sf::RenderTarget &target);

};

