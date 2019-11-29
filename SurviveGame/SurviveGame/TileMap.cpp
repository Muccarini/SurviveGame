#include "TileMap.h"



TileMap::TileMap()
{
	this->grid_size_f = 64.f;
	this->max_size.x = 20;
	this->max_size.y = 20;

	if(!tileset.loadFromFile("Sources/tileSheet/tilesheet.png"))
	{//THROW
		throw std::runtime_error("il file errore");
	}
	tileset.loadFromFile("Sources/tileSheet/tilesheet.png");
	
	std::ifstream openfile("Sources/Mappa.txt");
		//devo leggere il file e in base al numero trovato mettere un tile diverso 
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

						int wall_counter = 0;
						if (tile_type == 9) 
						{
							wall.setPosition(x * grid_size_f, y * grid_size_f);
							wall.setSize(sf::Vector2f(grid_size_f, grid_size_f));

							walls.push_back(wall);
							wall_counter++;
						}

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

std::vector<sf::FloatRect> TileMap::getWalls()
{
	std::vector<sf::FloatRect> wall_block;

	for (int i = 0 ; i!=walls.size() ; i++)
	{
		wall_block.push_back(walls[i].getGlobalBounds());
	}

	return wall_block;
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream openfile("Sources/Mappa.txt");
		
}


void TileMap::render(std::shared_ptr<sf::RenderTarget> target)
{

	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			y->render(target);

		}
	}
}
