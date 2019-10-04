#include "TileMap.h"



TileMap::TileMap()
{
	this->grid_size_f = 50.f;
	this->grid_size_u = static_cast<unsigned>(this->grid_size_f);
	this->max_size.x = 10;
	this->max_size.y = 10;
	this->layers = 5;

	for (size_t x = 0; x != this->max_size.x; x++)
	{
		this->map.push_back(std::vector <std::vector<Tile> >());

		for (size_t y = 0; y < this->max_size.x; y++)
		{
			this->map[x].resize(this->max_size.y);
			this->map[x].push_back(std::vector<Tile> ());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tile
						(x * this->grid_size_f, y * this->grid_size_f, this->grid_size_f));
			}
		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget & target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto &z : y)
			{
				z.render(target);
			}
		}
	}
}
