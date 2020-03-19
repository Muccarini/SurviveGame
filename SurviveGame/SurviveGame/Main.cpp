#define _CRTDBG_MAP_ALLOC
#include "Game.h"
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game;
	game.run();

	_CrtDumpMemoryLeaks();
	return 0;
}