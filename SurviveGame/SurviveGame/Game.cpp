#include "Game.h"


Game::Game() : window(sf::VideoMode(1920, 1080), "Survive.io"), game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 280.f)) 
{
	game_view.setCenter(player.getPosition());
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
	player.update(deltaTime, (window).mapPixelToCoords(sf::Mouse::getPosition(window)));
	enemy.update(deltaTime,&player);

	game_view.setCenter(player.getPosition());
	window.setView(game_view);
}


void Game::render()
{
	window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA
	player.render(&window); //RENDERIZZIAMO IL GIOCATORE PER IL NUOVO FRAME
	enemy.render(&window);
	window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE
}


