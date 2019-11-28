#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "RoundManager.h"
#include "Hud.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
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
	void updateBoss(sf::Time deltaTime);
	void updateGameView(sf::Time deltaTime);

	void renderPlayer();
	void renderBullet();
	void renderEnemies();
	void renderBoss();

	void textureInit();
	void gameViewInit();
	void enemiesInit();

	TextureHolder _textures;
	TileMap tile_map;
	sf::View game_view;
	Hud hud;
	RoundManager round;

	std::vector<sf::FloatRect> walls_collision;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> flying_bullets;
	Player player;
	Boss boss;

	int max_enemies;
	int enemies_alive;
	int kill_counter;

	int counter_flying_obj;

	float game_view_speed;


};
