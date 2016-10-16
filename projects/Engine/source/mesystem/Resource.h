#pragma once
#include <stdio.h>
#include <fstream>

#ifdef _WIN32

#include <direct.h>
#define GetCurrentDir _getcwd

#else

#include <unistd.h>
#define GetCurrentDir getcwd

#endif

#include <string>
#include <vector>
#include <map>

class Resource
{
public:
	static std::string GetWorkingDirectory()
	{
		char _path[FILENAME_MAX];
		
		if (!GetCurrentDir(_path, sizeof(_path)))
			return "";
		
		return std::string(_path) + "\\";
	}
};

//namespace MyEngine
//{
//	std::string GetWorkingDirectory()
//	{
//		char _path[FILENAME_MAX];
//
//		if (!GetCurrentDir(_path, sizeof(_path)))
//			return "";
//
//		return std::string(_path) + "\\";
//	}
//}