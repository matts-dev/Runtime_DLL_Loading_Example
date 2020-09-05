//#include "pch.h"
#include <iostream>
#include "DllExports.h"

#define USE_ALTERNATIVE 0

void tick_cpp(); //test using cpp data across dll boundary

void LogFromDLL()
{
#if USE_ALTERNATIVE
	std::cout << "Custom DLL Function ALTERNATIVE" << std::endl;
	
	int x = 6;
	if (x > 5)
		if (x > 2)
			std::cout << "TRUE TRUE - testing branching after reload" << std::endl;
		else
			std::cout << "TRUE FALSE - testing branching after reload" << std::endl;
	else
		if (x > 2)
			std::cout << "FALSE TRUE - testing branching after reload" << std::endl;
		else
			std::cout << "FALSE FALSE - testing branching after reload" << std::endl;

#else
	std::cout << "Custom DLL Function Loaded" << std::endl;

	int x = 4;
	if (x > 5)
		if (x > 2)
			std::cout << "TRUE TRUE - testing branching after reload" << std::endl;
		else
			std::cout << "TRUE FALSE - testing branching after reload" << std::endl;
	else
		if (x > 2)
			std::cout << "FALSE TRUE - testing branching after reload" << std::endl;
		else
			std::cout << "FALSE FALSE - testing branching after reload" << std::endl;
#endif


	tick_cpp();
}

///////////////////////////////////////////////////////////
// test cpp code
///////////////////////////////////////////////////////////
struct StringHolder
{
	StringHolder() { std::cout << __FUNCTION__"ctor" << std::endl; std::memset(&bytes, 0xAA, sizeof(bytes)); }
	~StringHolder() { std::cout << __FUNCTION__"dtor" << std::endl; std::memset(&bytes, 0xFF, sizeof(bytes));}
	char bytes[10];
};

class MyTestGame
{
public:
	MyTestGame() 
	{
		std::cout << __FUNCTION__ << " CONSTRUCTOR" << std::endl;
		heapMemory = new StringHolder;
	}

	~MyTestGame()
	{
		std::cout << __FUNCTION__ << " DESTRUCTOR" << std::endl;
		delete heapMemory;
	}

public:
	void tick()
	{
#if USE_ALTERNATIVE
		std::cout << __FUNCTION__ << " ALTERNATIVE" << std::endl;
#else
		std::cout << __FUNCTION__ << " ALTERNATIVE" << std::endl;
#endif
	}
private:
	StringHolder* heapMemory;
};


void tick_cpp()
{
	static MyTestGame myGame;
	myGame.tick();
}


MYGAMEDLL_API void tick()
{
	//this is a c function, idk if we can actually do c++ from within ?
	tick_cpp();

}
