#include "State.h"



State::State()
{
	quit = false;
}


State::~State()
{
}

void State::endState()
{
	this->quit = true;
}

bool State::getQuit()
{
	return this->quit;
}
