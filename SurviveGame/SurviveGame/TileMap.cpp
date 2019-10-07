#include "TileMap.h"



TileMap::TileMap()
{
	this->grid_size_f = 32.f;
	this->grid_size_u = static_cast<unsigned>(this->grid_size_f);
	this->max_size.x = 60;
	this->max_size.y = 34;
	this->layers = 1;

	tileset.loadFromFile("Sources/graphics-vertex-array-tilemap-tileset.png");
	sf::VertexArray tile_vertex_(sf::Quads);

	this->tile_vertex = tile_vertex_;
	
	// renderizza solo mezza mappa devo capire come mai
	/*for (size_t x = 0; x != this->max_size.x; x++)
	{
		this->map.push_back(std::vector <std::vector<Tile> >());

		for (size_t y = 0; y < this->max_size.x; y++)
		{
			this->map[x].resize(this->max_size.y);
			this->map[x].push_back(std::vector<Tile> ());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				tile_vertex[0].texCoords = sf::Vector2f(0.f, 0.f);
				tile_vertex[1].texCoords = sf::Vector2f(32.f, 0.f);
				tile_vertex[2].texCoords = sf::Vector2f(32.f, 32.f);
				tile_vertex[3].texCoords = sf::Vector2f(0.f, 32.f);

				tile_vertex[0].position = sf::Vector2f(x * grid_size_f, y * grid_size_f);
				tile_vertex[1].position = sf::Vector2f((x + 1) * grid_size_f, y * grid_size_f);
				tile_vertex[2].position = sf::Vector2f((x + 1) * grid_size_f, (y + 1) * grid_size_f);
				tile_vertex[3].position = sf::Vector2f(x * grid_size_f, (y + 1) * grid_size_f);

				this->map[x][y].push_back(Tile
						(x * this->grid_size_f, y * this->grid_size_f, this->grid_size_f, tile_vertex, tileset));
			}
		}
	}*/
	map.resize(max_size.x * max_size.y);
	tile_vertex.resize(max_size.x * max_size.y * 4);

	for (size_t x = 0; x < max_size.x; x++)
	{
		for (size_t y = 0; y < max_size.y; y++)
		{
			sf::Vertex* quad = &tile_vertex[(x + y * max_size.x) * 4];
			quad[0].texCoords = sf::Vector2f(0.f, 0.f);
			quad[1].texCoords = sf::Vector2f(32.f, 0.f);
			quad[2].texCoords = sf::Vector2f(32.f, 32.f);
			quad[3].texCoords = sf::Vector2f(0.f, 32.f);

			quad[0].position = sf::Vector2f(x * grid_size_f, y * grid_size_f);
			quad[1].position = sf::Vector2f((x + 1) * grid_size_f, y * grid_size_f);
			quad[2].position = sf::Vector2f((x + 1) * grid_size_f, (y + 1) * grid_size_f);
			quad[3].position = sf::Vector2f(x * grid_size_f, (y + 1) * grid_size_f);

			this->map.push_back(Tile
			(x * this->grid_size_f, y * this->grid_size_f, this->grid_size_f, tile_vertex, tileset));
		}

	}
}


TileMap::~TileMap()
{
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// applica la trasformazione
	states.transform *= getTransform();

	// applica la texture del tileset
	states.texture = &tileset;

	// disegna l'array di vertex
	target.draw(tile_vertex, states);
}


void TileMap::render(sf::RenderTarget & target)
{
	draw(target, sf::RenderStates::Default);
	
	for (auto i = map.begin(); i != map.end(); i++)
		(*i).render(target);

}
