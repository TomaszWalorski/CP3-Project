#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>

#include "dataset.h"

dataset::dataset() {

	int bbb = 0, www = 0, fff = 0, ppp = 0;     // COUNTERS OF GRAPHICAL OBJECTS
	std::string line;
	std::fstream file;

	file.open("a.txt", std::ios::in);
	if (file.good() == false)
	{
		std::cout << "Error, app cannot open file." << std::endl << "Press enter to continue.";
		getchar();
		exit(0);
	}

	getline(file, line);
	x = atoi(line.c_str());
	getline(file, line);
	y = atoi(line.c_str());


	for (int m = 0; m < x; m++)
	{
		tab_so.push_back(std::vector <char>());
		getline(file, line);
		for (int a = 0; a<y; a++)
		{
			tab_so[m].push_back(char(line[a]));
			switch (line[a])
			{
			case 'w': www++; break;
			case 'f': fff++; break;
			case 'p': ppp++; break;
			}
		}
	}

	getline(file, line);

	for (int a = 0; a<x; a++)
	{
		tab_ao.push_back(std::vector <char>());
	}

	for (int m = 0; m < x; m++)
	{
		tab_ao.push_back(std::vector <char>());
		getline(file, line);
		for (int a = 0; a<y; a++)
		{
			tab_ao[m].push_back(char(line[a]));
			switch (line[a])
			{
			case 'b': bbb++; break;
			case '0': break;
			}
		}
	}

	b = new box[bbb];
	w = new wall[www];
	f = new flor[fff];
	pu = new purpose[ppp];

	bbb = 0, www = 0, fff = 0; ppp = 0;

	for (int coord_x = 0; coord_x < x; coord_x++)
	{
		aop_so.push_back(std::vector <object *>());
		for (int coord_y = 0; coord_y < y; coord_y++)
		{
			aop_so[coord_x].push_back(new object());
			switch (tab_so[coord_x][coord_y])
			{
			case 'v':
				aop_so[coord_x][coord_y] = &g;
				break;
			case 'w':
				aop_so[coord_x][coord_y] = &w[www];
				www++;
				break;
			case 'f':
				aop_so[coord_x][coord_y] = &f[fff];
				fff++;
				break;
            case 'p':
                aop_so[coord_x][coord_y] = &pu[ppp];
                ppp++;
                break;
			}
		}
	}

	for (int coord_x = 0; coord_x < x; coord_x++)
	{
		aop_ao.push_back(std::vector <object *>());
		for (int coord_y = 0; coord_y < y; coord_y++)
		{
			aop_ao[coord_x].push_back(new object());
			switch (tab_ao[coord_x][coord_y])			{
            case 'k':
                aop_ao[coord_x][coord_y] = &k;
                break;
			case 'e':
				aop_ao[coord_x][coord_y] = &e;
				xe = coord_x; ye = coord_y;
				break;
			case 'p':
				aop_ao[coord_x][coord_y] = &p;
				xp = coord_x; yp = coord_y;
				break;
			case 'd':
				aop_ao[coord_x][coord_y] = &d;
				break;
			case 'b':
				aop_ao[coord_x][coord_y] = &b[bbb];
				bbb++;
				break;
			case 'B':
				aop_ao[coord_x][coord_y] = &bu;
				bu.change_coord(coord_x, coord_y);
				break;
			case '0': aop_ao[coord_x][coord_y] = 0;
				break;
			}
		}
	}

}

void dataset::showset(int nr_1, int &nr_2, time_t t) {
	for (int b = 0; b < x; b++)
	{
		for (int a = 0; a < y; a++)
		{
			switch (tab_so[b][a])
			{
			case 'v':
			case 'w': aop_so[b][a]->show(); break;
			case 'f':
				if (tab_ao[b][a] != '0') { aop_ao[b][a]->show(); }
				else aop_so[b][a]->show();
				break;
            case 'p':
				if (tab_ao[b][a] != '0') { aop_ao[b][a]->show(); }
				else aop_so[b][a]->show();
				break;
			}
		}
		std::cout << std::endl;
	}

	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	std::cout << std::endl << "Moves: " << nr_1 << "  Pushes: " << nr_2;
	int m = t / 60, s = t % 60;
	std::cout << "  Time: "; if(m < 10) std::cout << 0; std::cout << m << ":"; if (s < 10) std::cout << 0; std::cout << s << std::endl;
}

