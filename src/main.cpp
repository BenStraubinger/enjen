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
	
	if (!game.LoadScene()) {
		return 3;
	}
	
	game.Run();

	game.Shutdown();

	return 0;
}
