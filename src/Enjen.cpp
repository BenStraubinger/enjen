#include "Enjen.h"

#include "core/Runtime.h"


#include <iostream>


Enjen::Enjen()
	: _rt(nullptr),
	  _run_game(false)
{
	std::cout << "Enjen::Enjen()" << std::endl;
}


Enjen::~Enjen()
{
	std::cout << "Enjen::~Enjen()" << std::endl;
}


bool Enjen::Startup()
{
	std::cout << "Enjen::CreateWindow()" << std::endl;

	_rt = new Runtime(this);
	if(! _rt->Startup()) {
		std::cout << "Enjen failed to start the runtime." << std::endl;
		return false;
	}

	return true;
}


void Enjen::Shutdown()
{
	std::cout << "Enjen::CloseWindow()" << std::endl;

	_rt->Shutdown();
	delete _rt;
}


void Enjen::Run()
{
	std::cout << "Enjen::Run()" << std::endl;

	for(_run_game = true; _run_game; ) {

		_rt->Update();

	}

}


void Enjen::Stop()
{
	_run_game = false;
}













