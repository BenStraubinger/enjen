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
	
	controller_id = "DEV";
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


bool Enjen::LoadScene()
{
	std::cout << "Enjen setting up the scene..." << std::endl;
	
	
	if(! _renderer->LoadShader("default", "shaders/vertex/default.glsl", "shaders/fragment/default.glsl")) {
		std::cerr << "Enjen failed to load default shader." << std::endl;
		return false;
	}
	std::cout << "Enjen loaded default shader." << std::endl;
	
	
	// V1: position
	_vertices[0] =  0.5f;
	_vertices[1] = -0.5f;
	_vertices[2] =  0.0f;
	// V1: color
	_vertices[3] = 1.0f;
	_vertices[4] = 0.0f;
	_vertices[5] = 0.0f;
	
	// V2: position
	_vertices[6] = -0.5f;
	_vertices[7] = -0.5f;
	_vertices[8] =  0.0f;
	// V2: color
	_vertices[9]  = 0.0f;
	_vertices[10] = 1.0f;
	_vertices[11] = 0.0f;
	
	// V3: position
	_vertices[12] = 0.0f;
	_vertices[13] = 0.5f;
	_vertices[14] = 0.0f;
	// V3: color
	_vertices[15] = 0.0f;
	_vertices[16] = 0.0f;
	_vertices[17] = 1.0f;
	
	
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0); // Unbind VAO
	
	
	std::cout << "Enjen finished setting up the scene." << std::endl;
	return true;
}


void Enjen::DrawScene()
{
	_renderer->ClearFrame();
	
	
	_renderer->UseShader("default");
	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	
	
	_renderer->ShowFrame();
}


bool Enjen::UnloadScene()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	return true;
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
		
		if(_input->CheckDPad("P1", "DPAD") == DPadDirection::N) {
			std::cout << "DPad UP pressed." << std::endl;
			_renderer->SetClearColour(0.3f, 0.6f, 0.9f);
		}
		
		//
		// TEST - handle developer-mode input:
		//
		
		if(_input->CheckButton("DEV", "1")) {
			std::cout << "DEV: button 1 pressed." << std::endl;
			_renderer->SetClearColour(1.0f, 1.0f, 1.0f);
		}

		
		//
		// Render the scene:
		//
		
		DrawScene();
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


DPadDirection Enjen::CheckControllerDPad( std::string controller_id, std::string dpad_name )
{
	if(! _input->HasController(controller_id)) {
		return DPadDirection::UNKNOWN;
	}
	return _input->CheckDPad(controller_id, dpad_name);
}


void Enjen::UpdateControllerDPad( std::string controller_id, std::string dpad_name, DPadDirection direction )
{
	if(! _input->HasController(controller_id)) {
		return;
	}
	_input->UpdateDPad(controller_id, dpad_name, direction);
}
