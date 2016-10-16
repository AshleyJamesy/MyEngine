#pragma once
#include <map>
#include <list>
#include <vector>

#include <GLEW\glew.h>

#include "source\mesystem\Resource.h"

class Uniform
{
	GLuint	m_Progam	= 0;
	GLuint	m_Location	= 0;

	GLchar	m_Name[32];			//Variable Name in Shader
	GLint	m_Size		= 0;	//Size of Variable
	GLenum	m_Type		= 0;	//Type of Variable
	GLsizei m_Length	= 0;	//Name Length

	void* m_Reference	= nullptr;

public:
	void GetData(GLint _program, GLuint _index)
	{
		m_Progam	= _program;
		
		glGetActiveUniform(_program, _index, 32, &m_Length, &m_Size, &m_Type, m_Name);
		
		m_Location =
			glGetUniformLocation(_program, m_Name);
	}

	GLint GetSize()
	{
		return m_Size;
	}

	GLenum GetType()
	{
		return m_Type;
	}

	const GLchar* GetName()
	{
		return m_Name;
	}

	GLsizei GetLength()
	{
		return m_Length;
	}
	
};

class Shader
{
	static std::vector<unsigned int>			m_Attached;
	static std::map<std::string, unsigned int>	m_Imported;
	static std::map<std::string, unsigned int>	m_Programs;

public:
	static void Start(const char* _name);

	static void Stop();

	static unsigned int Program()
	{
		GLint _program;
		glGetIntegerv(GL_CURRENT_PROGRAM, &_program);

		return _program;
	}

	static unsigned int GetProgram(const char* _name);

	static unsigned int GetUniformLocation(const char* _uniform)
	{
		unsigned int _program = Program();

		if (_program > 0)
			return glGetUniformLocation(_program, _uniform);

		return -1;
	}

	static unsigned int GetUniformLocation(const char* _shader, const char* _uniform)
	{
		unsigned int _program = GetProgram(_shader);

		if (_program > 0)
			return glGetUniformLocation(_program, _uniform);

		return -1;
	}

	static void GetUniforms()
	{
		GLint _program;
		glGetIntegerv(GL_CURRENT_PROGRAM, &_program);
		
		GLint _count;

		glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &_count);
		
		printf("Active Uniforms: %d\n", _count);

		for (GLint i = 0; i < _count; i++)
		{
			Uniform _uniform;
				_uniform.GetData(_program, i);

			printf("Uniform: %u Name: %s\n", _uniform.GetType(), _uniform.GetName());
		}

		printf("\n");
	}

	static void Import(const char* _name, unsigned int _type);

	static void Attach(const char* _name);

	static void Compile(const char* _name);

};