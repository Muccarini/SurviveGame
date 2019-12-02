#include "GameLogic.h"


GameLogic::GameLogic() : game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f))
{
	varInit();
	entitiesInit();

	entitydata->enemies = this->enemies;
	entitydata->walls = this->tile_map.getWalls();
	entitydata->target = this->player;
	entitydata->mouse_pos_view = &this->mouse_pos_view;
	gameViewInit();
}

GameLogic::~GameLogic()
{ 
}

void GameLogic::update(sf::Time deltaTime)
{
	entitydata->deltaTime = deltaTime;
	updateMousePos();
	updateHud();

	updatePlayer(entitydata);
	updateEnemies(entitydata);
	/*updateBullets(deltaTime);*/

	updateGameView(deltaTime);
}


void GameLogic::render()
{
	tile_map.render(window);

	if(!round.isLoading() && !round.isBossRound())
		renderEnemies();

	renderPlayer();

	hud.renderTextsHud(window);
}

void GameLogic::updateHud()
{
	hud.updateText(kill_counter, round.getCountdown().asSeconds(), round.getCounter(), game_view);
}

void GameLogic::updateEnemies(const std::shared_ptr<EntityData> entitydata)
{
	if (kill_counter == 1) //RESET ROUND
	{
		for (int i = 0; i < enemies->size(); i++)
		{
			enemies->erase(enemies->begin(), enemies->end());
		}
		enemies_alive = 0,
		kill_counter = 0;
		round.reset();
		round.increase();

		if (round.getCounter() % 3 == 0)
			round.setBossRound(true);
	}

	if (!round.isLoading() && !round.isBossRound())
	{
		while (enemies_alive != max_enemies)
		{
			this->enemies->emplace_back(new Enemy());
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
	{
		round.startCountdown(this->entitydata->deltaTime);
		if(!round.isLoading() && round.isBossRound())
		{
			/*updateBoss(deltaTime);*/
		}
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

//void GameLogic::updateBoss(sf::Time deltaTime)
//{
//	boss.update(deltaTime, &player, tile_map.getWalls());
//	if ((boss.getHp() <= 0))
//	{
//		//BOSS MORTO
//		round.setBossRound(false);
//	}
//}

void GameLogic::updateGameView(sf::Time deltaTime)
{
	sf::Vector2f dir = player->getPosition() - game_view.getCenter();
	game_view.move(dir * deltaTime.asSeconds() * this->game_view_speed);
	window->setView(game_view);
}


void GameLogic::renderPlayer()
{
	player->render(window);
	player->renderHud(window);
}

//void GameLogic::renderBullet()
//{
//	for (auto i = flying_bullets.begin(); i != flying_bullets.end(); i++)
//	{
//		(*i)->render(window);
//		window->draw((*i)->hit_box);
//	}
//}

void GameLogic::renderEnemies()
{
	for (auto i = enemies->begin(); i != enemies->end(); i++)
	{
		(*i)->render(window);
		(*i)->renderHud(window);
	}
}

//void GameLogic::renderBoss()
//{
//	boss.render(window);
//}

void GameLogic::entitiesInit()
{  
	//DATA INIT
	entitydata = std::make_shared<EntityData>();

	//ENEMY INIT
	this->enemies = new std::vector<std::shared_ptr<Character>>;

		for(int i = 0 ; i < max_enemies ; i++)
		{
			this->enemies->emplace_back(new Enemy());
			this->enemies_alive = max_enemies;
		}
	//PLAYER INIT
		this->player = std::make_shared<PlayerT>();
}

void GameLogic::gameViewInit()
{
	this->game_view.setCenter(player->getPosition());
	this->game_view_speed = 4.5;
}

void GameLogic::varInit()
{
	max_enemies = 5;
	enemies_alive = 0;
	kill_counter = 0;
}


