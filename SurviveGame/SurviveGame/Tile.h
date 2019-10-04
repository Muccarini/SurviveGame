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
	Tile(float x, float y, float grideSizeF);
	virtual ~Tile();

protected:
	sf::RectangleShape shape;

private:
	

public:
	void update();
	void render(sf::RenderTarget &target);

};

