#include "GameLogic.h"


GameLogic::GameLogic() : game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f))
{
	textureInit();  //TODO CAMBIARE TEXTURE A BULLET
	enemiesInit();
	gameViewInit();
}

GameLogic::~GameLogic()
{ 
}

void GameLogic::update(sf::Time deltaTime)
{
	updateHud();
	updateMousePos();

	updatePlayer(deltaTime);
	updateEnemies(deltaTime);
	updateBullets(deltaTime);

	updateGameView(deltaTime);
}


void GameLogic::render()
{
	tile_map.render(window);

	renderEnemies();
	renderBoss();
	renderPlayer();
	renderBullet();

	hud.renderTextsHud(window);
}

void GameLogic::updateHud()
{
	hud.updateText(kill_counter, round.getCountdown().asSeconds(), round.getCounter(), game_view);
}

void GameLogic::updateEnemies(sf::Time deltaTime)
{
	if (kill_counter == 1) //RESET ROUND
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies.erase(enemies.begin(), enemies.end());
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
			std::shared_ptr<Enemy> enemy(new Enemy(rand() % 900, rand() % 900, _textures.get(Textures::Enemy)));
			enemies.push_back(enemy);
			enemies_alive++;
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->update(deltaTime, &player, tile_map.getWalls(), enemies);

			if ((enemies[i]->getHp() <= 0))
			{
				enemies.erase(enemies.begin() + i);
				enemies_alive--;
				kill_counter++;
			}
		}
	}
	else
	{
		round.startCountdown(deltaTime);
		if(!round.isLoading() && round.isBossRound())
		{
			updateBoss(deltaTime);
		}
	}
}

void GameLogic::updatePlayer(sf::Time deltaTime)
{
	player.update(deltaTime, mouse_pos_view, tile_map.getWalls(), enemies);
	if ((player.getHp() <= 0))
	{
		//states->top()->endState(); //GAME OVER
	}
}

void GameLogic::updateBullets(sf::Time deltaTime)
{
	//E' POSSIBILE METTERLO DENTRO PLAYER MA NON PUO ESTENDERE GAMECHARACTER BISOGNA FARE UN CLASSE BULLET APPARTE
	if (player.isShooting(deltaTime) && player.getAmmo())
	{
		std::unique_ptr<Bullet>bullet(new Bullet(_textures.get(Textures::Proiettile)));
		player.decreaseAmmo();

		bullet->setDir(player.getPosition(), mouse_pos_view);
		flying_bullets.push_back(std::move(bullet));
		counter_flying_obj++;
	}

	for (int i = 0; i < flying_bullets.size(); i++)
	{
		if (!(flying_bullets[i])->update(deltaTime, tile_map.getWalls(), enemies))
			flying_bullets.erase(flying_bullets.begin() + i);
	}
}

void GameLogic::updateBoss(sf::Time deltaTime)
{
	boss.update(deltaTime, &player, tile_map.getWalls());
	if ((boss.getHp() <= 0))
	{
		//BOSS MORTO
		round.setBossRound(false);
	}
}

void GameLogic::updateGameView(sf::Time deltaTime)
{
	sf::Vector2f dir = player.getPosition() - game_view.getCenter();
	game_view.move(dir * deltaTime.asSeconds() * this->game_view_speed);
	window->setView(game_view);
}


void GameLogic::renderPlayer()
{
	player.render(window);
	window->draw(player.hit_box);
}

void GameLogic::renderBullet()
{
	for (auto i = flying_bullets.begin(); i != flying_bullets.end(); i++)
	{
		(*i)->render(window);
		window->draw((*i)->hit_box);
	}
}

void GameLogic::renderEnemies()
{
	for (auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->render(window);
		window->draw((*i)->hit_box);
	}
}

void GameLogic::renderBoss()
{
	boss.render(window);
}

void GameLogic::textureInit()
{
	_textures.load(Textures::Enemy, "Sources/zombie1.png");
	_textures.load(Textures::Proiettile, "Sources/bullets/bullet1.png"); //TODO CAMBIARE IMMAGINE TROPPO DETTAGLIATA PER UN OGGETTO COSI' PICCOLO
	_textures.load(Textures::Boss, "Sources/boss/boss.png");
}

void GameLogic::gameViewInit()
{
	this->game_view.setCenter(player.getPosition());
	this->game_view_speed = 4.5;
}

void GameLogic::enemiesInit()
{
	max_enemies = 5;
	enemies_alive = 0;
	kill_counter = 0;
}


