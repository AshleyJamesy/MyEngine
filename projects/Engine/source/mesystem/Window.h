#pragma once
#include <iostream>

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"

class Window
{
public:
	GLFWwindow* m_Window;

	Window(int _width, int _height, const char* _title)
	{
		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_Window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);

		if (m_Window == nullptr)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_Window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
		}

		if (m_Window == nullptr)
			return;

		glfwMakeContextCurrent(m_Window);

		glewExperimental = GL_TRUE;

		glewInit();

		printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

		//glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glViewport(0, 0, _width, _height);
	}

	GLFWwindow* GetWindow()
	{
		return m_Window;
	}

private:

};