void dataset::tester()
{
	const int X=3;
	bool test[X];
	int nr_w=0, nr_f=0, nr_b=0, badf=0, badw=0, badp=0, badb=0, bad_empty=0, badxp=0, badyp=0;

	for (int g = 0; g < x; g++)
	{
		for (int d = 0; d < y; d++)
		{
			switch (tab_so[g][d])
			{
			case 'w':
				if ((aop_so[g][d] == &w[nr_w]) == false) { badw++; }
				nr_w++;
				break;
			case 'f':
				if ((aop_so[g][d] == &f[nr_f]) == false) { badf++; }
				nr_f++;
				break;
			}
		}
	}

	for (int g = 0; g < x; g++)
	{
		for (int d = 0; d < y; d++)
		{
			switch (tab_ao[g][d])
			{
			case 'p':
				if((aop_ao[g][d] == &p) == false) { badp++; }
				if (g != xp) badxp++;
				if (d != yp) badyp++;
				break;
			case 'b':
				if((aop_ao[g][d] == &b[nr_b]) == false) { badb++; }
				nr_b++;
				break;
			case '0': if((aop_ao[g][d] == 0) == false) { bad_empty++; }
				break;
			}
		}
	}

	test[0] = (badf == 0 && badw == 0);
	test[1] = (badb == 0 && badp == 0 && bad_empty==0);
	test[2] = (badxp == 0 && badyp == 0);

	std::cout << std::endl;
	for (int a = 0; a < X; a++)
	{
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		std::cout << "Test nr" << a << ":";
		if (test[a] == true) { std::cout << "+"; }
		else std::cout << "-";
		std::cout << std::endl;
	}
}

void dataset::update()
{
    		int bbb = 0;
		for (int g = 0; g < x; g++)
		{
			for (int d = 0; d < y; d++)
			{
				switch (tab_ao[g][d])
				{
                case 'k':
                    aop_ao[g][d] = &k;
                    break;
				case 'p':
					aop_ao[g][d] = &p;
					break;
				case 'b':
					aop_ao[g][d] = &b[bbb];
					bbb++;
					break;
				case '0':
				    aop_ao[g][d] = 0;
					break;
				case 'e':
					aop_ao[g][d] = &e;
					break;
				case 'B':
					aop_ao[g][d] = &bu;
					break;
				}
			}
		}
}

void dataset::move(int varx, int vary, bool &condition, int &nr_2)
{

switch (tab_so[xp + varx][yp + vary])
			{
			case 'w':
				break;
			case 'p':

			case 'f':
				switch (tab_ao[xp + varx][yp + vary])
				{
                case 'k':
                    break;
				case 'd':
					break;
				case '0':
					tab_ao[xp + varx][yp + vary] = 'p';
					tab_ao[xp][yp] = '0';
					xp = xp + varx;
			yp = yp + vary;
					break;
				case 'b':
					if ((tab_so[xp + (varx * 2)][yp + (vary * 2)] == 'f' || tab_so[xp + (varx * 2)][yp + (vary * 2)] == 'p') && (tab_ao[xp + (varx * 2)][yp + (vary * 2)] == '0' || tab_ao[xp + (varx * 2)][yp + (vary * 2)] == 'e'))
					{
						if (tab_ao[xp + (varx * 2)][yp + (vary * 2)] == 'e') { e.death = true; }
						tab_ao[xp + (varx * 2)][yp + (vary * 2)] = 'b';
						tab_ao[xp + varx][yp + vary] = 'p';
						tab_ao[xp][yp] = '0';
						xp = xp + varx;
						yp = yp + vary;
						nr_2++;
					}
					break;
				case 'B':
					tab_ao[xp + varx][yp + vary] = '0';
					tab_ao[xp][yp] = '0';
					condition = false;
					break;
				case 'e':
					tab_ao[xp + varx][yp + vary] = 'e';
					tab_ao[xp][yp] = '0';
					condition = false;
					break;
				}
				break;
            /*case 'p':
				switch (tab_ao[xp + varx][yp + vary])
				{
				case '0':
					tab_ao[xp + varx][yp + vary] = 'p';
					tab_ao[xp][yp] = '0';
					xp = xp + varx;
			yp = yp + vary;
					break;
				case 'b':
					if ((tab_so[xp + (varx * 2)][yp + (vary * 2)] == 'f' || tab_so[xp + (varx * 2)][yp + (vary * 2)] == 'p') && tab_ao[xp + (varx * 2)][yp + (vary * 2)] == '0')
					{
						tab_ao[xp + (varx * 2)][yp + (vary * 2)] = 'b';
						tab_ao[xp + varx][yp + vary] = 'p';
						tab_ao[xp][yp] = '0';
						xp = xp + varx;
			yp = yp + vary;
					}
					break;
				case 'e':
					tab_ao[xp + varx][yp + vary] = 'e';
					tab_ao[xp][yp] = 'g';
					condition = false;
					break;
				}
				break;*/
			}

}

