#pragma once
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "active_obj.h"

class box : public active_obj
{
	void show() 
	{
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "X"; 
	}
};