#include "core/Runtime.h"

#include "Enjen.h"
#include "core/Renderer.h"
//#include "core/Window.h"


#include <iostream>


Runtime::Runtime()
{
}


Runtime::~Runtime()
{
}


bool Runtime::Startup()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Runtime failed to initialize SDL2." << std::endl;
		return false;
	}

	return true;
}


void Runtime::Shutdown()
{
	SDL_Quit();
}


std::unique_ptr<Renderer> Runtime::CreateWindow(std::string title, unsigned int width, unsigned int height, bool show_border)
{
	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	if(!renderer->CreateWindow(title, width, height, show_border))
	{
		std::cerr << "Runtime failed to create the window." << std::endl;
		return nullptr;
	}

	return std::move(renderer);
}



void Runtime::Update()
{
	auto game = Enjen::Get();
	if (! game) {
		std::cerr << "Runtime failed to get a pointer to the game instance." << std::endl;
		return;
	}
	
	SDL_Event event;
	bool key_pressed;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			std::cout << "CloseWindow event - Last Window " << std::endl;
			game->Stop();
			return;
		}
		
		
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
			std::cout << "CloseWindow event." << std::endl;
		}
		
		
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			int width = event.window.data1;
			int height = event.window.data2;
			std::cout << "Window resize event: " << width << "x" << height << std::endl;
		}


		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if(event.type == SDL_KEYDOWN) {
				key_pressed = true;
			} else {
				key_pressed = false;
			}
			
			switch (event.key.keysym.sym)
			{
			
			// direction keys
			case SDLK_UP:
			case SDLK_w:
				game->UpdateControllerButton(0, "UP", key_pressed);
				break;
			case SDLK_DOWN:
			case SDLK_s:
				game->UpdateControllerButton(0, "DOWN", key_pressed);
				break;
			case SDLK_LEFT:
			case SDLK_a:
				game->UpdateControllerButton(0, "LEFT", key_pressed);
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				game->UpdateControllerButton(0, "RIGHT", key_pressed);
				break;
				
			// start
			case SDLK_RETURN:
				game->UpdateControllerButton(0, "START", key_pressed);
				break;
			// back
			case SDLK_ESCAPE:
				game->UpdateControllerButton(0, "BACK", key_pressed);
				break;
				
			//
			case SDLK_SPACE:
			case SDLK_SLASH:
				game->UpdateControllerButton(0, "B1", key_pressed);
				break;
			//
			case SDLK_LCTRL:
			case SDLK_COMMA:
				game->UpdateControllerButton(0, "B2", key_pressed);
				break;
			//
			case SDLK_LALT:
			case SDLK_PERIOD:
				game->UpdateControllerButton(0, "B3", key_pressed);
				break;
			//
			case SDLK_LSHIFT:
			case SDLK_m:
				game->UpdateControllerButton(0, "B4", key_pressed);
				break;

			// dev-mode keys
			case SDLK_1:
				game->UpdateControllerButton(0, "D1", key_pressed);
				break;
			case SDLK_2:
				game->UpdateControllerButton(0, "D2", key_pressed);
				break;
			case SDLK_3:
				game->UpdateControllerButton(0, "D3", key_pressed);
				break;
			case SDLK_4:
				game->UpdateControllerButton(0, "D4", key_pressed);
				break;
			case SDLK_5:
				game->UpdateControllerButton(0, "D5", key_pressed);
				break;

			// ignore unexpected keys
			default:
				break;
			}
		}
	}
}





