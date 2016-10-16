//#include "MessageBus.h"
//#include "Framework.h"
//#include "Component.h"
//#include "GameObject.h"
//#include "Serialise.h"
//#include "s_Input.h"
//
//#include <time.h>
//#include <random>
//
//#include <atomic>
//#include <thread>
//#include <chrono>
//#include <iostream>
//
//#include "TaskManager.h"
//
//#include "System.h"
//
//class MyComponent : public Component
//{
//public:
//	void Start()
//	{
//		printf("MyComponent Started!\n");
//	}
//	
//};
//
//void Update(bool* _active, unsigned int _interval)
//{
//	const auto wait_duration = std::chrono::milliseconds(_interval);
//
//	const bool m_MultiThread = true;
//
//	bool _update = false;
//
//	if(m_MultiThread)
//		for each(System* _system in MessageBus::_MessageBus().m_Systems)
//			std::thread* _thread = new std::thread(System::Thread, _system, &_update);
//
//	while (_active)
//	{
//		MessageBus::_MessageBus().SwapQueue();
//
//		MyEngine::Update();
//
//		if (m_MultiThread)
//		{
//			for each(System* _system in MessageBus::_MessageBus().m_Systems)
//				_system->m_Finished = false;
//
//			_update = true;
//
//			bool _finished;
//			while (true)
//			{
//				_finished = true;
//
//				for each(System* _system in MessageBus::_MessageBus().m_Systems)
//					if (!_system->m_Finished)
//						_finished = false;
//
//				if (_finished)
//					break;
//			}
//
//			_update = false;
//		}
//		else
//		{
//			MessageBus::_MessageBus().ReadQueue();
//		}
//
//		std::this_thread::sleep_for(wait_duration);
//	}
//}
//
//int main()
//{
//	//srand(time(NULL));
//	//
//	//Systems::Input _InputA;
//	//Systems::Input _InputB;
//	//Systems::Input _InputC;
//	//Systems::Input _InputD;
//	//
//	//GameObject _MyGameObject;
//	//_MyGameObject.AddComponent<MyComponent>();
//	//
//	//_MyGameObject.Start();
//	//
//	//bool _active;
//	//
//	//_active = true;
//	//
//	//std::thread thread_update(Update, &_active, 60);
//	//
//	//while (true) {
//	//}
//	//
//	//_active = false;
//	//
//	//thread_update.join();
//
//	while (ThreadPool::m_TaskCount > 0)
//	{
//		Task _task;
//
//		if()
//	}
//
//	return 0;
//}

#include <iostream>

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"

#include "mesystem\Resource.h"
#include "melua\lua.h"
#include "memath\Vector2.h"
#include "memath\Vector3.h"
#include "memath\Matrix4.h"

#include "mecontainers\StaticMap.h"

#include <assert.h>

#include <thread>

GLFWwindow* _window;

int CreateWindow(int _width, int _height, const char* _title)
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);

	if (_window == nullptr)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
	}

	if (_window == nullptr)
		return 2;

	glfwMakeContextCurrent(_window);

	glewExperimental = GL_TRUE;

	glewInit();

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	//glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, _width, _height);

	return 0;
}

void DrawQuadOutline(Vector3<float>& _Center, float _Width, float _Height, float _Line, Vector3<float>& _Colour)
{
	glLineWidth(_Width);
	glColor3f(_Colour.x, _Colour.y, _Colour.z);

	glBegin(GL_LINES);
	glVertex3f(_Center.x - _Width / 2, _Center.y + _Height / 2, _Center.z);
	glVertex3f(_Center.x + _Width / 2, _Center.y + _Height / 2, _Center.z);

	glVertex3f(_Center.x + _Width / 2, _Center.y + _Height / 2, _Center.z);
	glVertex3f(_Center.x + _Width / 2, _Center.y - _Height / 2, _Center.z);

	glVertex3f(_Center.x + _Width / 2, _Center.y - _Height / 2, _Center.z);
	glVertex3f(_Center.x - _Width / 2, _Center.y - _Height / 2, _Center.z);

	glVertex3f(_Center.x - _Width / 2, _Center.y - _Height / 2, _Center.z);
	glVertex3f(_Center.x - _Width / 2, _Center.y + _Height / 2, _Center.z);
	glEnd();
}

static int LUA_DrawQuadOutline(lua_State* _state)
{
	float _x		= (float) lua_tonumber(_state, 1);
	float _y		= (float) lua_tonumber(_state, 2);
	float _z		= (float) lua_tonumber(_state, 3);
	float _width	= (float) lua_tonumber(_state, 4);
	float _height	= (float) lua_tonumber(_state, 5);
	float _line		= (float) lua_tonumber(_state, 6);
	float _r		= (float) lua_tonumber(_state, 7);
	float _g		= (float) lua_tonumber(_state, 8);
	float _b		= (float) lua_tonumber(_state, 9);

	DrawQuadOutline(Vector3<float>(_x, _y, _z), _width, _height, _line, Vector3<float>(_r, _g, _b));

	return 0;
}

