#include "Game.h"


Game::Game() : _window(sf::VideoMode(1920, 1080), "Survive.io") {}

void Game::run()
{
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;

	while (_window.isOpen()) 
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
	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
			break;
		case sf::Event::Closed:
			_window.close();
			break;

		}
	}
}

void Game::update(sf::Time deltaTime)
{
	_player.update(deltaTime,&_window);
	_window.setView(_player.view);

	_enemy.update(deltaTime,&_player);
}


void Game::render()
{
	_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA
	_player.render(&_window); //RENDERIZZIAMO IL GIOCATORE PER IL NUOVO FRAME
	_enemy.render(&_window);
	_window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE
}


