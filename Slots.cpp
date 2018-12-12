/***************************************************************************
	Lab 9		For: James Dupuis

	By:


****************************************************************************/
#include <iostream>			//User screen and terminal IO utilities
#include <windows.h> 
#include <conio.h>
#include <stdlib.h>
#include "Slots.h"
#include "Utility.h"
using namespace std;

char choice;
int spin1 = 1;
int spin2 = 1;
int spin3 = 1;

void spinstop()
{
	if (_kbhit())
	{
		char delay = _getch();
	}


};

#define REELSIZE 10

int NUM_REELS[3][12] =
{ {1,2,3,4,5,6,7,8,9,10,1,2},
  {1,2,3,4,5,6,7,8,9,10,1,2},
  {1,2,3,4,5,6,7,8,9,10,1,2}
};

void RunSlots(float &cash)
{

	int spin = 0;
	int buttonpress = 0;

	system("cls");


	while (buttonpress < 3)
	{
		if (buttonpress < 1)
		{
			spin1++;
			if (spin1 > REELSIZE)
			{
				spin1 = 1;
			}
		}
		if (buttonpress < 2)
		{
			spin2++;		
			if (spin2 > REELSIZE)
			{
				spin2 = 1;
			}

		}
		if (buttonpress < 3)
		{
			spin3++;
			if (spin3 > REELSIZE)
			{
				spin3 = 1;
			}
		}

		system("cls");
		cout << NUM_REELS[0][spin1 - 1] << "\t" << NUM_REELS[1][spin2 - 1] << "\t" << NUM_REELS[2][spin3 - 1] << endl;
		cout << NUM_REELS[0][spin1] << "\t" << NUM_REELS[1][spin2] << "\t" << NUM_REELS[2][spin3] << endl;
		cout << NUM_REELS[0][spin1 + 1] << "\t" << NUM_REELS[1][spin2 + 1] << "\t" << NUM_REELS[2][spin3 + 1] << endl;
		
		if (_kbhit())
		{
			char delay = _getch();
			if (delay > 0)
			{
				buttonpress++;
				Sleep(100);
			}
		}

	}

	cout << endl;
	cout << "we did something!" << endl;
	system("pause");

}