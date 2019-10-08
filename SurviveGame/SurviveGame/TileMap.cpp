#include "TileMap.h"



TileMap::TileMap()
{
	this->grid_size_f = 32.f;
	this->max_size.x = 60;
	this->max_size.y = 34;
	this->layers = 1;

	tileset.loadFromFile("Sources/tileSheet/tilesheet3.png");
	
	// renderizza solo mezza mappa devo capire come mai

	this->map.resize(this->max_size.x, std::vector< std::vector<Tile*> > ());
	for (int x = 0; x < this->max_size.x; x++)
	{
		for (int y = 0; y < this->max_size.y; y++)
		{
			this->map[x].resize(this->max_size.y, std::vector<Tile*> ());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
				this->map[x][y][z] = new Tile(x * this->grid_size_f, y * grid_size_f, this->grid_size_f tileset);
			}
		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::loadFromFile(const std::string file_name)
{
		
}


void TileMap::render(sf::RenderTarget & target)
{
	//draw(target, sf::RenderStates::Default);
	
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto &z : y)
			{
				z->render(target);
			}
		}
	}
}
