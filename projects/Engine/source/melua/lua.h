#pragma once
#include "LUA\lua.hpp"

class LuaState
{
public:
	void OpenLib()
	{
		m_State = luaL_newstate();
		luaL_openlibs(m_State);
	}

	static void ReportErrors(lua_State* _state, int status)
	{
		if (status != 0) {
			printf("--%s\n", lua_tostring(_state, -1));
			lua_pop(_state, 1);
		}
	}

	static void PrintTable(lua_State* _state, unsigned int _d = 0, unsigned int _n = 0)
	{
		lua_pushnil(_state);
		while (lua_next(_state, -2) != 0)
		{
			//printf("%s - %s\n",
			//	lua_typename(m_State, lua_type(m_State, -2)),
			//	lua_typename(m_State, lua_type(m_State, -1))
			//);

			int _key	= lua_type(_state, -2);
			int _value	= lua_type(_state, -1);

			for (unsigned int _i = 0; _i < _n; ++_i)
				printf("    ");

			switch (_key)
			{
			case LUA_TSTRING:
				printf("%s = ", lua_tostring(_state, -2));
				break;
			case LUA_TNUMBER:
				printf("%u = ", (unsigned int) lua_tointeger(_state, -2));
				break;
			case LUA_TLIGHTUSERDATA:
				printf("%p = ", lua_topointer(_state, -2));
				break;
			default:
				printf("%s = ", lua_typename(_state, lua_type(_state, -2)));
				break;
			}

			switch (_value)
			{
			case LUA_TSTRING:
				printf("'%s'", lua_tostring(_state, -1));
				break;
			case LUA_TNUMBER:
				printf("%0.2f", lua_tonumber(_state, -1));
				break;
			case LUA_TBOOLEAN:
				printf("%s", lua_toboolean(_state, -1) ? "true" : "false");
				break;
			case LUA_TTABLE:
			{
				printf("\n");
				if (_n < _d)
					PrintTable(_state, _d, _n + 1);
			}
			break;
			case LUA_TFUNCTION:
				printf("'%s'", "FUNCTION");
				break;
			default:
				printf("'%s'", lua_tostring(_state, -1));
				break;
			}

			printf("\n");

			lua_pop(_state, 1);
		}
	}

	static void StackDump(lua_State* _state)
	{
		int i = lua_gettop(_state);

		printf("\n[Stack Dump] %d\n", i);

		while (i) {
			int j =  i - lua_gettop(_state);

			int t = lua_type(_state, i);
			switch (t)
			{
			case LUA_TSTRING:
				printf("	%d:`%s'\n", j, lua_tostring(_state, i));
				break;
			case LUA_TBOOLEAN:
				printf("	%d: %s\n", j, lua_toboolean(_state, i) ? "true" : "false");
				break;
			case LUA_TNUMBER:
				printf("	%d: %g\n", j, lua_tonumber(_state, i));
				break;
			case LUA_TTABLE:
				printf("	%d:table\n", j);
				//PrintTable(L, 1, 3);
				break;
			default: printf("	%d: %s\n", j, lua_typename(_state, t));
				break;
			}

			--i;
		}

		printf("[Stack Dump Finished]\n\n");
	}
	
	void SetPath(const char* _path)
	{
		lua_getglobal(m_State, "package");
		lua_getfield(m_State, -1, "path");
		std::string cur_path = lua_tostring(m_State, -1);
		cur_path.append(";");
		cur_path.append(_path);
		cur_path.clear();

		cur_path = _path;
		cur_path.append("?.lua");
		cur_path.append(";");

		lua_pop(m_State, 1);
		lua_pushstring(m_State, cur_path.c_str());
		lua_setfield(m_State, -2, "path");

		StackDump(m_State);

		lua_pop(m_State, 1);
	}

	void DoFile(const char* _file)
	{
		if (int _s = luaL_dofile(m_State, _file) != 0)
			ReportErrors(m_State, _s);
	}

	void LoadFile(const char* _file)
	{
		if (int _s = luaL_loadfile(m_State, _file) != 0)
			ReportErrors(m_State, _s);
	}

	lua_State* State() { return m_State; }

protected:
	lua_State* m_State;

};
