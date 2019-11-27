#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Hud.h"
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"
#include "Bullet.h"
#include <vector>



class GameLogic :
	public State
{
public:
	explicit GameLogic();
	virtual ~GameLogic();


private:
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


	std::vector<sf::FloatRect> walls_collision;

	sf::View game_view;
	Hud hud;
	int kill_counter;

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