void Reload(LuaState* _state, std::string _string)
{
	_state->DoFile("init.lua");

	lua_getglobal(_state->State(), "Gamemode");
	lua_getfield(_state->State(), -1, "Initialise");

	if (int _s = lua_pcall(_state->State(), 0, 0, 0) != 0)
		LuaState::ReportErrors(_state->State(), _s);

	lua_getglobal(_state->State(), "Hooks");
	lua_getfield(_state->State(), -1, "Call");
	lua_pushvalue(_state->State(), -1);
	lua_pushstring(_state->State(), "Awake");

	if (int _s = lua_pcall(_state->State(), 2, 0, 0) != 0)
		LuaState::ReportErrors(_state->State(), _s);

	lua_getglobal(_state->State(), "Hooks");
	lua_getfield(_state->State(), -1, "Call");
	lua_pushvalue(_state->State(), -1);
	lua_pushstring(_state->State(), "Start");

	if (int _s = lua_pcall(_state->State(), 2, 0, 0) != 0)
		LuaState::ReportErrors(_state->State(), _s);
}

void commandline(LuaState* _state)
{
	std::string _input;

	typedef void(*func_command)(LuaState*, std::string);

	StaticMap<std::string, void*, 32> m_Commands;

	m_Commands.Set("/reload", Reload);

	while (true)
	{
		std::getline(std::cin, _input);

		size_t _i = _input.find_first_of(' ');

		if(_input.size() > 0)
			if (_i > 0)
			{
				std::string _command	= _input.substr(0, _i);
				std::string _parameters = _input.substr(_i + 1, _input.size());

				if (_command[0] == '/')
				{
					auto _find = m_Commands.Find(_command);
					if (_find.m_Index > -1)
						((func_command)m_Commands.Get(_find))(_state, _parameters);
					else
						printf("Unknown Command\n");
				}
				else
					printf("%s\n", _input.c_str());
			}
	}
}

int main()
{
	CreateWindow(512, 512, "");
	
	LuaState m_LuaState;

	m_LuaState.OpenLib();

	lua_createtable(m_LuaState.State(), 0, 0);
	lua_setglobal(m_LuaState.State(), "Render");

	lua_getglobal(m_LuaState.State(), "Render");

	lua_pushcfunction(m_LuaState.State(), LUA_DrawQuadOutline);
	lua_setfield(m_LuaState.State(), -2, "DrawQuadOutline");

	lua_pop(m_LuaState.State(), -1);

	lua_createtable(m_LuaState.State(), 0, 0);
	lua_setglobal(m_LuaState.State(), "Gamemode");

	//std::string _path = MyEngine::Resource::GetWorkingDirectory() + "lua\\";
	//m_LuaState.SetPath(_path.c_str());

	std::thread CommandThread(commandline, &m_LuaState);

	m_LuaState.DoFile("hooks.lua");
	m_LuaState.DoFile("entity.lua");

	m_LuaState.DoFile("init.lua");

	lua_getglobal(m_LuaState.State(), "Gamemode");
	lua_getfield(m_LuaState.State(), -1, "Initialise");

	if (int _s = lua_pcall(m_LuaState.State(), 0, 0, 0) != 0)
		LuaState::ReportErrors(m_LuaState.State(), _s);

	lua_getglobal(m_LuaState.State(), "Hooks");
	lua_getfield(m_LuaState.State(), -1, "Call");
	lua_pushvalue(m_LuaState.State(), -1);
	lua_pushstring(m_LuaState.State(), "Awake");

	if (int _s = lua_pcall(m_LuaState.State(), 2, 0, 0) != 0)
		LuaState::ReportErrors(m_LuaState.State(), _s);

	lua_getglobal(m_LuaState.State(), "Hooks");
	lua_getfield(m_LuaState.State(), -1, "Call");
	lua_pushvalue(m_LuaState.State(), -1);
	lua_pushstring(m_LuaState.State(), "Start");

	if (int _s = lua_pcall(m_LuaState.State(), 2, 0, 0) != 0)
		LuaState::ReportErrors(m_LuaState.State(), _s);

	while (true)
	{
		glfwPollEvents();

		//Update
		lua_getglobal(m_LuaState.State(), "Gamemode");
		lua_getfield(m_LuaState.State(), -1, "Update");
		
		if (int _s = lua_pcall(m_LuaState.State(), 0, 0, 0) != 0)
			LuaState::ReportErrors(m_LuaState.State(), _s);

		lua_getglobal(m_LuaState.State(), "Hooks");
		lua_getfield(m_LuaState.State(), -1, "Call");
		lua_pushvalue(m_LuaState.State(), -1);
		lua_pushstring(m_LuaState.State(), "Update");

		if (int _s = lua_pcall(m_LuaState.State(), 2, 0, 0) != 0)
			LuaState::ReportErrors(m_LuaState.State(), _s);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render
		lua_getglobal(m_LuaState.State(), "Gamemode");
		lua_getfield(m_LuaState.State(), -1, "Render");

		if (int _s = lua_pcall(m_LuaState.State(), 0, 0, 0) != 0)
			LuaState::ReportErrors(m_LuaState.State(), _s);

		lua_getglobal(m_LuaState.State(), "Hooks");
		lua_getfield(m_LuaState.State(), -1, "Call");
		lua_pushvalue(m_LuaState.State(), -1);
		lua_pushstring(m_LuaState.State(), "Render");

		if (int _s = lua_pcall(m_LuaState.State(), 2, 0, 0) != 0)
			LuaState::ReportErrors(m_LuaState.State(), _s);

		glfwSwapBuffers(_window);
	}

	CommandThread.join();

	return 0;
}