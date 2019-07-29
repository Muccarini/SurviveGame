#include "Game.h"
#include "TextureHolder.h"


Game::Game() : _window(sf::VideoMode(1920, 1080), "Survive.io"), _hero() {} //CLASSE RENDERWINDOW *VEDERE MANUALE COSTRUTTORI

void Game::run()
{
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	int framePlayer = 0;
	while (_window.isOpen()) 
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) 
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame, framePlayer);
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
			handlePlayerInput(event.key.code, true);
			if (event.key.code == sf::Keyboard::Escape)
				_window.close();
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			_window.close();
			break;
		}
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::S || key == sf::Keyboard::W || key == sf::Keyboard::D || key == sf::Keyboard::A) 
	{
		_hero.isMoving = true;
	}
	// if(key == WASD) _hero.isMove =true
}

void Game::update(sf::Time deltaTime, int framePlayer)
{
	if (_hero.isMoving) _hero.move();
	sf::Vector2f movement;
	movement=_hero.move(); 
	_hero._sprite.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA
	_window.draw(_hero); //RENDERIZZIAMO IL GIOCATORE PER IL NUOVO FRAME
	_window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE
}


