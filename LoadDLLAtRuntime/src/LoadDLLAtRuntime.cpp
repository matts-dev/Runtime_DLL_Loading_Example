#include "Engine.h"
#include<iostream>

int main()
{
	Engine engine;
	
	std::cout << "[t] tick engine, [q] to quit, [r] to load game dll, [u] to unload game dll" << std::endl;

	//attempt to load dll on first launch
	engine.reloadGameDLL();

	char userChar = 't';
	while (userChar != 'q')
	{
		if (userChar == 'r')
		{
			engine.reloadGameDLL();
		}
		if (userChar == 'u')
		{
			engine.unloadGameDLL();
		}

		engine.tick();
		userChar = std::getchar();
		std::getchar(); //get the new line
	}
}