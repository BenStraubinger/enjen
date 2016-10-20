#include "Cfg.h"


#include <fstream>
#include <iostream>


Cfg::Cfg()
	: _cfg(Json::objectValue)
{
}


Cfg::~Cfg()
{
}


bool Cfg::LoadFile( std::string filename )
{

	std::ifstream cfg_file(filename);
	if (! cfg_file.is_open()) {
		std::cerr << "Cfg failed to open file: " << filename << std::endl;
		return false;
	}

	Json::Value cfg_object;

	std::string parse_error;

	Json::CharReaderBuilder json_builder;
	json_builder["allowComments"] = true;
	json_builder["collectComments"] = true;
	json_builder["strictRoot"] = true;
	json_builder["allowSingleQuotes"] = true;
	json_builder["rejectDupKeys"] = true;

	if( ! Json::parseFromStream(json_builder, cfg_file, &cfg_object, &parse_error) ) {
		std::cerr << "Cfg failed to parse file: " << filename << std::endl;
		return false;
	}

	if (cfg_file.is_open()) {
		cfg_file.close();
	}

	// replace the current config data
	_cfg = cfg_object;

	return true;
}


bool Cfg::SaveFile( std::string filename )
{
	return false;
}


Json::Value& Cfg::GetRoot()
{
	return _cfg;
}