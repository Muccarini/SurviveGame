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

	TextureHolder _textures;
	std::vector<std::shared_ptr<Enemy>> enemies;
	Player player;

	std::vector<std::shared_ptr<Bullet>> flying_bullets;
	int counter_flying_obj;

	int n_max_enemies;
	int n_enemies_alive;

	sf::Clock time;


};
