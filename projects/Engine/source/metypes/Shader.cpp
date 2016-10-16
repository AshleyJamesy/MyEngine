#include "Shader.h"
#include <fstream>
#include <sstream>

std::vector<unsigned int> Shader::m_Attached;
std::map<std::string, unsigned int> Shader::m_Imported;
std::map<std::string, unsigned int> Shader::m_Programs;

void Shader::Start(const char* _name)
{
	glUseProgram(m_Programs[_name]);
}

void Shader::Stop()
{
	glUseProgram(0);
}

unsigned int Shader::GetProgram(const char* _name)
{
	if (m_Programs.find(_name) != m_Programs.end())
		return m_Programs[_name];

	return 0;
}

void Shader::Import(const char* _name, unsigned int _type)
{
	std::string _fullpath = Resource::GetWorkingDirectory() + "resources\\shaders\\" + _name + ".glsl";
	
	if (m_Imported.find(_name) != m_Imported.end())
		return;
	
	std::ifstream _file;
	std::stringstream _stream;
	
	std::string _contents;
	
	_file.exceptions(std::ifstream::badbit);
	
	try
	{
		_file.open(_fullpath);
	
		if (!_file.good())
		{
			printf("%s '%s'\n", "Shader Log: Error Loading Shader", _name);
			return;
		}
	
		_stream << _file.rdbuf();
	
		_file.close();
	
		_contents = _stream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("%s\n", e.what());
		return;
	}
	
	GLuint _shader = glCreateShader(_type);
	
	const GLchar* _code = _contents.c_str();
	
	glShaderSource(_shader, 1, &_code, NULL);
	glCompileShader(_shader);
	
	int _status;
	char _log[512];
	
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &_status);
	if (!_status)
	{
		glGetShaderInfoLog(_shader, 512, NULL, _log);
		printf("Shader Log:\n%s\n", _log);
		return;
	}
	
	printf("Shader: Imported - %s\n", _name);
	
	m_Imported[_name] = _shader;
}

void Shader::Attach(const char* _name)
{
	if (m_Imported.find(_name) == m_Imported.end())
		return;

	auto _find = std::find(m_Attached.begin(), m_Attached.end(), m_Imported[_name]);
	if (_find != m_Attached.end())
		return;

	printf("Shader: Attached - %s\n", _name);

	m_Attached.push_back(m_Imported[_name]);
}

void Shader::Compile(const char* _name)
{
	if (m_Programs.find(_name) != m_Programs.end())
		return;

	unsigned int _program = glCreateProgram();
	m_Programs[_name] = _program;

	int _status;
	char _log[512];

	for (unsigned int _shader : m_Attached)
	{
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &_status);
		if (!_status)
		{
			glGetProgramInfoLog(_program, 512, NULL, _log);
			printf("Shader Log: Error Compiling\n\n%s\n", _log);
		}

		glAttachShader(_program, _shader);
	}

	//if (std::string(_name) == "particle_update")
	//{
	//	const char* varyings[] = { "position", "velocity", "lifetime", "lifespan" };
	//	glTransformFeedbackVaryings(Shader::GetProgram("particle_update"), 4, varyings, GL_INTERLEAVED_ATTRIBS);
	//}

	glLinkProgram(_program);

	glGetProgramiv(_program, GL_LINK_STATUS, &_status);
	if (!_status)
	{
		glGetProgramInfoLog(_program, 512, NULL, _log);
		printf("Shader Log: Error Linking\n\n%s\n", _log);
	}

	printf("Shader: Compiled - %s\n\n", _name);

	m_Attached.clear();
}
