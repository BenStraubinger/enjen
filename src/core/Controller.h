#ifndef ENJEN_CONTROLLER_H
#define ENJEN_CONTROLLER_H


#include <string>
#include <vector>
#include <map>


class Controller
{

public:
	
	Controller();
	~Controller();
	
	bool CheckButton(std::string button_name);
	void UpdateButton(std::string button_name, bool pressed);


private:
	
	std::map<std::string,bool> _buttons;
	
};



#endif //ENJEN_CONTROLLER_H
