/***************************************************************************
	Lab 9		For: James Dupuis

	By:


****************************************************************************/
#include <iostream>			//User screen and terminal IO utilities
#include <windows.h> 

#include "BlackJack.h"
#include "Slots.h"

using namespace std;		//namespace to simplify iostream functions


enum Casino
{
	uBLACKJACK = 'B',
	lBLACKJACK = 'b',
	uSLOTS = 'S',
	lSLOTS = 's',
	uQUIT = 'Q',
	lQUIT = 'q'
};

char PlyGame;

const float STARTINGCASH = 500.00;

struct Gamer
{
	float Currency;
	float BlackJCurrency;
	int BlackJWins;
	int BlackJLoss;
	float SlotsCurrency;
	int SlotsWin;
	int SlotsLoss;

};




int main()
{

	Gamer Player;
	BlackJackTable Table1;
	SlotMachine Slot1;

	Player.Currency = STARTINGCASH;

	while (1)
	{
		system("cls");
		cout << "Welcome to the Casino Cludge" << endl;
		cout << endl;
		cout << "This game was made by Mitchell Labrecque, Jordan Tuck, and Manpreet" << endl;
		cout << endl;
		cout << "You have " << Player.Currency << " Dollars to play with" << endl;
		cout << endl;
		cout << "[B]lackjack \t[S]lot Machine \t[Q]uit" << endl;
		cout << "Choose a game: ";
		cin >> PlyGame;

		switch (PlyGame)
		{
		case uBLACKJACK:
		case lBLACKJACK:
		{
			RunBlackJack(Player.Currency);
			break;
		}
		case uSLOTS:
		case lSLOTS:
		{
			RunSlots();
			break;
		}
		case uQUIT:
		case lQUIT:
		{
		
			return 0;
		}
	default:
		{
		}
		}

		if (Player.Currency <= 0.0)
		{
			cout << endl;
			cout << "Thank you for your money. Please come again anytime." << endl;
			system("pause");
			return 0;
		}

		system("pause");


//		if (_kbhit())
//		{
//			char delay = _getch();
//		}

	}
}