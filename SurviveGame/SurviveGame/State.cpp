#include "State.h"



State::State()
{
}


State::~State()
{
}

void State::updateMousePos()
{
	mouse_pos_view = (window)->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::endState()
{
	this->quit = true;
}

bool State::getQuit()
{
	return this->quit;
}
