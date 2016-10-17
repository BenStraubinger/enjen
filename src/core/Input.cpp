#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}


int Input::AddController()
{
	_controllers.push_back(std::make_unique<Controller>());
	return (int)_controllers.size() - 1;
}


int Input::ControllerCount()
{
	return (int)_controllers.size() - 1;
}


bool Input::CheckButton( unsigned int controller_id, std::string button_name )
{
	// ignore unknown controllers
	if(controller_id > ControllerCount()) {
		return false;
	}
	
	return _controllers[controller_id].get()->CheckButton(button_name);
}


void Input::UpdateButton( unsigned int controller_id, std::string button_name, bool pressed )
{
	// ignore unknown controllers
	if(controller_id > ControllerCount()) {
		return;
	}
	
	_controllers[controller_id].get()->UpdateButton(button_name, pressed);
}
