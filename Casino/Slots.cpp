/***************************************************************************
	Lab 9		For: James Dupuis

	By:


****************************************************************************/
#include <iostream>			//User screen and terminal IO utilities
#include <windows.h> 
#include <conio.h>
using namespace std;

char choice;

void RunSlots()
{

	while ((choice != 'Q') && (choice != 'q'))
	{
		cout << "-------------------------------" << "\t" << "111 = x10" << endl;
		cout << "|  x     |     x    |     x   |" << "\t" << "222 = x20" << endl;
		cout << "|        |          |         |" << "\t" << "333 = x30" << endl;
		cout << "|  7     |     7    |     7   |" << "\t" << "444 = x40" << endl;
		cout << "|        |          |         |" << "\t" << "555 = x50" << endl;
		cout << "|  3     |     3    |     3   |" << "\t" << "666 = x60" << endl;
		cout << "-------------------------------" << "\t" << "777 = x70" << endl;


		cout << "If you wish to leave press Q\q" << endl;
		if (_kbhit())
		{
			choice = _getch();
		}
		cout << "Slot Machine is Running" << endl;
	}
}

/*

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	COORD coord;
	CONSOLE_CURSOR_INFO lpCursor;

	lpCursor.bVisible = 0; // visible;
	lpCursor.dwSize = 1; // size;
	SetConsoleCursorInfo(hConsole, &lpCursor);

	coord.X = 0; // column;
	coord.Y = 0; // line;
	SetConsoleCursorPosition(hConsole,coord);

	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 48;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_BOLD; // FW_NORMAL; // FW_BOLD;
//	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	SetConsoleTextAttribute(hConsole, DEFAULTCOLOUR);

*/