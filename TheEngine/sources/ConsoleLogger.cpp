#include <Windows.h>
#include "ConsoleLogger.h"
#include <cstdio>
#include <iostream>
using namespace std;


ConsoleLogger::~ConsoleLogger()
{
	FreeConsole();
}

ConsoleLogger::ConsoleLogger()
{
	AllocConsole();

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
}


void ConsoleLogger::Log(char* message)
{
	cout << message << endl;
}
