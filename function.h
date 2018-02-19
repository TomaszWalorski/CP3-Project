#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <cstdio>
#include "dataset.h"
#include <windows.h>

void Cursor_Killer()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void mainloop(dataset &M)
{
	int counter_1=0, counter_2 = 0, counter_3 = 0;
	time_t t1, t2, t3;
	bool condition = true;
    int varx,vary;

	time( & t3);
	t1 = time(&t2) - t3;

    M.showset(counter_2, counter_3, t1);
	do {

		char button;

		Cursor_Killer();

		while (!_kbhit())
		{
			t1 = time(&t2) - t3;
			counter_1++;
			COORD coodr = { 0,0 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coodr);
			M.shot(counter_1); 
			M.update();  
			M.move_bullet(1, 0, condition); 

			if (M.state_of_enemy() == false)
			{
				switch (rand() % 4 + 1)
				{
				case 1:
					varx = 0; vary = 1;
					break;

				case 2:
					varx = 0; vary = -1;
					break;

				case 3:
					varx = 1; vary = 0;
					break;

				case 4:
					varx = -1; vary = 0;
					break;
				}
				M.move_enemy(varx, vary, condition);
			
			}

			Sleep(50);

			M.update(); 
			M.showset(counter_2, counter_3, t1);
			M.gameover(condition); 
			if (condition == false) break;
		}

		while (_kbhit())
		{
			while (button = _getch())
			{
				
				switch (button)
				{
				case 'd':
					varx = 0; vary = 1;
					M.move(varx, vary, condition, counter_3);
					counter_2++;
					break;

				case 'a':
					varx = 0; vary = -1;
					M.move(varx, vary, condition, counter_3);
					counter_2++;
					break;

				case 's':
					varx = 1; vary = 0;
					M.move(varx, vary, condition, counter_3);
					counter_2++;
					break;

				case 'w':
					varx = -1; vary = 0;
					M.move(varx, vary, condition, counter_3);
					counter_2++;
					break;
				case 'q':
					M.take_key();
					break;
				case 'z':
					M.open_door();
					break;
				case 'e':
					char b;
					HANDLE hOut;
					hOut = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
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
				break;
			}
			break;
		}
		
	} while (condition == true);
	
	M.update();
	COORD coodr = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coodr);
	M.showset(counter_2, counter_3, t1);

	std::cout << "Press any key to continue...";
	_getche();
}

void menu()
{
	while (1)
	{
		dataset M;
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

		std::cout << "Soko-Ban" << std::endl << std::endl;
		std::cout << "(1) Start game" << std::endl << "(2) Exit" << std::endl;
		char button; bool condition = false;
		button = _getche();

		COORD coodr = { 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coodr);

		switch (button)
		{
		case '1':
			mainloop(M);
			break;
		case '2':
			condition = true;
			break;
		}
		if (condition == true) { system("cls"); break; }
		system("cls");

		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		std::cout << "GAME OVER. TRY AGAIN!" << std::endl << std::endl;
	}
}
