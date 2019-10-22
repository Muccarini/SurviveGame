#include "Game.h"
#include "Player.h"
#include "Enemy.h"


Game::Game() : window(sf::VideoMode(1920, 1080), "Survive.io"), game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280.f, 720.f)) 
{
	//ENEMY
	for (int i = 0 ; i < 0; i++)
	{
		std::shared_ptr<Enemy> enemy(new Enemy(rand() % 1000, rand() % 1000));
		enemies.push_back(enemy); //std:move(enemy) per unique_ptr
	}
	//GUN
	ammo = 30;
	for(int i = 0 ; i < ammo ; i++)
	{
		Bullet bullet(player.getPosition());
		p_bullets.push_back(bullet);
	}

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
{
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
	player.update(deltaTime, mouse_pos_view, walls_collision, enemies);

	//GUN
	if (player.shoot() && ammo != 1)
	{
		int i = 4;
			p_bullets[i].update(deltaTime, mouse_pos_view, walls_collision, enemies);
	}

	//ENEMY
	for(auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->update(deltaTime,&player, walls_collision, enemies);
	}

	game_view.setCenter(player.getPosition());
	window.setView(game_view);
}


void Game::render()
{
	window.clear();

	tile_map.render(window);
	player.render(&window);

	
	int i = 4;
		p_bullets[i].render(&window);
	

	window.draw(player.hit_box);

	for (auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->render(&window);
		window.draw((*i)->hit_box);
	}
	
	window.display();
}


