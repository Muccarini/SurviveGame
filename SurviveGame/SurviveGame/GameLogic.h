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
#include "GridNode.h"
#include "StrategyFight.h"
#include <vector>

class GameLogic : public State
{
public:
    GameLogic(Textures::ID id, StrategyFight* stf);
	virtual ~GameLogic();


private:
	void update(sf::Time deltaTime);
	void render();

	void updateState();

	void updateAchievement(sf::Time deltaTim);

	void updatePlayer(sf::Time deltaTime);
	void updateRound();

	void spawnZombies(sf::Time deltaTime);
	void updateZombie(sf::Time deltaTime, int i);

	void spawnBoss(sf::Time deltaTime);
	void updateBoss(sf::Time deltaTime);

	void spawnPet();
	void updatePet(sf::Time deltaTime);

	void spawnBullet(BulletOwner::Owner owner);
	void updateBullet(sf::Time deltaTime);

	void updateBoost();

	void updateGameView(sf::Time deltaTime);
	void updateHud();

	void renderEnemies();
	void renderPlayer();
	void renderBoss();
	void renderPet();
	void renderBullets();
	void renderBoosts();
	void renderAchievement();

	void entitiesInit(Textures::ID id, StrategyFight* stf);
	void gameViewInit();
	void textureInit();
	void varInit();

	TileMap tile_map;
	GridNode grid;
	sf::View game_view;
	Hud hud;
	RoundManager round;
	Achievement * achievement;

	std::shared_ptr<TextureHolder> textures;

    std::vector<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<PlayerT> player;
	std::shared_ptr<Boss> boss;

	std::shared_ptr<Pet> pet;
	std::vector<std::shared_ptr<Boost>> boosts;
	std::vector<std::shared_ptr<Bullet>> bullets;

	std::shared_ptr<BoostPos> boost_pos;

	const int max_enemies = 5;
	int enemies_alive;
	bool boss_alive;
	bool pet_alive;

	int kill_counter;

	const float game_view_speed = 4.5f;
	sf::Clock boost_time;
	sf::Time rand_time;

};