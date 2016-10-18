#include "Enjen.h"


#include "core/Cfg.h"
#include "core/Runtime.h"
#include "core/Renderer.h"
#include "core/Input.h"


#include <iostream>

#include <chrono>
#include <thread>


Enjen* Enjen::_enjen = nullptr;


Enjen::Enjen()
	: _run_game(false),
	  _cfg(nullptr),
	  _rt(nullptr),
	  _renderer(nullptr),
	  _input(nullptr)
{
}


Enjen::~Enjen()
{
}


bool Enjen::Startup()
{
	_cfg = std::make_unique<Cfg>();
	if( ! _cfg->LoadFile("cfg/config.json") ) {
		std::cerr << "Enjen failed to load config file." << std::endl;
		return false;
	}

	_rt = std::make_unique<Runtime>();
	if(! _rt->Startup()) {
		std::cerr << "Enjen failed to start the runtime." << std::endl;
		return false;
	}
	
	_input = std::make_unique<Input>();
	int controller_id = _input->AddController();
	std::cout << "Enjen added input controller: " << controller_id << std::endl;
	
	Enjen::Set(this);

	return true;
}


void Enjen::Shutdown()
{
	CloseWindow();
	
	if (_rt) {
		_rt->Shutdown();
	}
	_rt = nullptr;
	
	_cfg = nullptr;
}


bool Enjen::CreateWindow()
{
	if (_renderer) {
		std::cerr << "Enjen already created the window." << std::endl;
		return false;
	}
	
	_renderer = _rt->CreateWindow("enjen - test");
	if(! _renderer) {
		std::cerr << "Enjen failed to create the window." << std::endl;
		return false;
	}
	return true;
}


void Enjen::CloseWindow()
{
	if (_renderer) {
		_renderer->CloseWindow();
	}
	_renderer = nullptr;
}


void Enjen::Run()
{	
	_run_game = true;
	while ( _run_game ) {
		
		_rt->Update();
		if(_input->CheckButton(0, "BACK")) {
			std::cout << "Enjen stopping - BACK button pressed." << std::endl;
			Stop();
			break;
		}
		if(_input->CheckButton(0, "B1")) {
			std::cout << "B1 button pressed." << std::endl;
			_renderer->SetClearColour(0.0f, 0.0f, 0.0f);
		}
		if(_input->CheckButton(0, "B2")) {
			std::cout << "B2 button pressed." << std::endl;
			_renderer->SetClearColour(1.0f, 0.0f, 0.0f);
		}
		if(_input->CheckButton(0, "B3")) {
			std::cout << "B3 button pressed." << std::endl;
			_renderer->SetClearColour(0.0f, 1.0f, 0.0f);
		}
		if(_input->CheckButton(0, "B4")) {
			std::cout << "B4 button pressed." << std::endl;
			_renderer->SetClearColour(0.0f, 0.0f, 1.0f);
		}

		_renderer->ClearFrame();
		_renderer->ShowFrame();
	}
	
	std::cout << "Enjen finished running." << std::endl;
}


void Enjen::Stop()
{
	_run_game = false;
}


Enjen *Enjen::Get()
{
	return _enjen;
}


bool Enjen::Set( Enjen *instance )
{
	// nullptr clears the current instance
	if(instance == nullptr) {
		_enjen = nullptr;
		return true;
	}
	
	// prevent overriding an existing instance
	if(_enjen != nullptr) {
		std::cerr << "Enjen instance already set." << std::endl;
		return false;
	}
	
	// set the current instance
	_enjen = instance;
	return true;
}


void Enjen::Sleep( unsigned int milliseconds )
{
	std::cout << "Sleeping for " << milliseconds << " milliseconds..." << std::endl;
	
	std::chrono::duration<unsigned int, std::milli> delta(milliseconds);
	std::this_thread::sleep_for(delta);
	
	std::cout << "Done." << std::endl;
}


bool Enjen::CheckControllerButton( unsigned int controller_id, std::string button_name )
{
	if(controller_id < _input->ControllerCount()) {
		return false;
	}
	return _input->CheckButton(controller_id, button_name);
}


void Enjen::UpdateControllerButton( unsigned int controller_id, std::string button_name, bool pressed )
{
	if(controller_id < _input->ControllerCount()) {
		return;
	}
	_input->UpdateButton(controller_id, button_name, pressed);
}