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

#include "mesystem\Resource.h"
#include "mesystem\Window.h"

#include "melua\lua.h"
#include "memath\Vector2.h"
#include "memath\Vector3.h"
#include "memath\Matrix4.h"

#include "mesystem\TaskManager.h"

#include "mecontainers\StaticMap.h"

#include <assert.h>

#include <thread>

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
	Window _Window = Window(512, 512, "MyEngine");
	ThreadPool _ThreadPool;

	LuaState m_LuaState;

	m_LuaState.OpenLib();

	lua_createtable(m_LuaState.State(), 0, 0);
	lua_setglobal(m_LuaState.State(), "Gamemode");

	//std::string _path = MyEngine::Resource::GetWorkingDirectory() + "lua\\";
	//m_LuaState.SetPath(_path.c_str());

	std::thread CommandThread(commandline, &m_LuaState);

	//lua includes
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

		glfwSwapBuffers(_Window.GetWindow());
	}

	CommandThread.join();

	return 0;
}