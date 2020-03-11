#include "GameLogic.h"


GameLogic::GameLogic(Textures::ID id, StrategyFight* stf) : game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f)), 
tile_map(sf::Vector2i(20, 20)), grid(20, 20)
{
	textureInit();
	entitiesInit(id, stf);
	varInit();
	gameViewInit();
	achievement = new Achievement(&round);
}

GameLogic::~GameLogic()
{ 

}

void GameLogic::update(sf::Time deltaTime)
{
	updateMousePos();

	updateAchievement(deltaTime);

	updateHud();

	updatePlayer(deltaTime);

	updateRound();

	if (!round.isLoading() && !round.isBossRound())
		spawnZombies(deltaTime);
	else
		spawnBoss(deltaTime);

	updatePet(deltaTime);

	updateBoost();

	updateBullet(deltaTime);

	updateGameView(deltaTime);

	updateState();
}


void GameLogic::render()
{
	tile_map.render(window);

	if(!boosts.empty())
		renderBoosts();

	renderPlayer();
	renderPet();
	renderEnemies();
	renderBoss();
	renderBullets();
	hud.renderTextsHud(window);

	renderAchievement();
}

void GameLogic::updateState()
{
	//GAMEOVER
	if(player)
		if(player->getHp() < 0)
		{
			this->states->top()->endState();
		}

	//PAUSE MENU
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->states->push(new PauseMenu());
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
		return;
	}
}

void GameLogic::updateAchievement(sf::Time deltaTime)
{
	achievement->updateBadge(deltaTime);
}

void GameLogic::updateHud()
{
	hud.updateText(round.getKills(), round.getCountdown().asSeconds(), round.getCounterRound(), game_view);
}

void GameLogic::spawnZombies(sf::Time deltaTime)
{
		while (enemies_alive != max_enemies)
		{
			this->enemies.emplace_back(new Enemy(textures->get(Textures::Enemy), grid, tile_map.getGridSize()));
			enemies_alive++;
		}

		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			updateZombie(deltaTime, i);

			if ((enemies[i]->getHp() <= 0))
			{
				enemies.erase(enemies.begin() + i);
				enemies_alive--;
				round.increaseKills();
			}
		}
}

void GameLogic::updateZombie(sf::Time deltaTime, int i)
{
	enemies[i]->updateMove(deltaTime, player->getPosition(), tile_map.getGridSize());
	enemies[i]->updateRotate(player->getPosition());
	enemies[i]->updateHud();
	enemies[i]->updateCollision(player, pet, tile_map.findWalls(static_cast<int>(enemies[i]->getPosition().x), static_cast<int>(enemies[i]->getPosition().y)), tile_map.getGridSize());
}

void GameLogic::spawnBoss(sf::Time deltaTime)
{
	round.startCountdown(deltaTime);
	if (!round.isLoading() && round.isBossRound())
	{
		if (!boss_alive)
		{
			std::shared_ptr<Boss>boss(new Boss(grid, textures->get(Textures::Boss)));
			this->boss = boss;
			this->boss_alive = true;
		}

		updateBoss(deltaTime);

		if ((boss->getHp() <= 0))
		{
			spawnPet();

			//RESET BOSS AND ROUND
			boss.reset();

			round.setBossRound(false);
			this->boss_alive = false;
			round.increaseBoss();
			round.setKills(0);
			round.reset();
			round.increaseRound();
		}
	}
}

void GameLogic::updateBoss(sf::Time deltaTime)
{
	boss->updateMove(deltaTime, player->getPosition(), tile_map.getGridSize());

	if (boss->shooting(deltaTime, player->getPosition()))
		spawnBullet(BulletOwner::Boss);

	boss->updateRotate(player->getPosition());
	boss->updateReload(deltaTime);
	boss->updateHud();
	boss->updateCollision(player->getHitBox().getGlobalBounds(), 
		tile_map.findWalls(static_cast<int>(boss->getPosition().x), static_cast<int>(boss->getPosition().y)),
		tile_map.getGridSize());
}

