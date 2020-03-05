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
	updateEntityData(deltaTime);
	achievement->updateBadge(deltaTime);

	updateHud();
	updatePlayer(deltaTime);
	updateRound();
	if (!round.isLoading() && !round.isBossRound())
		spawnZombies(deltaTime);
	else
		spawnBoss();

	updatePet();

	updateBoost();

	updateGameView(deltaTime);

	updateState();
}


void GameLogic::render()
{
	tile_map.render(window);

	if(!boost.empty())
		renderBoost();

	renderPlayer();
	renderPet();
	renderEnemies();
	renderBoss();

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

void GameLogic::updateHud()
{
	hud.updateText(round.getKills(), round.getCountdown().asSeconds(), round.getCounterRound(), game_view);
}

void GameLogic::spawnZombies(sf::Time deltaTime)
{
		while (enemies_alive != max_enemies)
		{
			this->enemies->emplace_back(new Enemy(textures->get(Textures::Enemy), &grid, tile_map.getGridSize()));
			enemies_alive++;
		}

		for (unsigned int i = 0; i < enemies->size(); i++)
		{
			updateZombie(deltaTime, i);

			if (((*enemies)[i]->getHp() <= 0))
			{
				enemies->erase(enemies->begin() + i);
				enemies_alive--;
				round.increaseKills();
			}
		}
}

void GameLogic::updateZombie(sf::Time deltaTime, int i)
{
	(*enemies)[i]->updateMove(deltaTime, player->getPosition(), tile_map.getGridSize());
	(*enemies)[i]->updateRotate(player->getPosition());
	(*enemies)[i]->updateHud();
	(*enemies)[i]->updateCollision(player->getHitBox().getGlobalBounds(), 
		pet->getHitBox().getGlobalBounds(), tile_map.findWalls(static_cast<int>((*enemies)[i]->getPosition().x), static_cast<int>((*enemies)[i]->getPosition().y)));
}

void GameLogic::spawnBoss()
{
	round.startCountdown(this->entitydata->deltaTime);
	if (!round.isLoading() && round.isBossRound())
	{
		if (!boss_alive)
		{
			std::shared_ptr<Character>boss(new Boss(this->entitydata));
			this->boss = boss;
			entitydata->boss = this->boss;
			this->boss_alive = true;
		}

		updateBoss();

		if ((boss->getHp() <= 0))
		{
			spawnPet();

			//RESET BOSS AND ROUND
			boss.reset();
			entitydata->boss.reset();

			round.setBossRound(false);
			this->boss_alive = false;
			round.increaseBoss();
			round.setKills(0);
			round.reset();
			round.increaseRound();
		}
	}
}

void GameLogic::updateBoss()
{

	boss->updateMove();
	boss->updateBullets();
	boss->updateRotate();
	boss->updateReload();
	boss->updateHud();
	boss->updateCollision();

	boss->updateShooting();
}

void GameLogic::spawnPet()
{
	//SPAWN PET
	if (!pet_alive)
	{
		this->pet = std::make_shared<Pet>(this->entitydata);
		entitydata->pet = this->pet;
		this->pet_alive = true;
	}
	else
		pet->boostHeal();
}

void GameLogic::updatePet()
{
	if (pet_alive)
	{
		pet->update();

		//PET DEATH
		if(pet->getHp() <= 0)
		{
			this->pet.reset();
			entitydata->pet.reset();
			this->pet_alive = false;
		}
	}
}

void GameLogic::updateBoost()
{
	//SPAWN BOOST
	if (boost.size() < 4)
	{
		if (boost_time.getElapsedTime() > rand_time)
		{
			this->boost.emplace_back(new Boost(boost_pos, this->entitydata));
			this->boost_time.restart();
			this->rand_time = sf::seconds((rand() % 10)+ 5.f);
		}
	}
	if (!boost.empty())
	{
		for (unsigned int i = 0; i < boost.size(); i++)
		{
			if (boost[i]->checkCollide(player->getHitBox().getGlobalBounds()))
				boost[i]->boostSubject(player);

			if (!boost[i]->isAlive())
				boost.erase(boost.begin() + i);
		}
	}
}

void GameLogic::updatePlayer(sf::Time deltaTime)
{
	player->updateMove(deltaTime);
	player->updateMovSpeed(deltaTime);
	player->updateCollision();


	player->updateBullets(deltaTime, mouse_pos_view);
	player->updateShooting(deltaTime);

	player->updateRotate();

	if (player->updateReload())
		player->setTexturesSprite(this->textures);

	player->updateHud();

}

void GameLogic::updateRound()
{
	if (round.getKills() == round.getKillsPerRound())
	{
		for (unsigned int i = 0; i < enemies->size(); i++)
		{
			enemies->erase(enemies->begin(), enemies->end());
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

void GameLogic::updateEntityData(sf::Time deltaTime)
{
	entitydata->deltaTime = deltaTime;
	entitydata->mouse_pos_view = this->mouse_pos_view;
}

void GameLogic::renderPlayer()
{
	player->renderHud(window);
	player->render(window);
	player->renderBullets(window);
}

void GameLogic::renderBoss()
{
	if (boss_alive)
	{
			boss->renderHud(window);
			boss->render(window);
			boss->renderBullets(window);
	}
}

void GameLogic::renderPet()
{
	if (pet_alive)
	{
		pet->renderHud(window);
		pet->render(window);
		pet->renderBullets(window);
	}
}

void GameLogic::renderBoost()
{
	for(int i = 0; i != boost.size(); i++)
	{
		boost[i]->render(window);
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
		for (auto i = enemies->begin(); i != enemies->end(); i++)
		{
			(*i)->render(window);
			(*i)->renderHud(window);
		}
	}
}

void GameLogic::entitiesInit(Textures::ID id, StrategyFight* stf)
{  
	entitydata = std::make_shared<EntityData>();

	this->id = id;
	this->entitydata->textures = this->textures;
	this->enemies = new std::vector<std::shared_ptr<Character>>;
	this->player = std::make_shared<PlayerT>(this->entitydata, id, stf);
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
	entitydataInit();
}

void GameLogic::entitydataInit()
{
	entitydata->enemies        = this->enemies;
	entitydata->map            = std::make_shared<TileMap>(this->tile_map);
	entitydata->player         = this->player;
	entitydata->boss           = nullptr;
	entitydata->grid		   = std::make_shared<GridNode>(20, 20);
	entitydata->grid->initGrid(entitydata->map->getObstacle());
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

