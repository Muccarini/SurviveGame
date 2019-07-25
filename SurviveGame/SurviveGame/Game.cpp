#include "Game.h"
#include "TextureHolder.h"


Game::Game(): _window(sf::VideoMode(1920, 1080),"Survive.io"), //CLASSE RENDERWINDOW *VEDERE MANUALE COSTRUTTORI
_player(),_isMovingUp(false), _isMovingDown(false), _isMovingLeft(false), _isMovingRight(false)
{
	//_textures.load(Textures::Background,"PATH/TO/THE/BACKGROUND_IMAGE");
	_textures.load(Textures::Personaggio, "C:/Users/pandi/source/repos/SurvivalGame/Debug/textures/pg.png");
	_player.setTexture(_textures.get(Textures::Personaggio));
	_player.setPosition(100.f, 100.f);
	_player.setTextureRect(sf::IntRect(0, 0, 32, 48));
	//_player.setScale(sf::Vector2f(1.5f, 1.5f));
}

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
	
	if (key == sf::Keyboard::S)
	{
		_isMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::W)
	{
		_isMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		_isMovingRight = isPressed;
	}
	else if (key == sf::Keyboard::A)
	{
		_isMovingLeft = isPressed;
	}
}

void Game::update(sf::Time deltaTime, int framePlayer)
{  // QUI CI SARA' LA LOGICA DEL GIOCO CHE FAREMO PIU IN LA'

	const float PlayerSpeed = 150.f;

	framePlayer = 0;
    sf::Vector2f movement(0.f, 0.f);
	if (framePlayer == 5)
		framePlayer = 0;

	if (_isMovingUp) //VELOCITA' DEL GIOCATORE
	{
		//movement.y = 0;
		movement.y -= PlayerSpeed;
		_player.setTextureRect(sf::IntRect(framePlayer * 32, 48, 32, 48));
		//_player.setScale(sf::Vector2f(1.5f, 1.5f));
	}
	if (_isMovingDown)
	{
		//movement.y = 0;
		movement.y += PlayerSpeed;
		_player.setTextureRect(sf::IntRect(framePlayer * 32, 0, 32, 48));
		//_player.setScale(sf::Vector2f(1.5f, 1.5f));
	}
	if (_isMovingLeft)
	{
		//movement.x = 0;
		movement.x -= PlayerSpeed;
		_player.setTextureRect(sf::IntRect(framePlayer * 32, 48 * 2, 32, 48));
		//_player.setScale(sf::Vector2f(1.5f, 1.5f));
	}
	if (_isMovingRight)
	{
		//movement.x = 0;
		movement.x += PlayerSpeed;
		_player.setTextureRect(sf::IntRect(framePlayer * 32, 48 * 3, 32, 48));
		//_player.setScale(sf::Vector2f(1.5f, 1.5f));
	}

	_player.move(movement * deltaTime.asSeconds()); // VELOCITA DEL GIOCATORE * TEMPO = DISTANZA   
	framePlayer++;
}

void Game::render()
{
	_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA
	_window.draw(_player); //RENDERIZZIAMO IL GIOCATORE PER IL NUOVO FRAME
	_window.display();   // LO FACCIAMO VEDERE A SCHERMO ALL'UTENTE
}


