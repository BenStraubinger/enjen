#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}


bool Input::AddController( std::string controller_id )
{
	// prevent duplicates
	if(HasController(controller_id)) {
		return false;
	}
	_controllers[controller_id] = std::make_unique<Controller>();
	return true;
}


bool Input::HasController( std::string controller_id )
{
	if(_controllers.count(controller_id) > 0) {
		return true;
	};
	return false;
}


bool Input::CheckButton( std::string controller_id, std::string button_name )
{
	// ignore unknown controllers
	if(! HasController(controller_id)) {
		return false;
	}
	
	return _controllers[controller_id].get()->CheckButton(button_name);
}


void Input::UpdateButton( std::string controller_id, std::string button_name, bool pressed )
{
	// ignore unknown controllers
	if(! HasController(controller_id)) {
		return;
	}
	
	_controllers[controller_id].get()->UpdateButton(button_name, pressed);
}
