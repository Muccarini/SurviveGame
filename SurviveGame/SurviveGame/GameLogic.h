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
    GameLogic();
	virtual ~GameLogic();


private:
	void update(sf::Time deltaTime);
	void render();

	void updateHud();
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
	void varInit();

	void newRound();

	TextureHolder _textures;
	TileMap tile_map;
	sf::View game_view;
	Hud hud;

	std::vector<sf::FloatRect> walls_collision;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> flying_bullets;
	Player player;

	int max_enemies;
	int enemies_alive;
	int kill_counter;

	int counter_flying_obj;
	bool loading_new_level;
	sf::Time countdown;

	float game_view_speed;


};
