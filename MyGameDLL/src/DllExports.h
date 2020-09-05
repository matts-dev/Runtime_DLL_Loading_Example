#pragma once

//https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=vs-2019

//dll projec will define this
#ifdef MYGAMEDLL_EXPORTS
#define MYGAMEDLL_API __declspec(dllexport)
#else
#define MYGAMEDLL_API __declspec(dllimport)
#endif

//MSDN examples show extern "C" here; trying without since this is cpp.
//MYGAMEDLL_API void LogFromDLL();
//Turns out c++ name mangling is happening, so need to correct function name so that is mangled when trying to get proc address
//using extern c means funciton name will match exactly
extern "C" MYGAMEDLL_API void LogFromDLL();


//extern "C" MYGAMEDLL_API void tick();
