#include "Game.h"
#include "Player.h"
#include "Enemy.h"


Game::Game() : window(sf::VideoMode(1920, 1080), "Survive.io"), game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f)) 
{
	//TEXTURES
	_textures.load(Textures::Enemy, "Sources/zombie1.png");
	_textures.load(Textures::Proiettile, "Sources/bullets/bullet1.png");
	//PLAYER

	//ENEMY
	n_max_enemies = 5;
	n_enemies_alive = 0;

	game_view.setCenter(player.getPosition());
	walls_collision = tile_map.getWalls();
}

void Game::run()
{
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;

	while (window.isOpen()) 
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) 
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{ // E' QUI CHE REGISTRI GLI EVENTI E POI IN UPDATE SELEZIONI
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	mouse_pos_view = (window).mapPixelToCoords(sf::Mouse::getPosition(window));
	// UPDATE
	player.update(deltaTime, mouse_pos_view, walls_collision, enemies);
	if ((player.getHp() < 0))
	{
		window.close();
	}

	//ENEMY
	while(n_enemies_alive != n_max_enemies)
	{
		std::shared_ptr<Enemy> enemy(new Enemy(rand() % 1000, rand() % 1000, _textures.get(Textures::Enemy)));
		enemies.push_back(enemy); //std:move(enemy) per unique_ptr
		n_enemies_alive++; //VITA
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(deltaTime, &player, walls_collision, enemies);

		if ((enemies[i]->getHp() < 0))
		{
			enemies.erase(enemies.begin() + i);
			n_enemies_alive--; //MORTE
		}

	}

	//BULLET
	if (player.isShooting(deltaTime) && player.ammo)
	{
		std::unique_ptr<Bullet>bullet(new Bullet(_textures.get(Textures::Proiettile))); //creo proiettile
		player.ammo--;

		bullet->setDir(player.getPosition(), mouse_pos_view); //set al proiettile la sua direzione
		flying_bullets.push_back(std::move(bullet)); //lo metto in un vettore (diventa "autosuff")
		counter_flying_obj++;
	}
	for (int i = 0; i < flying_bullets.size(); i++)
	{
		if (!(flying_bullets[i])->update(deltaTime, walls_collision, enemies)) 
			flying_bullets.erase(flying_bullets.begin() + i);
	}

	game_view.setCenter(player.getPosition());
	window.setView(game_view);
}


void Game::render()
{
	window.clear();

	tile_map.render(window);
	player.render(&window);

	//BULLET
	for (auto i = flying_bullets.begin(); i != flying_bullets.end(); i++)
	{
		(*i)->render(&window);
		window.draw((*i)->hit_box);
	}

	window.draw(player.hit_box);

	//ENEMY
	for (auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->render(&window);
		window.draw((*i)->hit_box);
	}
	
	window.display();
}


