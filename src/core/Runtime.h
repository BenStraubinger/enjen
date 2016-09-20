#ifndef ENJEN_RUNTIME_H
#define ENJEN_RUNTIME_H


#define GLEW_STATIC
#include <GL/glew.h>

#include "SDL.h"


// forward declarations:
class Enjen;
class Renderer;


class Runtime
{

public:

	Runtime() = delete;
	Runtime(Enjen* _game);
	~Runtime();

	bool Startup();
	void Shutdown();

	bool CreateWindow(unsigned int width = 1280, unsigned int height = 720);
	void CloseWindow();

	void Update();


private:

	Enjen *_game;
	Renderer *_renderer;

};



#endif //ENJEN_RUNTIME_H