void GameLogic::spawnPet()
{
	if (!pet_alive)
	{
		this->pet = std::make_shared<Pet>(textures->get(Textures::Pet), boss->getPosition());
		this->pet_alive = true;
	}
	else
		pet->boostHeal();
}

void GameLogic::updatePet(sf::Time deltaTime)
{
	if (pet_alive)
	{
		pet->updateMove(deltaTime, player->getPosition());
		pet->updateRotate(mouse_pos_view);

		if (player->isShooting())
			spawnBullet(BulletOwner::Pet);

		pet->updateHud();
		pet->updateCollision(player->getHitBox().getGlobalBounds());

		//PET DEATH
		if(pet->getHp() <= 0)
		{
			this->pet.reset();
			this->pet_alive = false;
		}
	}
}

void GameLogic::spawnBullet(BulletOwner::Owner owner)
{
		if(owner == BulletOwner::Player)
		player->getStf()->shot(bullets, player->getPosition(), mouse_pos_view, textures->get(Textures::Proiettile));
		player->setAmmo(player->getAmmo() - player->getStf()->nrshot);
		if ((player->getAmmo() - player->getStf()->nrshot) < 0)
			player->getStf()->nrshot = player->getAmmo();
		if (owner == BulletOwner::Boss)
		{
			std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Boss, boss->getPosition(), textures->get(Textures::Proiettile)));
			boss->setAmmo(boss->getAmmo() - 1);
			bullets.emplace_back(bullet);
			bullet->calculateDir(boss->getPosition(), player->getPosition());
		}
		if (owner == BulletOwner::Pet)
		{
			std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Pet, pet->getPosition(), textures->get(Textures::Proiettile)));
			bullets.emplace_back(bullet);
			bullet->calculateDir(pet->getPosition(), mouse_pos_view);
		}
}

void GameLogic::updateBullet(sf::Time deltaTime)
{
	if (!bullets.empty())
	{
		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->updateRotate();

			switch (bullets[i]->getOwner())
			{
			case(BulletOwner::Player):
				bullets[i]->updateAlliedCollision(enemies, boss, tile_map.findWalls(static_cast<int>(bullets[i]->getPosition().x), static_cast<int>(bullets[i]->getPosition().y)));
				break;

			case(BulletOwner::Pet):
				bullets[i]->updateAlliedCollision(enemies, boss, tile_map.findWalls(static_cast<int>(bullets[i]->getPosition().x), static_cast<int>(bullets[i]->getPosition().y)));
				break;

			case(BulletOwner::Boss):
				bullets[i]->updateEnemyCollision(player, pet, tile_map.findWalls(static_cast<int>(bullets[i]->getPosition().x), static_cast<int>(bullets[i]->getPosition().y)));
				break;
			}
			bullets[i]->updateMove(deltaTime);

			if (bullets[i]->isCollide())
				bullets.erase(bullets.begin() + i);
		}
	}
}

void GameLogic::updateBoost()
{
	//SPAWN BOOST
	if (boosts.size() < 4)
	{
		if (boost_time.getElapsedTime() > rand_time)
		{
			std::shared_ptr<Boost> boost(new Boost(boost_pos));
			boost->setTexturesSprite(textures->get(boost->getId()));

			this->boosts.emplace_back(boost);
			this->boost_time.restart();
			this->rand_time = sf::seconds((rand() % 10)+ 5.f);
		}
	}
	if (!boosts.empty())
	{
		for (unsigned int i = 0; i < boosts.size(); i++)
		{
			if (boosts[i]->checkCollide(player->getHitBox().getGlobalBounds()))
				boosts[i]->boostSubject(player);

			if (!boosts[i]->isAlive())
				boosts.erase(boosts.begin() + i);
		}
	}
}

