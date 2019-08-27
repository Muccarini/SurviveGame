#include "Game.h"


Game::Game() : _window(sf::VideoMode(1920, 1080), "Survive.io"), _view(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 500.f))
{
	//init game 
	float gridSizeF = 100.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);

	//init view
	_view.setSize(1920.f, 1080.f);
	_view.setCenter(_window.getSize().x / 2.f, _window.getSize().y / 2.f);

	//init game elemts
	sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));
}

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

void Game::handlePlayerInput(sf::Keyboard::Key key)
{
}



void Game::update(sf::Time deltaTime)
{
	_player.update(deltaTime);
	_enemy.update(deltaTime,&_player);
}


void Game::render()
{
	_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA

	_map.draw(&_window);
	
	_window.setView(_view);

	_window.draw(shape);

	_window.setView(_window.getDefaultView());

	_player.render(&_window); //RENDERIZZIAMO IL GIOCATORE PER IL NUOVO FRAME
	_enemy.render(&_window);
	_window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE
}


