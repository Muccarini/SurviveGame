#include "GameLogic.h"


GameLogic::GameLogic() : game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f))
{
	textureInit();
	entitiesInit();
	varInit();
	gameViewInit();
}

GameLogic::~GameLogic()
{ 
	//delete enemies;
}

void GameLogic::update(sf::Time deltaTime)
{
	updateMousePos();
	updateEntityData(deltaTime);
	updateHud();

	updatePlayer(entitydata);
	updateEnemies(entitydata);
	updatePet(entitydata);

	updateBoost(entitydata);

	updateGameView(deltaTime);
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
}

void GameLogic::updateHud()
{
	hud.updateText(kill_counter, round.getCountdown().asSeconds(), round.getCounter(), game_view);
}

void GameLogic::updateEnemies(const std::shared_ptr<EntityData> entitydata)
{
	if (kill_counter == 5) //RESET ROUND
	{
		for (int i = 0; i < enemies->size(); i++)
		{
			enemies->erase(enemies->begin(), enemies->end());
		}

		enemies_alive = 0;
		kill_counter = 0;
		round.reset();
		round.increase();

		if (!pet_alive) {
			this->pet = std::make_shared<Pet>(textures.get(Textures::HP), textures.get(Textures::Proiettile), player->getPosition());
			this->pet_alive = true;
		}

		if (round.getCounter() % 3 == 0)
			round.setBossRound(true);
	}

	//ZOMBIE SPAWN
	if (!round.isLoading() && !round.isBossRound())
	{
		while (enemies_alive != max_enemies)
		{
			this->enemies->emplace_back(new Enemy(textures.get(Textures::Enemy)));
			enemies_alive++;
		}

		for (int i = 0; i < enemies->size(); i++)
		{
			(*enemies)[i]->update(entitydata);

			if (((*enemies)[i]->getHp() <= 0))
			{
				enemies->erase(enemies->begin() + i);
				enemies_alive--;
				kill_counter++;
			}
		}
	}

	else
		//BOSS SPAWN
	{
		round.startCountdown(this->entitydata->deltaTime);
		if(!round.isLoading() && round.isBossRound())
		{
			if (!boss_alive)
			{
				std::shared_ptr<Character>boss(new Boss(textures.get(Textures::Boss), textures.get(Textures::Proiettile)));
				this->boss = boss;
				entitydata->boss = this->boss;
				this->boss_alive = true;
			}
			updateBoss(entitydata);
		}
	}
}

void GameLogic::updateBoss(std::shared_ptr<EntityData> entitydata)
{
		boss->update(entitydata);
		if ((boss->getHp() <= 0))
		{
			boss.reset();
			entitydata->boss.reset();
			entitydata->boss = nullptr;
			round.setBossRound(false);
			this->boss_alive = false;
		}
}

void GameLogic::updatePet(std::shared_ptr<EntityData> entitydata)
{
	if (pet_alive)
	{
		pet->update(entitydata);
	}
}

void GameLogic::updateBoost(std::shared_ptr<EntityData> entitydata)
{
	if (boost.size() < 4)
	{
		if (boost_time.getElapsedTime() > rand_time)
		{
			this->boost.emplace_back(new Boost(boost_pos, textures.get(Textures::HP), textures.get(Textures::MS)));
			this->boost_time.restart();
			this->rand_time = sf::seconds((rand() % 10)+ 5);
		}
	}
	//if !empty
		for (int i = 0; i < boost.size(); i++)
		{
			boost[i]->update(entitydata);
			if (!boost[i]->isAlive())
				boost.erase(boost.begin() + i);

		}
}

void GameLogic::updatePlayer(const std::shared_ptr<EntityData> entitydata)
{
	player->update(entitydata);
	if(player->getHp() <=0)
	{
		//states->top()->endState(); //GAMEOVER
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

void GameLogic::entitiesInit()
{  
	entitydata = std::make_shared<EntityData>();

	this->enemies = new std::vector<std::shared_ptr<Character>>;
	this->player = std::make_shared<PlayerT>(textures.get(Textures::Personaggio), textures.get(Textures::Proiettile), textures.get(Textures::PersonaggioMS));
}

void GameLogic::gameViewInit()
{
	this->game_view.setCenter(player->getPosition());
}

void GameLogic::varInit()
{
	this->max_enemies = 1;
	this->enemies_alive = 0;
	this->boss_alive = false;
	this->pet_alive = false;

	this->kill_counter = 0;
	this->game_view_speed = 4.5f;
	this->rand_time = sf::seconds((rand() % 10) +5);

	boost_pos = std::make_shared<BoostPos>();
	entitydataInit();
}

void GameLogic::entitydataInit()
{
	entitydata->enemies        = this->enemies;
	entitydata->map            = std::make_shared<TileMap>(this->tile_map);
	entitydata->player         = this->player;
	entitydata->boss           = nullptr;
}

void GameLogic::textureInit()
{
	textures.load(Textures::Enemy, "Sources/zombie1.png");
	textures.load(Textures::Proiettile, "Sources/bullets/bullet1.png");
	textures.load(Textures::Boss, "Sources/boss/boss.png");
	textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	textures.load(Textures::PersonaggioMS, "Sources/player_boost_speed.png");
	textures.load(Textures::HP, "Sources/hp.png");
	textures.load(Textures::MS, "Sources/ms.png");
}

