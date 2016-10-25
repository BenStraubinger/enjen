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


private:
	
	std::map<std::string,bool> _buttons;
	std::map<std::string,DPadDirection> _dpads;
	
};



#endif //ENJEN_CONTROLLER_H
