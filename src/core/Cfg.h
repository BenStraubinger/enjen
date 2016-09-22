#ifndef ENJEN_CFG_H
#define ENJEN_CFG_H


#include "json/json.h"


class Cfg
{

public:

	Cfg();
	~Cfg();

	bool LoadFile(std::string filename);
	bool SaveFile(std::string filename);

	Json::Value& GetRoot();


private:

	Json::Value _cfg;


};



#endif //ENJEN_CFG_H
