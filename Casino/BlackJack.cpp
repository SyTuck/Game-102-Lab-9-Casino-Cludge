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
	DEALER,
	PLAYER	
};
enum markers
{
	NOTPICKED,
	PICKED
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

	} while (deck[s][c] != NOTPICKED);

	deck[s][c] = PICKED;
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

	for (int y = DEALER; y <= PLAYER; y++)
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
void DisplayCards(bool showDeal, int bet, float ins, int plyHand)
{
	int cnt = 0;
	
	cout << "Current Bet: $" << bet << ".00  Insurance: $" << ins;
	if (ins == (int)ins)
	{
		cout << ".00";
	}
	else
	{
		cout << "0" << endl;
	}
	cout << endl;

	cout << "Player: ";
	do
	{
		cout << hands[PLAYER][cnt].face << hands[PLAYER][cnt].suit << ", ";
		cnt++;

	} while (hands[PLAYER][cnt].value != 0);


	cout << "\t Dealer: ";

	cnt = 0;
	do
	{

		if ((!showDeal) && (cnt == 0))
		{
			cout << "**, ";
			cnt++;
		}
		cout << hands[DEALER][cnt].face << hands[DEALER][cnt].suit << ", ";
		cnt++;

	} while (hands[DEALER][cnt].value != 0);

	cout << endl;
	cout << endl << "Player Hand Value: " << plyHand << endl;
	cout << endl;
}

/****************************************************************************
	PromptPlayer
	
	This function displays our supported blackjack options then inputs and
	returns the player's selection
	
*****************************************************************************/
blackjack PromptPlayer()
{
	bool GoodChoice = true;
	char pChoice = NOTHING;
	blackjack retval = NOTHING;

	cout << "[H]it [S]tay  S[P]lit" << endl;
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
		default:
		{
			GoodChoice = false;
		}
		}
	} while (!GoodChoice);

	return retval;
}

/****************************************************************
	YesKeyPressed
	
	This function waits for the player to enter Y, y, N, n
	and will return true for Y and y

****************************************************************/
bool YesKeyPressed()
{
	char yesno;

	do
	{
		yesno = WaitForKey();
	} while ((yesno != 'Y') && (yesno != 'y') &&
		(yesno != 'N') && (yesno != 'n'));

	if ((yesno == 'Y' ) || (yesno == 'y'))
	{
		return true;
	}
	else
	{
		return false;
	}

}

/****************************************************************
	GetBet

	This function prompts the user for the amount of money they
	wish to bet and returns the value of their wager

****************************************************************/
int GetBet()
{
	char betC;
	int retval;

	cout << "[1] $5  [2] $10  [3] $20 -- How much would you like to bet? ";

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
	float Insurance = 0.0;
	bool Stayed = false;
	bool StillPlaying = false;
	int PlayerHandValue, DealerHandValue;

	srand(time(0));
	
	system("cls");
	cout << "BlackJack Running" << endl;
	cout << endl;
	cout << "[1] for bet \t[2] for quit: ";
	cout << endl;
	cout << endl;
	choice = (int) (WaitForKey() - '0');

	if (choice == 1)
	{
		bet = GetBet();

		StillPlaying = true;

//		DealCards();
		DealerHandValue = DealOneCard(DEALER);
		DealerHandValue = DealOneCard(DEALER);

		PlayerHandValue = DealOneCard(PLAYER);
		PlayerHandValue = DealOneCard(PLAYER);

		DisplayCards(Stayed, bet, Insurance, PlayerHandValue);

		cout << endl;
		if (hands[DEALER][1].value == 11)
		{
			cout << "The Dealer has an Ace! Would you like to buy insurance? (Y/N): " << endl;

			if (YesKeyPressed)
			{
				Insurance = bet / 2;
			}
		}

		cout << "Do you wish to Double Down? (Y/N): " << endl;
		if (YesKeyPressed())
		{
			bet = bet * 2;
		}

		while (StillPlaying)
		{
			system("cls");
			cout << "Playing BlackJack at the Casino Cludge" << endl;
			cout << endl;

			DisplayCards(Stayed, bet, Insurance, PlayerHandValue);

			if (!Stayed)
			{
				PlayerChoice = PromptPlayer();
			}
			else
			{
			//	sleep()
			}

			if (PlayerChoice == HIT)
			{
				PlayerHandValue = DealOneCard(PLAYER);
				if (PlayerHandValue > 21)
				{
					StillPlaying = false;
				}
			}
			else if (PlayerChoice == STAY)
			{
				Stayed = true;

			}
		} //while still playing
	} //if betting (playing)
}