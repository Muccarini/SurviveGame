#include "Game.h"



Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Survive.io", sf::Style::Fullscreen);
	states.push(new MainMenu());
	states.top()->window = this->window;
	states.top()->states = &this->states;
}


Game::~Game()
{
}

void Game::run()
{
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;

	while (window->isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			if (!this->states.empty())
			{
				if (this->window->hasFocus())
				{
					this->states.top()->update(TimePerFrame);

					if (this->states.top()->getQuit())
					{
						this->states.top()->endState();
						delete this->states.top();
						this->states.pop();
					}
				}
			}
			else
				window->close();
		}
		render();
	}
}

void Game::render()
{
	window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	window->display();
}

void Game::processEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				this->states.top()->endState();
			break;
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}
