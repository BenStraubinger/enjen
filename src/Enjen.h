#ifndef ENJEN_ENJEN_H
#define ENJEN_ENJEN_H


#define GLEW_STATIC
#include "GL/glew.h"

#include "SDL.h"

#include <string>
#include <memory>


// forward declarations:
class Cfg;
class Runtime;
class Renderer;
class Input;
class Controller;


class Enjen
{

public:

	Enjen();
	~Enjen();
	
	static Enjen* GetInstance();

	bool Startup();
	void Shutdown();
	
	bool CreateWindow();
	void CloseWindow();

	void Run();
	void Stop();
	
	void Sleep(unsigned int milliseconds);
	
	
	bool CheckControllerButton( std::string controller_id, std::string button_name );
	void UpdateControllerButton( std::string controller_id, std::string button_name, bool pressed );


private:
	
	// basic singleton
	static Enjen* _enjen;
	static bool SetInstance( Enjen *instance );
	
	// game state
	bool _run_game;
	
	
	std::unique_ptr<Cfg> _cfg;
	std::unique_ptr<Runtime> _rt;
	std::unique_ptr<Renderer> _renderer;
	std::unique_ptr<Input> _input;
	
};



#endif //ENJEN_ENJEN_H
