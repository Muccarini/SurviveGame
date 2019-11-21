#pragma once
#include <SFML/Graphics.hpp>
#include "Gui.h"
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

	void updateEnemies(sf::Time deltaTime);
	void updatePlayer(sf::Time deltaTime);
	void updateBullets(sf::Time deltaTime);
	void updateGameView(sf::Time deltaTime);

	void renderPlayer();
	void renderBullet();
	void renderEnemies();

	void textureInit();
	void gameViewInit();
	void enemiesInit();



	sf::RenderWindow window;
	sf::Vector2f mouse_pos_view;
	std::vector<sf::FloatRect> walls_collision;

	sf::View game_view;
	float game_view_speed;
	TileMap tile_map;

	TextureHolder _textures;
	std::vector<std::shared_ptr<Enemy>> enemies;
	Player player;

	std::vector<std::shared_ptr<Bullet>> flying_bullets;
	int counter_flying_obj;

	int max_enemies;
	int enemies_alive;

	sf::Clock time;


};
