#include "Game.h"
#include "Player.h"
#include "Enemy.h"


Game::Game() : window(sf::VideoMode(1920, 1080), "Survive.io"), game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 280.f)) 
{
	player = new Player();

	for (int i = 0 ; i < 10 ; i++)
	{
		enemies.push_back(new Enemy(rand() % 500, rand() % 500));
	}
	game_view.setCenter(player->getPosition());
	game_view.setSize(600.f, 280.f);
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
	player->update(deltaTime, (window).mapPixelToCoords(sf::Mouse::getPosition(window)));

	for(auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->update(deltaTime, player);
	}

	game_view.setCenter(player->getPosition());
	window.setView(game_view);
}


void Game::render()
{
	window.clear();

	tile_map.render(window);
	player->render(&window);
	for (auto i = enemies.begin(); i != enemies.end(); i++)
	{
		(*i)->render(&window);
	}

	
	window.display();
}


