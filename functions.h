#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "dataset.h"

int mainloop (dataset &M) 
{
	bool condition = true;
    int varx,vary;
	do {
		M.update();

		system("cls");
		M.showset();

		char button;
		button = _getch();
		switch (button)
		{
		case 'd':
		    varx = 0; vary = 1;
			M.move(varx,vary);
			break;

		case 'a':
		    varx = 0; vary = -1;
		    M.move(varx,vary);
			break;

		case 's':
		    varx = 1; vary = 0;
		    M.move(varx,vary);
		    break;

		case 'w':
		    varx = -1; vary = 0;
			M.move(varx,vary);
			break;
        case 'e':
			char b;
			std::cout << std::endl << "exit (Y/N)";
			b = _getch();
			switch (b)
			{
			case 'y':
				condition = false;
				break;
			case  'n':
				break;
			}
			break;
		}
	} while (condition == true);
	
}
