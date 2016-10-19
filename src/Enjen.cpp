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
	std::string controller_id = "P1";
	_input->AddController( controller_id );
	std::cout << "Enjen added input controller: " << controller_id << std::endl;
	
	Enjen::SetInstance( this );

	return true;
}


void Enjen::Shutdown()
{
	CloseWindow();
	
	_input = nullptr;
	
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
	
	std::string title = "enjen";
	unsigned int width = 1280;
	unsigned int height = 720;
	bool border = true;
	
	auto cfg = _cfg->GetRoot();
	if(cfg.isObject()) {
		if(cfg.isMember("window") && cfg["window"].isObject()) {
			if(cfg["window"].isMember("title") && cfg["window"]["title"].isString()) {
				title = cfg["window"]["title"].asString();
			}
			if(cfg["window"].isMember("width") && cfg["window"]["width"].isUInt()) {
				width = cfg["window"]["width"].asUInt();
			}
			if(cfg["window"].isMember("height") && cfg["window"]["height"].isUInt()) {
				height = cfg["window"]["height"].asUInt();
			}
			if(cfg["window"].isMember("border") && cfg["window"]["border"].isBool()) {
				border = cfg["window"]["border"].asBool();
			}
		}
	}
	
	_renderer = _rt->CreateWindow(title, width, height, border);
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
	std::cout << "Enjen running..." << std::endl;
	
	_run_game = true;
	while ( _run_game ) {
		
		//
		// Update the state of the runtime:
		//
		
		_rt->Update();
		
		
		//
		// TEST - handle player input:
		//
		
		if(_input->CheckButton("P1", "BACK")) {
			std::cout << "Enjen stopping - BACK button pressed." << std::endl;
			Stop();
			break;
		}
		
		if(_input->CheckButton("P1", "B1")) {
			std::cout << "B1 button pressed." << std::endl;
			_renderer->SetClearColour(0.0f, 0.0f, 0.0f);
		}
		if(_input->CheckButton("P1", "B2")) {
			std::cout << "B2 button pressed." << std::endl;
			_renderer->SetClearColour(1.0f, 0.0f, 0.0f);
		}
		if(_input->CheckButton("P1", "B3")) {
			std::cout << "B3 button pressed." << std::endl;
			_renderer->SetClearColour(0.0f, 1.0f, 0.0f);
		}
		if(_input->CheckButton("P1", "B4")) {
			std::cout << "B4 button pressed." << std::endl;
			_renderer->SetClearColour(0.0f, 0.0f, 1.0f);
		}
		
		
		//
		// TEST - handle developer-mode input:
		//
		
		if(_input->CheckButton("P1", "DEV1")) {
			std::cout << "DEV1 button pressed." << std::endl;
			_renderer->SetClearColour(1.0f, 1.0f, 1.0f);
		}

		
		//
		// Render the scene:
		//
		
		_renderer->ClearFrame();
		_renderer->ShowFrame();
	}
	
	std::cout << "Enjen finished running." << std::endl;
}


void Enjen::Stop()
{
	_run_game = false;
}


Enjen *Enjen::GetInstance()
{
	return _enjen;
}


bool Enjen::SetInstance( Enjen *instance )
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


bool Enjen::CheckControllerButton( std::string controller_id, std::string button_name )
{
	if(! _input->HasController(controller_id)) {
		return false;
	}
	return _input->CheckButton(controller_id, button_name);
}


void Enjen::UpdateControllerButton( std::string controller_id, std::string button_name, bool pressed )
{
	if(! _input->HasController(controller_id)) {
		return;
	}
	_input->UpdateButton(controller_id, button_name, pressed);
}