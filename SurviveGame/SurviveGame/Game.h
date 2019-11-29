#pragma once
#include <SFML/Graphics.hpp>
#include"State.h"
#include "MainMenu.h"
#include <stack>

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void render();
	void processEvents();

	std::shared_ptr<sf::RenderWindow> window;
	std::stack<State*> states;

	sf::Clock dt_clock;
	sf::Time deltaTime;
};

