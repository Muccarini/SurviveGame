#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

struct Node 
{
	int x;
	int y;
	float G;
	float H;
	float F;
	std::shared_ptr<Node> parent;
};

class Tile
{

public:
	Tile(float x, float y, float grideSizeF, sf::Texture& txt, int t_type);

	virtual ~Tile();

protected:

	sf::FloatRect rect_shape;
	sf::Texture& textures;

private: 
	

public:

	sf::RectangleShape shape;
	int type_tile;
	void render(std::shared_ptr<sf::RenderTarget> target);

};

