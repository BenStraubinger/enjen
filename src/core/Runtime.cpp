#include "core/Runtime.h"

#include "Enjen.h"
#include "core/Renderer.h"


#include <iostream>


Runtime::Runtime(Enjen* game)
	: _game(game),
	  _renderer(nullptr)
{
	std::cout << "Runtime::Runtime()" << std::endl;
}


Runtime::~Runtime()
{
	std::cout << "Runtime::~Runtime()" << std::endl;
}


bool Runtime::Startup()
{
	std::cout << "Runtime::CreateWindow()" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Runtime failed to init SDL2." << std::endl;
		return false;
	}

	_renderer = new Renderer(_game);
	if(!_renderer->CreateWindow())
	{
		std::cout << "Runtime failed to start the renderer." << std::endl;
		return false;
	}

	std::cout << "Runtime started the renderer." << std::endl;

	return true;
}


void Runtime::Shutdown()
{
	std::cout << "Runtime::CloseWindow()" << std::endl;

	_renderer->CloseWindow();
	delete _renderer;

	SDL_Quit();
}


bool Runtime::CreateWindow(unsigned int width, unsigned int height)
{
	if(_renderer != nullptr) {
		std::cout << "Runtime failed to create window, a window already exists." << std::endl;
		return false;
	}

	_renderer = new Renderer(_game);
	if(!_renderer->CreateWindow(width, height))
	{
		std::cout << "Runtime failed to start the renderer." << std::endl;
		return false;
	}

	std::cout << "Runtime started the renderer." << std::endl;
	return true;
}


void Runtime::CloseWindow()
{
	if(_renderer == nullptr) {
		std::cout << "Runtime failed to close window, no window currently exists." << std::endl;
		return;
	}

	_renderer->CloseWindow();
	delete _renderer;
	_renderer = nullptr;
}


void Runtime::Update()
{
	//std::cout << "Runtime::Run()" << std::endl;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			_game->Stop();
			return;
		}


		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			// quit game
			case SDLK_ESCAPE:
				_game->Stop();
				return;

			// set background colour: black
			case SDLK_1:
				_renderer->SetClearColour(0.0f, 0.0f, 0.0f);
				break;
			// set background colour: red
			case SDLK_2:
				_renderer->SetClearColour(1.0f, 0.0f, 0.0f);
				break;
			// set background colour: green
			case SDLK_3:
				_renderer->SetClearColour(0.0f, 1.0f, 0.0f);
				break;
			// set background colour: blue
			case SDLK_4:
				_renderer->SetClearColour(0.0f, 0.0f, 1.0f);
				break;
			// set background colour: white
			case SDLK_5:
				_renderer->SetClearColour(1.0f, 1.0f, 1.0f);
				break;

			// close and reopen the window at 1280x720
			case SDLK_COMMA:
				CloseWindow();
				SDL_Delay(250);
				CreateWindow(1280, 720);
				break;

			// close and reopen the window at 1440x900
			case SDLK_PERIOD:
				CloseWindow();
				SDL_Delay(250);
				CreateWindow(1440, 900);
				break;

			// ignore unexpected keys
			default:
				break;
			}
		}




		_renderer->ClearFrame();
		_renderer->ShowFrame();

	}
}



