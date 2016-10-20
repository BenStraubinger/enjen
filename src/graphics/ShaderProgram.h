#ifndef ENJEN_SHADERPROGRAM_H
#define ENJEN_SHADERPROGRAM_H


#define GLEW_STATIC
#include "GL/glew.h"

#include "SDL.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


#include <string>


class ShaderProgram
{

public:
	
	ShaderProgram();
	~ShaderProgram();
	
	GLuint ID();
	bool Loaded();
	
	bool Load( std::string vert_shader_filename, std::string frag_shader_filename );
	
	void Use();


private:
	
	bool _loaded;
	
	GLuint _id;
	
	GLuint _vert_id;
	GLuint _frag_id;
	
};



#endif //ENJEN_SHADERPROGRAM_H
