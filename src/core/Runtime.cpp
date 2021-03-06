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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
	{
		std::cerr << "Runtime failed to initialize SDL2." << std::endl;
		return false;
	}

	SDL_Joystick *ctrl;
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		ctrl = SDL_JoystickOpen(i);
		if (ctrl) {
			std::cout << "Runtime added joystick: " << SDL_JoystickNameForIndex(i) << std::endl <<
				"    - " << (SDL_JoystickNumAxes(ctrl) / 2) << " sticks" << std::endl <<
				"    - " << SDL_JoystickNumButtons(ctrl) << " buttons" << std::endl;
			_active_joysticks.push_back(ctrl);
		}
	}

	return true;
}


void Runtime::Shutdown()
{
	for (std::vector<SDL_Joystick*>::iterator it = _active_joysticks.begin(); it != _active_joysticks.end(); it++) {
		if (SDL_JoystickGetAttached(*it)) {
			std::cout << "Runtime removed joystick: " << SDL_JoystickName(*it) << std::endl;
			SDL_JoystickClose(*it);
		}
	}
	_active_joysticks.clear();
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
	bool button_pressed;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			std::cout << "CloseWindow event - Last Window " << std::endl;
			game->Stop();
			return;
		}


		if ( event.type != SDL_WINDOWEVENT && 
			event.type != SDL_KEYDOWN &&
			event.type != SDL_KEYUP &&
			event.type != SDL_MOUSEMOTION) {
			std::cout << "SDL Event: " << event.type << std::endl;
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
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat != 0) {
					break;
				}
				key_pressed = true;
			}
			else {
				key_pressed = false;
			}

			switch (event.key.keysym.sym)
			{

				// direction keys
			case SDLK_UP:
			case SDLK_w:
				if(key_pressed) {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::N);
				} else {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::CENTER);
				}
				break;
			case SDLK_DOWN:
			case SDLK_s:
				if(key_pressed) {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::S);
				} else {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::CENTER);
				}
				break;
			case SDLK_LEFT:
			case SDLK_a:
				if(key_pressed) {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::W);
				} else {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::CENTER);
				}
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				if(key_pressed) {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::E);
				} else {
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::CENTER);
				}
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


		if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP )
		{
			if (event.type == SDL_JOYBUTTONDOWN) {
				button_pressed = true;
			}
			else {
				button_pressed = false;
			}

			switch (event.jbutton.button)
			{
			// primary buttons
			case 0: // X
				game->UpdateControllerButton("P1", "B3", button_pressed);
				break;
			case 1: // A
				game->UpdateControllerButton("P1", "B1", button_pressed);
				break;
			case 2: // B
				game->UpdateControllerButton("P1", "B2", button_pressed);
				break;
			case 3: // Y
				game->UpdateControllerButton("P1", "B4", button_pressed);
				break;

			// start
			case 9:
				game->UpdateControllerButton("P1", "START", button_pressed);
				break;
			// back
			case 8:
				game->UpdateControllerButton("P1", "BACK", button_pressed);
				break;

			// ignore unexpected keys
			default:
				if (button_pressed) {
					std::cout << "Joystick button pressed: " << std::to_string(event.jbutton.button) << std::endl;
				}
				else {
					std::cout << "Joystick button released: " << std::to_string(event.jbutton.button) << std::endl;
				}
				
				break;
			}
		}


		if (event.type == SDL_JOYHATMOTION)
		{
			switch (event.jhat.value)
			{

				// dpad
				case SDL_HAT_CENTERED:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::CENTER);
					break;
				case SDL_HAT_UP:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::N);
					break;
				case SDL_HAT_RIGHTUP:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::NE);
					break;
				case SDL_HAT_RIGHT:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::E);
					break;
				case SDL_HAT_RIGHTDOWN:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::SE);
					break;
				case SDL_HAT_DOWN:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::S);
					break;
				case SDL_HAT_LEFTDOWN:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::SW);
					break;
				case SDL_HAT_LEFT:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::W);
					break;
				case SDL_HAT_LEFTUP:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::NW);
					break;

				// ignore unexpected keys
				default:
					game->UpdateControllerDPad("P1", "DPAD", DPadDirection::UNKNOWN);
					break;
			}
		}


		if (event.type == SDL_JOYAXISMOTION)
		{
			std::string joystick_name = "";
			switch (event.jaxis.axis)
			{
				case 0:
					joystick_name = "JOY0-X";
					break;

				case 1:
					joystick_name = "JOY0-Y";
					break;

				case 2:
					joystick_name = "JOY1-X";
					break;

				case 3:
					joystick_name = "JOY1-Y";
					break;

				default:
					break;
			}
			if (joystick_name != "") {
				game->UpdateControllerJoystick("P1", joystick_name, event.jaxis.value);
				std::cout << "Joystick Move Event - " << joystick_name << ": " << game->CheckControllerJoystick("P1", joystick_name) << std::endl;
			}
		}
	}
}





