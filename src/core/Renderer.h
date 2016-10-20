#ifndef ENJEN_RENDERER_H
#define ENJEN_RENDERER_H


#define GLEW_STATIC
#include "GL/glew.h"

#include "SDL.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


#include <string>
#include <map>
#include <memory>


// forward declarations:
class Enjen;
class ShaderProgram;

using ShaderMap = std::map<std::string,std::unique_ptr<ShaderProgram>>;


class Renderer
{

public:

	Renderer();
	~Renderer();

	bool CreateWindow(std::string title, unsigned int width, unsigned int height, bool show_border = true);
	void CloseWindow();

	void ClearFrame();
	void SetClearColour(float r, float g, float b);

	void ShowFrame();

	void LogGraphicsInfo();
	
	bool LoadShader( std::string shader_id, std::string vert_shader_filename, std::string frag_shader_filename );
	bool UseShader( std::string shader_id );


private:

	SDL_Window *_sdlWindow;
	SDL_GLContext _glContext;

	glm::vec3 _clear_colour;
	
	ShaderMap _shaders;
	

	bool InitGraphics( bool vsync = true );

};


#endif //ENJEN_RENDERER_H