#include "core/Renderer.h"


#include "Enjen.h"
#include "core/Cfg.h"


#include <iostream>


Renderer::Renderer()
	: _sdlWindow(nullptr),
	  _glContext(nullptr),
	  _clear_colour(0.0f, 0.0f, 0.0f)
{
}


Renderer::~Renderer()
{
}


bool Renderer::CreateWindow(std::string title, unsigned int width, unsigned int height, bool border)
{
	Uint32 sdl_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

	if (! border) {
		sdl_flags |= SDL_WINDOW_BORDERLESS;
	}

	_sdlWindow = SDL_CreateWindow(title.c_str(),
							   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							   width, height,
							   sdl_flags);

	if (!_sdlWindow)
	{
		std::cerr << "Renderer failed to create SDL_Window: " << SDL_GetError() << std::endl;
		return false;
	}

	_glContext = SDL_GL_CreateContext(_sdlWindow);
	if (!_glContext)
	{
		std::cerr << "Renderer failed to create OpenGL context: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!InitGraphics())
	{
		std::cerr << "Renderer failed to set up the window. " << std::endl;
		return false;
	}

	ClearFrame();
	ShowFrame();

	LogGraphicsInfo();
	return true;
}


void Renderer::CloseWindow()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_sdlWindow);
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
	SDL_GL_SwapWindow(_sdlWindow);
}


void Renderer::LogGraphicsInfo()
{
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
		std::cerr << "Renderer failed to set OpenGL attributes." << std::endl;
		return false;
	}

	glewExperimental = GL_TRUE;
	failure |= glewInit();

	if(failure) {
		std::cerr << "Renderer failed to initialize GLEW." << std::endl;
		return false;
	}

	return true;
}