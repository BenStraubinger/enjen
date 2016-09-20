#include "Enjen.h"


int main(int argc, char *argv[])
{
	Enjen game;
	if (!game.Startup()) {
		return -1;
	}

	game.Run();

	game.Shutdown();

	return 0;
}