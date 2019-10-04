#include "Game.h"


Game::Game() : _window(sf::VideoMode(1920, 1080), "Survive.io"), _map(&_player, &_enemy)
{
	_font.loadFromFile("Sources/Dosis-Light.ttf");
	_text.setCharacterSize(30);
	_text.setFillColor(sf::Color::Black);
	_text.setFont(_font);
	_text.setPosition(20.f, 20.f);

	_player.subscribe(&_map);
	_enemy.subscribe(&_map);
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
		//render();
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
	_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA

	_window.draw(_map._tileMap);

	
	//update della posizione del mouse
	mousePosScreen = sf::Mouse::getPosition();
	_window.setView(_map._view);
	(&_map)->_view.setCenter(_player.getPosition());
	mousePosWindow = sf::Mouse::getPosition(_window);

	mousePosView = _window.mapPixelToCoords(mousePosWindow);
	if (mousePosView.x >= 0.f)
		mousePosGrid.x = mousePosView.x / gridSizeU;
	if (mousePosView.y >= 0.f)
		mousePosGrid.y = mousePosView.y / gridSizeU;

	std::stringstream ss;
	ss << "TEST\n Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
		<< "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
		<< "View: " << mousePosView.x << " " << mousePosView.y << "\n"
		<< "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
		
	_text.setString(ss.str());

	_player.update(_window, deltaTime, mousePosView);
	_enemy.update(_window, deltaTime, &_player);

	tile_map.render(_window);
	_window.draw(_text);
	
	_window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE

}


void Game::render()
{/*
	_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA
	
	_window.draw(_map._tileMap);

	//_window.draw(_wall);

	//_window.draw(*(_map.player));
	//_player.render(&_window); //RENDERIZZIAMO IL GIOCATORE PER IL NUOVO FRAME
	_enemy.render(&_window);

	//_window.setView(_window.getDefaultView());

	_window.draw(_text);

	_window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE*/
}


