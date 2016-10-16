#pragma once
#include "Component.h"

#include <GLFW\glfw3.h>

struct KeyState
{
	enum State
	{
		KEY_UP,
		KEY_DOWN,
		KEY_PRESSED,
		KEY_RELEASED,
		KEY_REPEAT
	};
};

class Input : public Component
{
public:
	static KeyState::State m_KeyStates[1024];

	static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode)
	{

	}

	static void MouseCallback(GLFWwindow* _window, double _x, double _y)
	{

	}

	static void ScrollCallback(GLFWwindow* _window, double _x, double _y)
	{

	}

private:

};