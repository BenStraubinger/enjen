#ifndef ENJEN_ENJEN_H
#define ENJEN_ENJEN_H


#define GLEW_STATIC
#include <GL/glew.h>

#include "SDL.h"


// forward declarations:
class Cfg;
class Runtime;


class Enjen
{

public:

	Enjen();
	~Enjen();

	Cfg* GetCfg();

	bool Startup();
	void Shutdown();

	void Run();
	void Stop();


private:

	Cfg *_cfg;
	Runtime *_rt;

	bool _run_game;

};



#endif //ENJEN_ENJEN_H
