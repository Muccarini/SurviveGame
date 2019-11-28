#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "RoundManager.h"
#include "Hud.h"
#include "TileMap.h"
#include "Bullet.h"
#include "PlayerT.h"
#include "Enemy.h"
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

	void updateCharacter(sf::Time deltaTime);
	void renderCharacter();

	void updateGameView(sf::Time deltaTime);

	void renderBullet();

	void characterinit();
	void textureInit();
	void gameViewInit();
	void enemiesInit();

	TextureHolder _textures;
	TileMap tile_map;
	sf::View game_view;
	Hud hud;
	RoundManager round;

	std::vector<std::shared_ptr<Bullet>> flying_bullets;

	std::vector<std::shared_ptr<Character>> entities;
	std::shared_ptr<EntityData> entitydata;

	int max_enemies;
	int enemies_alive;
	int kill_counter;

	int counter_flying_obj;

	float game_view_speed;

};
