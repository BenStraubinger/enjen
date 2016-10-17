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
	
	int AddController();
	int ControllerCount();
	
	bool CheckButton( unsigned int controller_id, std::string button_name );
	void UpdateButton( unsigned int controller_id, std::string button_name, bool pressed );


private:
	
	std::vector<std::unique_ptr<Controller>> _controllers;
	
	
};


#endif //ENJEN_INPUT_H