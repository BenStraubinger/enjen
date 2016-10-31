#include "ShaderProgram.h"


#include <fstream>
#include <iostream>


ShaderProgram::ShaderProgram()
	: _loaded(false),
	  _id(0)
{
}


ShaderProgram::~ShaderProgram()
{
}


GLuint ShaderProgram::ID()
{
	return _id;
}


bool ShaderProgram::Loaded()
{
	return _loaded;
}


bool ShaderProgram::Load( std::string vert_shader_filename, std::string frag_shader_filename )
{
	if(_id) {
		std::cerr << "ShaderProgram already loaded." << std::endl;
		return false;
	}
	
	std::string vert_file_data = "";
	std::string frag_file_data = "";
	std::string line = "";
	
	GLint success;
	GLchar error_log[1024];
	
	
	std::ifstream vert_shader_file(vert_shader_filename);
	if (! vert_shader_file.is_open()) {
		std::cerr << "ShaderProgram failed to open vertex shader file: " << vert_shader_filename << std::endl;
		return false;
	}
	while ( getline(vert_shader_file, line) )
	{
		vert_file_data += line + "\n";
	}
	vert_shader_file.close();
	
	std::cout << "ShaderProgram loaded vertex shader file: " << vert_shader_filename << std::endl;
	
	
	std::ifstream frag_shader_file(frag_shader_filename);
	if (! frag_shader_file.is_open()) {
		std::cerr << "ShaderProgram failed to open fragment shader file: " << frag_shader_filename << std::endl;
		return false;
	}
	while ( getline(frag_shader_file, line) )
	{
		frag_file_data += line + "\n";
	}
	frag_shader_file.close();
	
	std::cout << "ShaderProgram loaded fragment shader file: " << frag_shader_filename << std::endl;
	
	
	const GLchar* vert_shader_src = vert_file_data.c_str();
	_vert_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vert_id, 1, &vert_shader_src, NULL);
	glCompileShader(_vert_id);
	glGetShaderiv(_vert_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(_vert_id, 1024, NULL, error_log);
		std::cout << "ShaderProgram failed to compile vertex shader: " << error_log << std::endl;
		return false;
	};
	
	
	const GLchar* frag_shader_src = frag_file_data.c_str();
	_frag_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_frag_id, 1, &frag_shader_src, NULL);
	glCompileShader(_frag_id);
	glGetShaderiv(_frag_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(_frag_id, 1024, NULL, error_log);
		std::cout << "ShaderProgram failed to compile fragment shader: " << error_log << std::endl;
		return false;
	};
	
	
	_id = glCreateProgram();
	glAttachShader(_id, _vert_id);
	glAttachShader(_id, _frag_id);
	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(_id, 1024, NULL, error_log);
		std::cout << "ShaderProgram failed to link compiled shaders: " << error_log << std::endl;
		glDeleteShader(_vert_id);
		glDeleteShader(_frag_id);
		return false;
	}
	
	glDeleteShader(_vert_id);
	glDeleteShader(_frag_id);
	
	std::cout << "ShaderProgram loaded with id: " << _id << std::endl;
	return true;
}


void ShaderProgram::Use()
{
	if(_id) {
		glUseProgram(_id);
	}
}
