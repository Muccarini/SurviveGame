#include "Game.h"


Game::Game() : _window(sf::VideoMode(1920, 1080), "Survive.io")
{
	//_wall.setFillColor(sf::Color::Red);
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
	_player.update(deltaTime, mousePosView);
	_map.update(deltaTime, _window, &_player);
	_enemy.update(deltaTime,&_player);
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_view.move(-viewSpeed * deltaTime.asSeconds(), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_view.move(viewSpeed * deltaTime.asSeconds(), 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_view.move(0.f, -viewSpeed * deltaTime.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_view.move(0.f, viewSpeed * deltaTime.asSeconds());
	}*/
	
	/*//update della posizione del mouse
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(_window);
	_window.setView(_view);
	mousePosView = _window.mapPixelToCoords(mousePosWindow);
	if (mousePosView.x >= 0.f)
		mousePosGrid.x = mousePosView.x / gridSizeU;
	if (mousePosView.y >= 0.f)
		mousePosGrid.y = mousePosView.y / gridSizeU;
	_window.setView(_window.getDefaultView());
	_view.setCenter(_player.getPosition());
	*/

}


void Game::render()
{
	_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA
	
	_window.draw(_map._tiles);

	_window.draw(_wall);

	//_window.draw(*(_map.player));
	_player.render(&_window); //RENDERIZZIAMO IL GIOCATORE PER IL NUOVO FRAME
	_enemy.render(&_window);

	_window.setView(_window.getDefaultView());

	_window.draw(_map._text);

	_window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE
}


