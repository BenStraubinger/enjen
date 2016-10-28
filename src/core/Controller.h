#ifndef ENJEN_CONTROLLER_H
#define ENJEN_CONTROLLER_H


#include <string>
#include <vector>
#include <map>


enum DPadDirection: int {
	NW,      N,  NE,
	 W, CENTER,   E,
	SW,      S,  SE,
	UNKNOWN
};


class Controller
{

public:
	
	Controller();
	~Controller();
	
	bool CheckButton(std::string button_name);
	void UpdateButton(std::string button_name, bool pressed);

	DPadDirection CheckDPad(std::string dpad_name);
	void UpdateDPad(std::string dpad_name, DPadDirection direction);

	int CheckJoystick(std::string joystick_name);
	void UpdateJoystick(std::string joystick_name, int value);


private:
	
	std::map<std::string, bool> _buttons;
	std::map<std::string, DPadDirection> _dpads;
	std::map<std::string, int> _joysticks;

	int _joystick_deadzone = 1500;
	int _joystick_max_value = 31500;
	
};



#endif //ENJEN_CONTROLLER_H
