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
	auto game = Enjen::GetInstance();
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
				if(event.key.repeat != 0) {
					break;
				}
				key_pressed = true;
			} else {
				key_pressed = false;
			}
			
			switch (event.key.keysym.sym)
			{
			
			// direction keys
			case SDLK_UP:
			case SDLK_w:
				game->UpdateControllerButton("P1", "UP", key_pressed);
				break;
			case SDLK_DOWN:
			case SDLK_s:
				game->UpdateControllerButton("P1", "DOWN", key_pressed);
				break;
			case SDLK_LEFT:
			case SDLK_a:
				game->UpdateControllerButton("P1", "LEFT", key_pressed);
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				game->UpdateControllerButton("P1", "RIGHT", key_pressed);
				break;
				
			// start
			case SDLK_RETURN:
				game->UpdateControllerButton("P1", "START", key_pressed);
				break;
			// back
			case SDLK_ESCAPE:
				game->UpdateControllerButton("P1", "BACK", key_pressed);
				break;
				
			// primary buttons
			case SDLK_SPACE:
			case SDLK_SLASH:
				game->UpdateControllerButton("P1", "B1", key_pressed);
				break;
			case SDLK_LCTRL:
			case SDLK_COMMA:
				game->UpdateControllerButton("P1", "B2", key_pressed);
				break;
			case SDLK_LALT:
			case SDLK_PERIOD:
				game->UpdateControllerButton("P1", "B3", key_pressed);
				break;
			case SDLK_LSHIFT:
			case SDLK_m:
				game->UpdateControllerButton("P1", "B4", key_pressed);
				break;

			// dev-mode keys
			case SDLK_1:
				game->UpdateControllerButton("DEV", "1", key_pressed);
				break;
			case SDLK_2:
				game->UpdateControllerButton("DEV", "2", key_pressed);
				break;
			case SDLK_3:
				game->UpdateControllerButton("DEV", "3", key_pressed);
				break;
			case SDLK_4:
				game->UpdateControllerButton("DEV", "4", key_pressed);
				break;
			case SDLK_5:
				game->UpdateControllerButton("DEV", "5", key_pressed);
				break;

			// ignore unexpected keys
			default:
				break;
			}
		}
	}
}





