#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include <vector>
#include "Box2D/Box2D.h"



class Game
{
public:
	explicit Game();
	
	void run();

private:
	void processEvents();

	void update(sf::Time deltaTime);
	void render();



	sf::RenderWindow window;
	sf::Vector2f mouse_pos_view;
	sf::FloatRect collision;

	sf::View game_view;
	TileMap tile_map;

	std::vector<std::unique_ptr<Enemy>> enemies;
	Player player;


};
