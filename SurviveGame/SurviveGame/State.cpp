#include "State.h"



State::State()
{
}


State::~State()
{
	delete states;
}

void State::updateMousePos()
{
	this->mouse_pos_view = (window)->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::endState()
{
	this->quit = true;
}

bool State::getQuit()
{
	return this->quit;
}
