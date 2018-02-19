#pragma once
#pragma once
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include "active_obj.h"

class bullet : public active_obj
{
private:

	int x, y;
	bool state;
	int counter;

public:
	bullet()
	{
		x = 0;
		y = 0;
		counter = 0;
		state = false;
	}

	bullet(int a, int b)
	{
		x = a;
		y = b;
		counter = 0;
		state = false;
	}

	void show()
	{
		 
		counter++;
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		switch ((counter % 2))
		{
		case 0:
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case 1:
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		}

		std::cout << "*";
	}

	int _state()
	{
		return state;
	}

	void change_state(bool new_state)
	{
		state = new_state;
	}

	int _x()
	{
		return x;
	}

	int _y()
	{
		return y;
	}

	void change_coord(int new_x, int new_y)
	{
		x += new_x;
		y += new_y;
	}

	void reset_coord()
	{
		x = 0;
		y = 0;
	}
};
