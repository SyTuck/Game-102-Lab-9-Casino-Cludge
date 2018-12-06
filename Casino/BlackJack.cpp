/***************************************************************************
	Lab 9		For: James Dupuis

	By:


****************************************************************************/
#include <iostream>			//User screen and terminal IO utilities
#include <ctime>
#include <conio.h>			//special keyboard library (to retrieve chars without waiting)

using namespace std;

enum blackjack
{
	NOTHING,
	HIT,
	STAY,
	SPLIT,
	DOUBLE,
	INSURANCE,
	TOTCHOICES
};

enum bjChoices
{
	lHIT = 'h',
	uHIT = 'H',
	lSTAY = 's',
	uSTAY = 'S',
	lSPLIT = 'p',
	uSPLIT = 'P',
	lDOUBLE = 'd',
	uDOUBLE = 'D',
	lINSURANCE = 'i',
	uINSURANCE = 'I'
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
#define MAXHANDSIZE 10
#define OVERSIZEDHAND 999

int deck[4][13] = {};
card hands[2][MAXHANDSIZE] = {};

#define DEALERid 0
#define PLAYERid 1

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
	PickACard

	the function will find an free card in the deck.
	The suit and card is returned in the refrence arguments

**************************************************************/
void PickACard(int &s, int &c)
{
	do
	{
		s = rand() % 4;
		c = rand() % 13;

	} while (deck[s][c] != EMPTY);
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
			PickACard(suit, card);

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
	cout << endl;
}

/****************************************************************************
	PromptPlayer
	
	This function displays out supported blackjack options then inputs and
	returns the player's selection
	
*****************************************************************************/
blackjack PromptPlayer()
{
	bool GoodChoice = true;
	char pChoice = NOTHING;
	blackjack retval = NOTHING;

	cout << "[H]it  [S]tay  S[P]lit  [D]ouble  [I]nsurance" << endl;
	cout << "Choose an option to play: " << endl;

	do
	{
		GoodChoice = true;
		pChoice = WaitForKey();

		switch (pChoice)
		{
		case lHIT:
		case uHIT:
		{
			retval = HIT;
			break;
		}
		case lSTAY:
		case uSTAY:
		{
			retval = STAY;
			break;
		}
		case lSPLIT:
		case uSPLIT:
		{
			retval = SPLIT;
			break;
		}
		case lDOUBLE:
		case uDOUBLE:
		{
			retval = DOUBLE;
			break;
		}
		case lINSURANCE:
		case uINSURANCE:
		{
			retval = INSURANCE;
			break;
		}
		default:
		{
			GoodChoice = false;
		}
		}
	} while (!GoodChoice);

	return retval;
}

/***************************************************************
	DealOneCard

	This function deals out one card to either the player or the
	dealer. It returns the current value of their hand

*****************************************************************/
int DealOneCard(int pID)
{
	int suit, card;
	int cnt = 0;
	int retval = 0;

	PickACard(suit, card);

	while (hands[pID][cnt].value != 0)		//find the next available spot
	{
		retval += hands[pID][cnt].value;
		
		cnt++;
		if (cnt >= MAXHANDSIZE)
		{
			retval = OVERSIZEDHAND;
		}
	}
	   
	if (retval < OVERSIZEDHAND)
	{
		hands[pID][cnt].face = GetCardChar(card);
		hands[pID][cnt].suit = GetCardSuit(suit);
		hands[pID][cnt].value = GetCardValue(card);
		retval += hands[pID][cnt].value;
	}
	return retval;
}

/*********************************************************************************************
	RunBlackJack

	This is the main method to run the blackjack table

**********************************************************************************************/
void RunBlackJack()
{
	int choice;
	blackjack PlayerChoice = NOTHING;
	int bet = 0;
	bool Stayed = false;
	bool StillPlaying = false;
	int PlayerHandValue, DealerHandValue;

	srand(time(0));
	
	system("cls");
	cout << "BlackJack Running" << endl;
	cout << endl;
	cout << "[1] for bet \t[2] for quit: ";
	choice = (int) (WaitForKey() - '0');

	if (choice == 1)
	{
		cout << endl;
		cout << "[1] $5  [2] $10  [3] $20 -- How much to bet? ";
		bet = (int) WaitForKey();

		StillPlaying = true;

//		DealCards();
		DealerHandValue = DealOneCard(DEALERid);
		DealerHandValue = DealOneCard(DEALERid);

		PlayerHandValue = DealOneCard(PLAYERid);
		PlayerHandValue = DealOneCard(PLAYERid);


		while (StillPlaying)
		{
			system("cls");
			cout << "Playing BlackJack at the Casino Cludge" << endl;
			cout << endl;

			DisplayCards(Stayed);

			cout << endl << "Player Hand Value: " << PlayerHandValue << endl;
			cout << endl;

			PlayerChoice = PromptPlayer();

			if (PlayerChoice == HIT)
			{
				PlayerHandValue = DealOneCard(PLAYERid);
				if (PlayerHandValue > 21)
				{
					StillPlaying = false;
				}
			}
		} //while still playing
	} //if betting (playing)
}