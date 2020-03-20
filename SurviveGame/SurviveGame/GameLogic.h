#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Observer.h"
#include "PauseMenu.h"
#include "RoundManager.h"
#include "BoostManager.h"
#include "CollisionManager.h"
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
    GameLogic(Textures::ID id, std::shared_ptr<StrategyFight> stf);
	virtual ~GameLogic();

private:

	virtual void update(const sf::Time& delta_time);
	virtual void render();

	void updateState();

	void updateAchievement(const sf::Time& delta_time);

	void updatePlayer(const sf::Time& delta_time);
	void updateRound();

	void spawnZombies(const sf::Time& delta_time);
	void updateZombie(const sf::Time& delta_time, int i);

	void spawnBoss(const sf::Time& delta_time);
	void updateBoss(const sf::Time& delta_time);

	void spawnPet();
	void updatePet(const sf::Time& delta_time);

	void spawnBullet(BulletOwner::Owner owner);
	void updateBullet(const sf::Time& delta_time);

	void updateBoost();

	void updateGameView(const sf::Time& delta_time);
	void updateHud();

	void renderEnemies();
	void renderPlayer();
	void renderBoss();
	void renderPet();
	void renderBullets();
	void renderBoosts();
	void renderAchievement();

	void playerInit(Textures::ID id, std::shared_ptr<StrategyFight> stf);
	void gameViewInit();
	void textureInit();
	void varInit();

	TileMap tile_map;
	GridNode grid;
	sf::View game_view;
	Hud hud;
	RoundManager round;
	Achievement * achievement;
	CollisionManager collision;
	BoostManager boost_manager;

	std::shared_ptr<TextureHolder> textures;

    std::vector<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<PlayerT> player;
	std::shared_ptr<Boss> boss;

	std::shared_ptr<Pet> pet;
	std::vector<std::shared_ptr<Bullet>> bullets;

	int enemies_alive;
	bool boss_alive;
	bool pet_alive;

	const int max_enemies = 5;
	const float game_view_speed = 4.5f;

};