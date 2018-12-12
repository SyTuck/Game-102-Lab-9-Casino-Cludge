#include <iostream>
#include <conio.h>
#include "Utility.h"

using namespace std;

/**************************************************************
	fixZeroes

	this function checks if a number has a decimal places and
	decides if there should be a "0" or a ".00" padded to it
	the cout

*************************************************************/

void fixZeroes(float num)
{
	if (num == int(num))
	{
		cout << ".00";
	}
	else
	{
		cout << "0";
	}
}

/********************************************
	WaitForKey

	This function gets and returns the keyboard
	entry immediately when the key is pressed;
	to speed up the game.

	There is a bug here if more than one key is
	pressed or many keys are pressed rapidly

*********************************************/

char WaitForKey()
{
	char key = -127;

	do
	{
		key = _getch();
	}							//not sure if getch can return with out a keypress
	while (key == -127);		//but here we make sure		

	cout << key;				//echo back the key because it's not automatic with this function

	return key;
}


/****************************************************************
	GetBet

	This function prompts the user for the amount of money they
	wish to bet and returns the value of their wager

****************************************************************/


float GetBet(float csh)
{
	char betC;
	float retval;

	if (csh >= 5.0)
	{
		cout << "[1] $5";
	}
	if (csh >= 10.0)
	{
		cout << " [2] $10";
	}
	if (csh >= 20.0)
	{
		cout << " [3] $20";
	}
	cout << endl;
	cout << "How much would you like to bet? ";

	do
	{
		betC = WaitForKey();
	} while ((betC <= '0') || (betC >= '4'));

	switch (betC)
	{
	case '1':
	{
		retval = 5;
		break;
	}
	case '2':
	{
		retval = 10;
		break;
	}
	case '3':
	{
		retval = 20;
	}
	}
	cout << endl;
	return retval;
}
