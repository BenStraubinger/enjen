#include "Enjen.h"


#include "core/Cfg.h"
#include "core/Runtime.h"


#include <iostream>


Enjen::Enjen()
	: _rt(nullptr),
	  _run_game(false)
{
}


Enjen::~Enjen()
{
}


bool Enjen::Startup()
{
	_cfg = new Cfg();
	if( ! _cfg->LoadFile("config.json") ) {
		std::cerr << "Enjen failed to load config file." << std::endl;
		return false;
	}

	_rt = new Runtime(this);
	if(! _rt->Startup()) {
		std::cerr << "Enjen failed to start the runtime." << std::endl;
		return false;
	}

	return true;
}


void Enjen::Shutdown()
{
	_rt->Shutdown();
	delete _rt;
}


void Enjen::Run()
{
	for(_run_game = true; _run_game; ) {

		_rt->Update();

	}
}


void Enjen::Stop()
{
	_run_game = false;
}


Cfg *Enjen::GetCfg()
{
	return _cfg;
}















