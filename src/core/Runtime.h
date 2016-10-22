#ifndef ENJEN_RUNTIME_H
#define ENJEN_RUNTIME_H


#define GLEW_STATIC
#include "GL/glew.h"

#include "SDL.h"

#include <string>
#include <memory>
#include <vector>


// forward declarations:
class Enjen;
class Renderer;


class Runtime
{

public:

	Runtime();
	~Runtime();

	bool Startup();
	void Shutdown();

	std::unique_ptr<Renderer> CreateWindow(std::string title, unsigned int width = 1280, unsigned int height = 720, bool show_border = true);

	void Update();


private:

	std::vector<SDL_Joystick*> _active_joysticks;

};



#endif //ENJEN_RUNTIME_H