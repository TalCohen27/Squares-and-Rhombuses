#ifndef _GOTOXY_H_
#define _GOTOXY_H_

#include <iostream>
using namespace std;
#include <windows.h>
#include <process.h>

// function definition -- requires windows.h
inline void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

// function definition -- requires process.h
inline void clrscr()
{
	system("cls");
}

#endif