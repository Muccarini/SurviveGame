#include "TileMap.h"
#include <sstream>


TileMap::TileMap(const int *level) : _level(level)
{

}

TileMap::~TileMap()
{
	
}

bool TileMap::load(const std::string & tileset, sf::Vector2u tileSize,
	const int * tiles, unsigned int width, unsigned int height)
{
	//load del tileset
	if (!t_tileset.loadFromFile(tileset))
		return false;
	//ridimensiona l'array per adattare le dimensioni del livello 
	t_vertex.setPrimitiveType(sf::Quads);
	t_vertex.resize(width * height * 4);

	//cicla la matrice che gli viene passata per riempire lo schermo così da riempirlo 
	//con i tiles giusti
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			//prende il tile corrente 
			int tileNumber = tiles[i + j * width];

			//trova la sua posizione nella nexture del tileset
			int tu = tileNumber % (t_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (t_tileset.getSize().x / tileSize.x);

			// prende un puntatore al quadrato del tile corrente
			sf::Vertex* quad = &t_vertex[(i + j * width) * 4];

			// definisce i 4 vertici del quadrato
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

			_tile.t_vertex = t_vertex;

			//STO CERCANDO DI CAPIRE COME SETTARE LA COLLISIONE DEI TILE 1
			//do la posizione del Tile attraverso il vertice in alto a sinistra così lo
			//posso sfruttare con la classe FloatRect
			_posMapX = quad[0].position.x;
			_posMapY = quad[0].position.y;
			_tile.posMapX = _posMapX;
			_tile.posMapY = _posMapY;
			if (tileNumber == 1)
			{
				_collision.setSize(static_cast<sf::Vector2f>(tileSize));
				_collision.setFillColor(sf::Color::Transparent);
				_collision.setOutlineColor(sf::Color::Magenta);
				_collision.setOutlineThickness(1.f);
				_collision.setPosition(sf::Vector2f(i * tileSize.x, j * tileSize.y));
				_tile.collision = _collision;
				solidTiles.push_back(_collision);
			}

			_col.left = i * tileSize.x;
			_col.top = j * tileSize.y;
			_col.width = tileSize.x;
			_col.height = tileSize.y;

			_tile._col = _col;
			_tiles.push_back(_tile);
		}
	}

	return true;
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// applica la trasformazione
	states.transform *= getTransform();

	// applica la texture del tileset
	states.texture = &t_tileset;

	// disegna l'array di vertex
	target.draw(t_vertex, states);
	int pos = 0;
	for (auto i = solidTiles.begin(); i < solidTiles.end(); i++)
	{
		target.draw(solidTiles[pos], states);
		pos++;
	}
}

sf::FloatRect TileMap::findTile(sf::Vector2f posMap, sf::FloatRect spriteDim)
{
	sf::FloatRect rightTile;

	//il problema sta nelle coordinate del giocatore e quelle degli angoli del rettangolo del 
	//tile che sono uguali solo se il player si trova nell'angolo in alto a sinistra del tile stesso
	/*for (auto i = _tiles.begin(); posMap != sf::Vector2f((*i).posMapX, (*i).posMapY)
		|| i < _tiles.end(); i++)
	{
		if (posMap.x > (*i).posMapX && posMap.x<=(*i).posMapX + (*i)._col.width)
			if(posMap.y <= (*i).posMapY && posMap.y < (*i).posMapY + (*i)._col.height)
		rightTile = (*i)._col;
	}*/
	auto i = _tiles.begin();
	while (posMap.x <= (*i).posMapX || posMap.x > (*i).posMapX + spriteDim.width &&
		posMap.y >= (*i).posMapY || posMap.y > (*i).posMapY + spriteDim.height)
	{
		rightTile = (*i)._col;
		i++;
	}

	return rightTile;
}
	