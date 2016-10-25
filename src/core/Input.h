#ifndef ENJEN_INPUT_H
#define ENJEN_INPUT_H


#include "core/Controller.h"


#include <memory>
#include <string>
#include <vector>
#include <map>


class Input
{

public:
	
	Input();
	~Input();
	
	bool AddController( std::string controller_id );
	bool HasController( std::string controller_id );
	
	bool CheckButton( std::string controller_id, std::string button_name );
	void UpdateButton( std::string controller_id, std::string button_name, bool pressed );
	DPadDirection CheckDPad( std::string controller_id, std::string dpad_name );
	void UpdateDPad( std::string controller_id, std::string dpad_name, DPadDirection direction);


private:
	
	std::map<std::string,std::unique_ptr<Controller>> _controllers;
	
	
};


#endif //ENJEN_INPUT_H