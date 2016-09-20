#include "core/Renderer.h"


#include "Enjen.h"


#include <iostream>


Renderer::Renderer(Enjen *game)
	: _game(game),
	  _window(nullptr),
	  _glContext(nullptr),
	  _window_size(1280, 720),
	  _clear_colour(0.0f, 0.0f, 0.0f)
{
	std::cout << "Renderer::Renderer()" << std::endl;
}


Renderer::~Renderer()
{
	std::cout << "Renderer::~Renderer()" << std::endl;
}


bool Renderer::CreateWindow(unsigned int width, unsigned int height)
{
	std::cout << "Renderer::CreateWindow()" << std::endl;

	_window_size.x = width;
	_window_size.y = height;

	std::cout << "Renderer creating window: "<< std::endl;
	_window = SDL_CreateWindow("enjen",
							   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							   _window_size.x, _window_size.y,
							   SDL_WINDOW_OPENGL);

	if (!_window)
	{
		std::cout << "Renderer failed to create window: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "Renderer created the window. "<< std::endl;

	_glContext = SDL_GL_CreateContext(_window);
	if (!_glContext)
	{
		std::cout << "Renderer failed to create GL context: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!InitGraphics())
	{
		std::cout << "Renderer failed to initialize graphics settings. " << std::endl;
		return false;
	}

	ClearFrame();
	ShowFrame();

	LogGraphicsInfo();
	return true;
}


void Renderer::CloseWindow()
{
	std::cout << "Renderer::CloseWindow()" << std::endl;

	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
}


void Renderer::ClearFrame()
{
	glClearColor(_clear_colour.r, _clear_colour.g, _clear_colour.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::SetClearColour( float r, float g, float b )
{
	// clamp values between 0 and 1
	if(r < 0.0f) r = 0.0f;
	if(r > 1.0f) r = 1.0f;
	if(g < 0.0f) g = 0.0f;
	if(g > 1.0f) g = 1.0f;
	if(b < 0.0f) b = 0.0f;
	if(b > 1.0f) b = 1.0f;

	_clear_colour.r = r;
	_clear_colour.g = g;
	_clear_colour.b = b;
}



void Renderer::ShowFrame()
{
	SDL_GL_SwapWindow(_window);
}


void Renderer::LogGraphicsInfo()
{
	std::cout << "Runtime::LogGraphicsInfo()" << std::endl;

	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &value);
	if(value & SDL_GL_CONTEXT_PROFILE_CORE) {
		std::cout << "SDL_GL_CONTEXT_PROFILE_CORE: yes" << std::endl;
	} else {
		std::cout << "SDL_GL_CONTEXT_PROFILE_CORE: no" << std::endl;
	}

	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value);
	std::cout << "SDL_GL_DOUBLEBUFFER: " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
	std::cout << "SDL_GL_DEPTH_SIZE: " << value << std::endl;

	value = SDL_GL_GetSwapInterval();
	if(value) {
		std::cout << "VSync: yes" << std::endl;
	} else {
		std::cout << "VSync: no" << std::endl;
	}
}


bool Renderer::InitGraphics()
{
	int failure = 0;
	failure |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	failure |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	failure |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	failure |= SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	failure |= SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// enable VSync
	failure |= SDL_GL_SetSwapInterval(1);

	if(failure) {
		std::cout << "Renderer failed to set GL attributes." << std::endl;
		return false;
	}

	glewExperimental = GL_TRUE;
	failure |= glewInit();

	if(failure) {
		std::cout << "Renderer failed to initialize GLEW." << std::endl;
		return false;
	}

	return true;
}










