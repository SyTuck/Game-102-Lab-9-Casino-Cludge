/***************************************************************************
	Lab 9		For: James Dupuis

	By:


****************************************************************************/
#include <iostream>			//User screen and terminal IO utilities
#include <ctime>

using namespace std;

enum blackjack
{
	HIT,
	STAY,
	SPLIT,
	DOUBLE,
	INSURANCE
};

enum person
{
	EMPTY,
	DEALER = 1,
	PLAYER = 2	
};


struct card
{
	int value;
	char suit;
	char face;
};

#define NUMOFSUITS 4
#define NUMOFCARDS 13

int deck[4][13] = {};
card hands[2][10] = {};

/*************************************************************
	GetCardChar
	
	This function takes int/index from the deck array and
	returns a character for that card

**************************************************************/
const char FaceCards[] = { 'J','Q','K','A' };

char GetCardChar(int crd)
{
	int retval = 0;

	if (crd < 9)
	{
		retval = '2' + crd;
	}
	else
	{
		retval = FaceCards[crd - 10];
	}

	return retval;

}

/*************************************************************
	GetCardSuit

	This function takes the suit int/index and returns a
	character for the card's suit

***************************************************************/
const char Suits[] = { 'H','D','C','S' };

char GetCardSuit(int st)
{
	return Suits[st];
}

/***************************************************************
	GetCardValue

	This function takes the card int/index and returns the value
	of the card.
	
	For this 2 - 10  = face value ( 2 - 10)
	         J, Q, K = 10
				   A = 11 (or 1 to be decided by the calling program)

***************************************************************/
int GetCardValue(int crd)
{
	int retval = 0;

	if (crd < 9)
	{
		retval = 2 + crd;
	}
	else if (crd < 13)
	{
		retval = 10;
	}
	else if (crd == 13)
	{
		retval = 11;
	}

	return retval;	
}
/*************************************************************
	DealCards
	
	This function sets the initial cards for the player and the
	dealer
	
**************************************************************/
void DealCards()
{
	int suit = 0;
	int card = 0;

	for (int y = DEALER-1; y <= PLAYER-1; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			do
			{
				suit = rand() % 4;
				card = rand() % 13;

			} while (deck[suit][card] != EMPTY);

			deck[suit][card] = y+1;
			hands[y][x].face = GetCardChar(card);
			hands[y][x].suit = GetCardSuit(suit);
			hands[y][x].value = GetCardValue(card);
		}
	}
}

/***********************************************************************
	DisplayCards
	
	This function displays the Player's and the Dealers hands. It is
	passed a flag to say whether the Dealer's first card is shown or not
	
************************************************************************/
void DisplayCards(bool showDeal)
{
	int cnt = 0;

	cout << "Player: ";
	do
	{

		cout << hands[PLAYER - 1][cnt].face << hands[PLAYER - 1][cnt].suit << ", ";
		cnt++;

	} while (hands[PLAYER - 1][cnt].value != 0);

	cout << "\t Dealer: ";

	cnt = 0;
	do
	{

		if ((!showDeal) && (cnt == 0))
		{
			cout << "**, ";
			cnt++;
		}
		cout << hands[DEALER - 1][cnt].face << hands[DEALER - 1][cnt].suit << ", ";
		cnt++;

	} while (hands[DEALER - 1][cnt].value != 0);

	cout << endl;
}

void RunBlackJack()
{
	int choice;
	int blackjack = 0;
	int bet = 0;
	bool Stayed = false;
	bool StillPlaying = false;

	srand(time(0));
	
	system("cls");
	cout << "BlackJack Running" << endl;
	cout << endl;
	cout << "[1] for bet \t[2] for quit: ";
	cin >> choice;

	if (choice == 1)
	{
		cout << endl;
		cout << "[1] $5  [2] $10  [3] $20 -- How much to bet? ";
		cin >> bet;

		StillPlaying = true;

		DealCards();

		while (StillPlaying)
		{
			system("cls");
			cout << "Playing BlackJack at the Casino Cludge" << endl;
			cout << endl;

			DisplayCards(Stayed);

			switch (blackjack)
			{
			case HIT:
			{
				cout << "you chose hit" << endl;
				break;
			}
			case STAY:
			{
				cout << "you chose stay" << endl;
				break;
			}
			case SPLIT:
			{
				cout << "you chose split" << endl;
				break;
			}
			case DOUBLE:
			{
				cout << "you chose to double" << endl;
				break;
			}
			case INSURANCE:
			{
				cout << "you chose insurance" << endl;
				break;
			}
			}
			StillPlaying = false;
			system("pause");
		} //while still playing
	} //if betting (playing)
}