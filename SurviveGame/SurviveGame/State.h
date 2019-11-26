#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class State
{
public:
	State();
	virtual ~State();

	virtual void update(sf::Time deltaTime) = 0;
	virtual void render() = 0;

	void endState();
	bool getQuit();

	std::stack<State*>* states;
	sf::RenderWindow* window;
private:
	bool quit;
};

