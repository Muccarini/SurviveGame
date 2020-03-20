#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class State
{
public:
	State();
	virtual ~State();

	virtual void update(const sf::Time& delta_time) = 0;
	virtual void render() = 0;

	void endState();

	bool getQuit();

	std::stack<State*> *states;
	std::shared_ptr<sf::RenderWindow> window;

protected:
	void updateMousePos();
	sf::Vector2f mouse_pos_view;

private:
	bool quit;
};

