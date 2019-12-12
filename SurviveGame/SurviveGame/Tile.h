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
	Tile(float x, float y, float grideSizeF, sf::Texture& txt, int t_type);

	virtual ~Tile();

protected:
	sf::RectangleShape shape;
	sf::Texture& textures;

private: 
	

public:

	int type_tile;
	sf::IntRect rect_shape;
	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);

};

