#pragma once
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "active_obj.h"

class player : public active_obj
{
public:
    bool have_key;

    player()
    {
        have_key = false;
    }
	void show() 
	{ 
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
		std::cout << "o"; 
	}

};