void dataset::move_enemy(int varx, int vary, bool &condition)
{

	switch (tab_so[xe + varx][ye + vary])
	{
	case 'w':
		break;
	case 'p':

	case 'f':
		switch (tab_ao[xe + varx][ye + vary])
		{
		case 'k':
			break;
		case 'd':
			break;
		case '0':
			tab_ao[xe + varx][ye + vary] = 'e';
			tab_ao[xe][ye] = '0';
			xe = xe + varx;
			ye = ye + vary;
			break;
		case 'b':
			break;
		case 'B':
			tab_ao[xp + varx][yp + vary] = '0';
			tab_ao[xp][yp] = '0';
			condition = false;
			break;
		case 'p':
			tab_ao[xe + varx][ye + vary] = 'e';
			tab_ao[xe][ye] = '0';
			xe = xe + varx;
			ye = ye + vary;
			condition = false;
			break;
		}
		break;
	/*case 'p':
		switch (tab_ao[xe + varx][ye + vary])
		{
		case '0':
			tab_ao[xe + varx][ye + vary] = 'e';
			tab_ao[xe][ye] = '0';
			xe = xe + varx;
			ye = ye + vary;
			break;
		case 'b':
			break;
		}
		break;*/
	}

}

void dataset::move_bullet(int varx, int vary, bool &condition)
{
	if (bu._state() == true)
	{
		switch (tab_so[bu._x() + varx][bu._y() + vary])
		{
		case 'w':
			tab_ao[bu._x()][bu._y()] = '0';
			bu.change_state(false);
			break;
		case 'p':

		case 'f':
			switch (tab_ao[bu._x() + varx][bu._y() + vary])
			{
			case 'k':
				tab_ao[bu._x()][bu._y()] = '0';
				bu.change_state(false);
				break;
			case 'd':
				tab_ao[bu._x()][bu._y()] = '0';
				bu.change_state(false);
				break;
			case 'b':
				tab_ao[bu._x()][bu._y()] = '0';
				bu.change_state(false);
				break;
			case 'e':
				tab_ao[bu._x()][bu._y()] = '0';
				bu.change_state(false);
				break;
			case '0':
				tab_ao[bu._x() + varx][bu._y() + vary] = 'B';
				tab_ao[bu._x()][bu._y()] = '0';
				bu.change_coord(varx, vary);

				break;
			case 'p':
				tab_ao[bu._x() + varx][bu._y() + vary] = '0';
				tab_ao[bu._x()][bu._y()] = '0';
				condition = false;
				break;
			}
			break;
			//case 'p':
			//	switch (tab_ao[bu._x() + varx][bu._y() + vary])
			//	{
			//	case '0':
			//		tab_ao[bu._x() + varx][bu._y() + vary] = 'B';
			//		tab_ao[bu._x()][bu._y()] = '0';
			//		bu.change_coord(varx, vary);
			//		break;
			//	case 'p':
			//		tab_ao[bu._x() + varx][bu._y() + vary] = '0';
			//		tab_ao[bu._x()][bu._y()] = 'b';
			//		condition = false;
			//		break;
			//	case 'b':
			//		break;
			//	}
			//	break;
		}
	}
}

void dataset::gameover(bool &condition)
{
    if(condition!=false)
    {
        condition = false;
        for(int n=0; n<x; n++)
        {
            for(int m=0; m<y; m++)
            {
                if(tab_so[n][m]=='p' && tab_ao[n][m]!='b') condition = true;
            }
        }
    }
}

void dataset::take_key()
{
    for(int x1 = -1; x1 < 2; x1++)
    {
        for(int y1 = -1; y1 < 2; y1++)
        {
            if(tab_ao[xp + x1][ yp + y1] == 'k')
            {
                p.have_key = true;
                tab_ao[xp + x1][yp + y1] = '0';
            }
        }
    }
}

void dataset::open_door()
{
	for (int x1 = -1; x1 < 2; x1++)
	{
		for (int y1 = -1; y1 < 2; y1++)
		{
			if (tab_ao[xp + x1][yp + y1] == 'd')
			{
				if (p.have_key == true)
				{
					tab_ao[xp + x1][yp + y1] = '0';
					p.have_key = false;
				}
			}
		}
	}
}

bool dataset::state_of_enemy()
{
	return e.death;
}

void dataset::shot(int counter)
{
	for (int coord_x = 0; coord_x < x; coord_x++)
	{
		for (int coord_y = 0; coord_y < x; coord_y++)
		{
			if (tab_so[coord_x][coord_y] == 'v')
			{
				if (tab_so[coord_x + 1][coord_y] == 'f')
				{
					if (tab_ao[coord_x + 1][coord_y] == '0')
					{
						if (bu._state() == false)
						{
							if ((counter % 10) == 0)
							{
								bu.reset_coord();
								tab_ao[coord_x][coord_y] = 'B';
								bu.change_state(true);
								bu.change_coord(coord_x, coord_y);
							}
						} 
					}
				}
			}
		}
	}
}