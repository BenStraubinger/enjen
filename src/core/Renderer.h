#ifndef ENJEN_RENDERER_H
#define ENJEN_RENDERER_H


#define GLEW_STATIC
#include <GL/glew.h>

#include "SDL.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


#include <string>


// forward declarations:
class Enjen;


class Renderer
{

public:

	Renderer() = delete;
	Renderer(Enjen* game);

	~Renderer();

	bool CreateWindow(unsigned int width = 1280, unsigned int height = 720);
	void CloseWindow();

	void ClearFrame();
	void SetClearColour(float r, float g, float b);

	void ShowFrame();

	void LogGraphicsInfo();


private:

	Enjen *_game;

	SDL_Window *_window;
	SDL_GLContext _glContext;

	std::string _window_title;
	bool _window_border;
	glm::uvec2 _window_size;

	glm::vec3 _clear_colour;

	bool InitGraphics();

};



#endif //ENJEN_RENDERER_H