void GameLogic::updatePlayer(sf::Time deltaTime)
{
	player->updateMove(deltaTime);
	player->updateDash(deltaTime,tile_map);

	if (!enemies.empty())
		player->updateCollisionEnemies(enemies);
	if (boss_alive)
		player->updateCollisionBoss(boss->getHitBox().getGlobalBounds());

	player->updateCollisionWalls(tile_map.findWalls(static_cast<int>(player->getPosition().x), static_cast<int>(player->getPosition().y)), tile_map.getGridSize());

	player->updateMovSpeed(deltaTime);

	if (player->shooting(deltaTime))
		spawnBullet(BulletOwner::Player);

	player->updateRotate(mouse_pos_view);

	if (player->updateReload(deltaTime))
		player->setTexturesSprite(textures->get(player->getId()));

	player->updateHud();

}

void GameLogic::updateRound()
{
	if (round.getKills() == round.getKillsPerRound())
	{
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			enemies.erase(enemies.begin(), enemies.end());
		}

		enemies_alive = 0;
		round.setKills(0);
		round.reset();
		round.increaseRound();

		if (round.getCounterRound() % round.getRoundPerBoss() == 0)
			round.setBossRound(true);
	}
}

void GameLogic::updateGameView(sf::Time deltaTime)
{
	sf::Vector2f dir = player->getPosition() - game_view.getCenter();
	game_view.move(dir * deltaTime.asSeconds() * this->game_view_speed);
	window->setView(game_view);
}

void GameLogic::renderPlayer()
{
	player->renderHud(window);
	player->render(window);
}

void GameLogic::renderBoss()
{
	if (boss_alive)
	{
			boss->renderHud(window);
			boss->render(window);
	}
}

void GameLogic::renderPet()
{
	if (pet_alive)
	{
		pet->renderHud(window);
		pet->render(window);
	}
}

void GameLogic::renderBullets()
{
	for (int i = 0; i != bullets.size(); i++)
	{
		bullets[i]->render(this->window);
	}
}

void GameLogic::renderBoosts()
{
	for(int i = 0; i != boosts.size(); i++)
	{
		boosts[i]->render(window);
	}
}

void GameLogic::renderAchievement()
{
	if (achievement->isKillsOn())
	{
		achievement->renderKillsBadge(this->window, this->game_view);
	}

	if (achievement->isRoundOn())
	{
	    achievement->renderRoundBadge(this->window, this->game_view);
	}

	if (this->achievement->isBossOn())
	{
		achievement->renderBossBadge(this->window, this->game_view);

	}
}

void GameLogic::renderEnemies()
{
	if (!round.isLoading() && !round.isBossRound())
	{
		for (auto i = enemies.begin(); i != enemies.end(); i++)
		{
			(*i)->render(window);
			(*i)->renderHud(window);
		}
	}
}

void GameLogic::entitiesInit(Textures::ID id, StrategyFight* stf)
{  
	this->player = std::make_shared<PlayerT>(id, stf);
	player->setTexturesSprite(textures->get(id));

	this->grid.initGrid(tile_map.getObstacle());
}

void GameLogic::gameViewInit()
{
	this->game_view.setCenter(player->getPosition());
}

void GameLogic::varInit()
{
	this->enemies_alive = 0;
	this->boss_alive = false;
	this->pet_alive = false;
	this->rand_time = sf::seconds((rand() % 10) +5.f);

	boost_pos = std::make_shared<BoostPos>();
}

void GameLogic::textureInit()
{
	this->textures = std::make_shared<TextureHolder>();

	textures->load(Textures::Enemy, "Sources/zombie1.png");
	textures->load(Textures::Proiettile, "Sources/bullets/bullet1.png");
	textures->load(Textures::Boss, "Sources/boss/boss.png");
	textures->load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	textures->load(Textures::ShotgunP, "Sources/Top_Down_Survivor/shotgun/move/survivor-move_shotgun_0.png");
	textures->load(Textures::RifleP, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	textures->load(Textures::HandgunP, "Sources/Top_Down_Survivor/handgun/move/survivor-move_handgun_0.png");
	textures->load(Textures::Pet, "Sources/pet.png");
	textures->load(Textures::HP, "Sources/hp.png");
	textures->load(Textures::MS, "Sources/ms.png");
}

