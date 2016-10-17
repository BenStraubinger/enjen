#include "Enjen.h"


int main(int argc, char *argv[])
{
	Enjen game;

	if (!game.Startup()) {
		return 1;
	}
	
	if (!game.CreateWindow()) {
		return 2;
	}
	
	game.Run();

	game.Shutdown();

	return 0;
}
