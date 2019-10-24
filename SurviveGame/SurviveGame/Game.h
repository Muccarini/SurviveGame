#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Bullet.h"
#include <vector>



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
	std::vector<sf::FloatRect> walls_collision;

	sf::View game_view;
	TileMap tile_map;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> p_bullets;

	Player player;
	bool p_shooting;
	int ammo;


};
