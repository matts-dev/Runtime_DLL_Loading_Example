#include <iostream>

#include "Engine.h"

#include <winbase.inl>
#include <libloaderapi.h>
#include <atlstr.h>

void Engine::tick()
{
	logFromDLL();
}

void NoFunctionLoadedLog() { std::cout << "NO DLL LOADED" << std::endl; }

static logFromDLL_functionPtr logFromDLL = NoFunctionLoadedLog;

void Engine::reloadGameDLL()
{
	if (hGameDll)
	{
		unloadGameDLL();
	}

	CStringW DLL_NAME_WIDE = DLL_NAME;
	hGameDll = LoadLibrary(DLL_NAME_WIDE);
	if (hGameDll)
	{
		std::cout << "loaded game dll" << std::endl;

		logFromDLL_functionPtr fptr = (logFromDLL_functionPtr)GetProcAddress(hGameDll, "LogFromDLL");
		if (fptr)
		{
			logFromDLL = fptr;
		}
		else
		{
			std::cerr << "failed to find the dll function" << std::endl;
		}
	}
	else
	{
		std::cerr << "failed to load the game dll" << std::endl;
	}
	
}

void Engine::unloadGameDLL()
{
	if (hGameDll)
	{
		std::cout << "unloaded previous game dll" << std::endl;

		FreeLibrary(hGameDll);
		logFromDLL = &NoFunctionLoadedLog;
		hGameDll = nullptr;
	}
}

