#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Observer.h"
#include "PauseMenu.h"
#include "RoundManager.h"
#include "Achievement.h"
#include "Hud.h"
#include "TileMap.h"
#include "TextureHolder.h"
#include "Enemy.h"
#include "PlayerT.h"
#include "Boss.h"
#include "Pet.h"
#include "Boost.h"

#include <vector>

class GameLogic : public State
{
public:
    GameLogic();
	virtual ~GameLogic();


private:
	void update(sf::Time deltaTime);
	void render();

	void updateState();

	void updatePlayer();
	void updateEnemies();
	void updateBoss();
	void updatePet();
	void updateBoost();

	void updateGameView(sf::Time deltaTime);
	void updateEntityData(sf::Time deltaTime);
	void updateHud();

	void renderEnemies();
	void renderPlayer();
	void renderBoss();
	void renderPet();
	void renderBoost();
	void renderAchievement();

	void entitiesInit();
	void gameViewInit();
	void textureInit();
	void varInit();
	void entitydataInit();

	TileMap tile_map;
	sf::View game_view;
	Hud hud;

	RoundManager round;
	Achievement * achievement;

	std::shared_ptr<TextureHolder> textures;

    std::vector<std::shared_ptr<Character>> * enemies;
	std::shared_ptr<Character> player;
	std::shared_ptr<Character> boss;

	std::shared_ptr<Character> pet;
	std::vector<std::shared_ptr<Entity>> boost;

	std::shared_ptr<EntityData> entitydata;
	std::shared_ptr<BoostPos> boost_pos;

	const int max_enemies = 1;
	int enemies_alive;
	bool boss_alive;
	bool pet_alive;

	const float game_view_speed = 4.5f;
	sf::Clock boost_time;
	sf::Time rand_time;

};