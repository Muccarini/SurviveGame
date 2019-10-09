#include "TileMap.h"



TileMap::TileMap()
{
	this->grid_size_f = 64.f;
	this->max_size.x = 60;
	this->max_size.y = 34;
	this->layers = 1;

	tileset.loadFromFile("Sources/tileSheet/tilesheet3.png");
	
	std::ifstream openfile("Sources/Mappa.txt");
		//devo leggere il file e in base al numero trovato mettere un tile diverso 
	int type_map[60][34];
	if(openfile.is_open())
	{
		while (!openfile.eof())
		{
			this->map.resize(this->max_size.y, std::vector<Tile*> ());
			int y = 0;
			while (y < this->max_size.y)
			{
				int x = 0;
				while (x < this->max_size.x)
				{
					this->map[y].resize(this->max_size.x, NULL);

					std::string str, value;
					std::getline(openfile, str);
					std::stringstream stream(str);

					while (std::getline(stream, value, ' ') && openfile.peek() != '\n')
					{
						std::string t_type = value.substr(0, value.find(','));
						tile_type = atoi(t_type.c_str());
						
						this->map[y][x] = new Tile(x * this->grid_size_f, y * grid_size_f, this->grid_size_f, tileset, tile_type);
						x++;
					}
				}
				y++;
			}

		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream openfile("Sources/Mappa.txt");
		
}


void TileMap::render(sf::RenderTarget & target)
{
	//draw(target, sf::RenderStates::Default);

	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			y->render(target);

		}
	}
}
