#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "RoundManager.h"
#include "Hud.h"
#include "TileMap.h"
#include "TextureHolder.h"
#include "Enemy.h"
#include "PlayerT.h"
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
	void updatePlayer(const std::shared_ptr<EntityData> entitydata);
	void updateEnemies(const std::shared_ptr<EntityData> entitydata);
	void updateGameView(sf::Time deltaTime);

	void renderEnemies();
	void renderPlayer();
	/*void renderBullet();*/

	void entitiesInit();
	void gameViewInit();
	void varInit();

	TextureHolder textures;
	TileMap tile_map;
	sf::View game_view;
	Hud hud;
	RoundManager round;

	/*std::vector<std::shared_ptr<Bullet>> flying_bullets;*/

    std::vector<std::shared_ptr<Character>> * enemies;
	std::shared_ptr<Character> player;

	std::shared_ptr<EntityData> entitydata;

	int max_enemies;
	int enemies_alive;
	int kill_counter;

	int counter_flying_obj;

	float game_view_speed;

};
