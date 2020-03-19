#include "GameLogic.h"


GameLogic::GameLogic(Textures::ID id, std::shared_ptr<StrategyFight> stf) : game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f)),
tile_map(sf::Vector2i(20, 20)), grid(20, 20)
{
	textureInit();
	boost_manager.setTextures(textures->get(Textures::HP), textures->get(Textures::MS));
	playerInit(id, stf);
	varInit();
	gameViewInit();
	achievement = new Achievement(&round);
}

GameLogic::~GameLogic()
{ 
	delete achievement;
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

	//petCollision
	if(pet_alive)
	{
		collision.CollideWithEntity(enemies[i]->getHitBox().getGlobalBounds(), pet->getHitBox().getGlobalBounds());
		if (collision.isCollide())
			pet->takeDamage();
		collision.reset();
	}

	//collisionwalls
	sf::Vector2f dir = collision.CollideWithWalls(enemies[i]->getHitBox().getGlobalBounds(), tile_map.findWalls(static_cast<int>(enemies[i]->getPosition().x), static_cast<int>(enemies[i]->getPosition().y)));
	if (collision.isCollide())
	{
		enemies[i]->setPosition(player->getPosition() + dir);
		collision.reset();
	}
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

	//playerCollision
		sf::Vector2f dir = collision.CollideWithEntity(pet->getHitBox().getGlobalBounds(), player->getHitBox().getGlobalBounds());
		if (collision.isCollide())
			pet->setPosition(pet->getPosition() + dir);
		collision.reset();

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
	if (owner == BulletOwner::Player)
	{
		player->getStf()->shot(bullets, owner, player->getPosition(), mouse_pos_view, textures->get(Textures::Proiettile));
		player->setAmmo(player->getAmmo() - player->getStf()->nrshot);
		if ((player->getAmmo() - player->getStf()->nrshot) < 0)
			player->getStf()->nrshot = player->getAmmo();
	}
		if (owner == BulletOwner::Boss)
		{
			std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Boss, boss->getPosition(), textures->get(Textures::Proiettile)));
			boss->setAmmo(boss->getAmmo() - 1);
			bullets.emplace_back(bullet);
			bullet->calculateDir(boss->getPosition(), player->getPosition());
		}
		if (owner == BulletOwner::Pet)
		{
			player->getStf()->shot(bullets, owner, pet->getPosition(), mouse_pos_view, textures->get(Textures::Proiettile));
			if ((player->getAmmo() - player->getStf()->nrshot) < 0)
				player->getStf()->nrshot = player->getAmmo();
		}
}

void GameLogic::updateBullet(sf::Time deltaTime)
{
	if (!bullets.empty())
	{
		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->updateRotate();

			//ALLIED
			if (bullets[i]->isAllied())
			{
				//collisonZombies
				if (!enemies.empty())
				{
					for (int j = 0; j != enemies.size(); j++)
					{
						collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), enemies[j]->getHitBox().getGlobalBounds());
						if (collision.isCollide())
						{
							enemies[j]->takeDamage();
							bullets.erase(bullets.begin() + i);
							j = (enemies.size() - 1);
						}
					}
				}

				//collisionBoss
				if (boss_alive)
				{
					collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), boss->getHitBox().getGlobalBounds());
					if (collision.isCollide())
					{
						boss->takeDamage();
						bullets.erase(bullets.begin() + i);
					}
				}
			}
			else //!ALLIED
			{
				//collisionPlayer
				collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), player->getHitBox().getGlobalBounds());
				if (collision.isCollide())
				{
					player->takeDamage();
					bullets.erase(bullets.begin() + i);
				}
				else
				{
					if (pet_alive)
					{
						//collisionPet
						collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), pet->getHitBox().getGlobalBounds());
						if (collision.isCollide())
						{
							pet->takeDamage();
							bullets.erase(bullets.begin() + i);
						}
					}
				}
			}

			//WALLS
			if (collision.isCollide())
				collision.reset();
			else
			{
				collision.CollideWithWalls(bullets[i]->getHitBox().getGlobalBounds(), tile_map.findWalls(static_cast<int>(bullets[i]->getPosition().x), static_cast<int>(bullets[i]->getPosition().y)));
				if (collision.isCollide())
				{
					collision.reset();
					bullets.erase(bullets.begin() + i);
				}
				else
					bullets[i]->updateMove(deltaTime);
			}
		}
	}
}

void GameLogic::updateBoost()
{
	//SPAWN
	if (boost_manager.canSpawn())
	{
		boost_manager.spawn();
	}

	////UPDATE BOOST
	int b_type = boost_manager.checkCollisionType(player->getHitBox().getGlobalBounds());
	player->boost(BoostType::Type(b_type));
}

void GameLogic::updatePlayer(sf::Time deltaTime)
{
	player->updateMove(deltaTime);
	player->updateMovSpeed(deltaTime);
	player->updateHud();

	//collisionZomies
	if (!enemies.empty())
	{
		for(int i = 0; i != enemies.size(); i++)
		{
			sf::Vector2f dir = collision.CollideWithEntity(player->getHitBox().getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds());
			if(collision.isCollide())
			{
				player->takeDamage();
				player->setPosition(player->getPosition() + dir);
				collision.reset();
			}
		}
	}

	//collisionBoss
	if (boss_alive)
	{
		sf::Vector2f dir = collision.CollideWithEntity(player->getHitBox().getGlobalBounds(), boss->getHitBox().getGlobalBounds());
		if (collision.isCollide())
		{
			player->setPosition(player->getPosition() + dir);
			collision.reset();
		}
	}

	//collisionwalls
	sf::Vector2f dir = collision.CollideWithWalls(player->getHitBox().getGlobalBounds(), tile_map.findWalls(static_cast<int>(player->getPosition().x), static_cast<int>(player->getPosition().y)));
	if (collision.isCollide())
	{
		player->setPosition(player->getPosition() + dir);
		collision.reset();
	}

	if (player->shooting(deltaTime))
		spawnBullet(BulletOwner::Player);

	player->updateRotate(mouse_pos_view);

	if (player->updateReload(deltaTime))
		player->setTexturesSprite(textures->get(player->getId()));
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
	boost_manager.renderBoosts(window);
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

void GameLogic::playerInit(Textures::ID id, std::shared_ptr<StrategyFight> stf)
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

