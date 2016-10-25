#include "Controller.h"


Controller::Controller()
{
}


Controller::~Controller()
{
}


bool Controller::CheckButton( std::string button_name )
{
	if(_buttons.count(button_name) > 0) {
		return _buttons[button_name];
	}
	return false;
}


void Controller::UpdateButton( std::string button_name, bool pressed )
{
	_buttons[button_name] = pressed;
}


DPadDirection Controller::CheckDPad( std::string dpad_name )
{
	if(_dpads.count(dpad_name) > 0) {
		return _dpads[dpad_name];
	}
	return DPadDirection::UNKNOWN;
}


void Controller::UpdateDPad( std::string dpad_name, DPadDirection direction )
{
	_dpads[dpad_name] = direction;
}




