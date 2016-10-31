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


int Controller::CheckJoystick(std::string joystick_name)
{
	if (_joysticks.count(joystick_name) > 0) {
		return _joysticks[joystick_name];
	}
	return 0;
}


void Controller::UpdateJoystick(std::string joystick_name, int value)
{
	// normalize joystick value
	if (value >= 0) {
		if (value < _joystick_deadzone) {
			value = 0;
		} else if (value > _joystick_max_value) {
			value = _joystick_max_value;
		}
	} else {
		if (value > (0 - _joystick_deadzone)) {
			value = 0;
		}
		else if (value < (0 - _joystick_max_value)) {
			value = 0 - _joystick_max_value;
		}
	}

	_joysticks[joystick_name] = value;
}

