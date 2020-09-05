#pragma once
#include <iostream>
#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void(*logFromDLL_functionPtr)(void);
extern logFromDLL_functionPtr logFromDLL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* const DLL_NAME = "MyGameDLL.dll";

class Engine
{
public:
	void tick();
	void reloadGameDLL();
	void unloadGameDLL();
private:
	HMODULE hGameDll = nullptr;
};