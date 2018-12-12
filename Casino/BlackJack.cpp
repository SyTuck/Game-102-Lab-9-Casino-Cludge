/***************************************************************************
	Lab 9		For: James Dupuis

	By:


****************************************************************************/
#include <iostream>			//User screen and terminal IO utilities
#include <ctime>
#include <conio.h>			//special keyboard library (to retrieve chars without waiting)
#include <windows.h>

using namespace std;

enum blackjack
{
	NOTHING,
	HIT,
	STAY,
	SPLIT,
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
	PLAYER,
	plySPLIT,
	plySPLITb,
	plySPLITc
};
enum markers
{
	NOTPICKED,
	PICKED
};

#define NUMOFSUITS 4
#define NUMOFCARDS 13
#define MAXHANDSIZE 11			 	//4 aces + 4 2's + 3 3's = 21 (worst possible scenario at astromical odds (greater than 1:8,000,000)
#define OVERSIZEDHAND 999

struct card
{
	int value;
	char suit;
	char face;
};

struct player
{
	card hand[MAXHANDSIZE] = {};
	int cardsInHand = 0;
	int acesInHand = 0;
	bool isDealer = false;
	int handValue = 0;
	float insurance = 0.0;
	int bet = 0;
	bool stayed = false;
	bool doubledDown = false;
	bool busted = false;
};

int deck[4][13] = {};
//card hands[3][MAXHANDSIZE] = {};

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
/*************************************************************
	GetCardChar
	
	This function takes int/index from the deck array and
	returns a character for that card

**************************************************************/
const char FaceCards[] = { 'J','Q','K','A' };

char GetCardChar(int crd)
{
	int retval = 0;

	if (crd < 8)
	{
		retval = '2' + crd;
	}
	else if (crd == 8)				//special exception for 10
	{								//only using a single char so 
		retval = '0';				//will have to put in the '1'
	}								//when the hand is shown
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
	The suit, card, and value is returned in the card refrence
	argument

**************************************************************/
void PickACard(card *crd)
{
	int f, s;

	do
	{
		s = rand() % 4;
		f = rand() % 13;

	} while (deck[s][f] != NOTPICKED);

	deck[s][f] = PICKED;
	crd->face = GetCardChar(f);
	crd->suit = GetCardSuit(s);
	crd->value = GetCardValue(f);
}
/*************************************************************
	DealCards
	
	This function sets the initial cards for the player and the
	dealer
	
**************************************************************/
/*void DealCards()
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
*/

/******************************************************
	showCards

	this function takes a player and displays
	the cards in their hands.

	It includes support for suit colour but needs
	to be told if hiding the dealer's first card

*******************************************************/
#define DEFAULTCOLOUR 0x07
#define REDCOLOUR 0x0c
#define GREYCOLOUR 0x08
#define WHITECOLOUR 0x0f

void showCards(player plyr, bool fsthidden)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int x = 0; x < plyr.cardsInHand; x++)
	{
		SetConsoleTextAttribute(hConsole, WHITECOLOUR);
		if ((x == 0) && (fsthidden))
		{
			cout << "**";
		}
		else
		{
			if (plyr.hand[x].face == '0')	//exception for 10 because we're only using a single char
			{
				cout << '1';
			}
			cout << plyr.hand[x].face;
			if ((plyr.hand[x].suit == 'H') || (plyr.hand[x].suit == 'D'))
			{
				SetConsoleTextAttribute(hConsole, REDCOLOUR);
			}
			else
			{
				SetConsoleTextAttribute(hConsole, GREYCOLOUR);
			}
			cout << plyr.hand[x].suit;
		}
		SetConsoleTextAttribute(hConsole, DEFAULTCOLOUR);
		cout << ", ";
	}


}
/***********************************************************************
	DisplayTable
	
	This function displays the Player's and the Dealers hands. It is
	passed a flag to say whether the Dealer's first card is shown or not
	
************************************************************************/
void DisplayTable(player tbl[], int plyrs, float csh)
{
	cout << "Playing BlackJack at the Casino Cludge" << endl;
	cout << endl;
	cout << "Available funds: $" << csh;
	fixZeroes(csh);
	cout << "  Insurance Purchased: $" << tbl[PLAYER].insurance;
	fixZeroes(tbl[PLAYER].insurance);
	cout << endl;
	cout << endl;
	cout << "Main Hand: $" << tbl[PLAYER].bet;
	fixZeroes(tbl[PLAYER].bet);
	cout << "  ";

	showCards(tbl[PLAYER], false);
	cout << "  Hand Value: " << tbl[PLAYER].handValue << endl;

	if (tbl[plySPLIT].cardsInHand != 0)
	{
		cout << "Split Bet: $" << tbl[plySPLIT].bet << ".00";
		showCards(tbl[plySPLIT], false);
		cout << endl;
		cout << "Split Hand Value: " << tbl[PLAYER].handValue << endl;
	}

	cout << endl;
	cout << "Dealer's Hand: ";
	cout << endl;
	showCards(tbl[DEALER], !tbl[PLAYER].stayed);  // &tbl[plySPLIT].stayed));

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

/***************************************************************
	DealOneCard

	This function deals out one card to either the player or the
	dealer. It returns the current value of their hand

*****************************************************************/
void DealOneCard(player &plyr)
{
	card *cp = &(plyr.hand[plyr.cardsInHand]);		//a shortcut pointer

	PickACard(cp);

	plyr.handValue += cp->value;
	if ((plyr.handValue > 21) && (cp->face == 'A'))	//if player busts with an ace
	{												//roll back the ace to a value of 1
		plyr.handValue -= 10;
	}

	plyr.cardsInHand++;
}

/*********************************************************************************************
	RunBlackJack

	This is the main method to run the blackjack table

**********************************************************************************************/
void RunBlackJack(float &Cash)
{
	int choice;
	blackjack PlayerChoice = NOTHING;
	float bet = 0.0;

	bool Stayed = false;
	bool split = false;
	bool doubleDowned = false;
	bool StillPlaying = false;
	int PlayerHandValue, DealerHandValue;

	int NumOfHands = 2;

	player tableHands[5] = {};
//	player Player;
//	player Split;

	srand(time(0));
	
	do
	{
		system("cls");
		cout << "Welcome to the BlackJack table at the Casino Cludge" << endl;
		cout << endl;
		if (Cash < 5.0)
		{
			cout << "Sorry, you do not have enough funds for this table." << endl;
			system("pause");
			choice = 2;
		}
		else
		{
			cout << "[1] for bet \t[2] for quit: ";
			choice = (int)(WaitForKey() - '0');
			cout << endl;
			cout << endl;
		}

		if (choice == 1)
		{
			player tableHands[5] = {};		//keeping it within this scope makes a cheap way to reinitialize the players hands
			StillPlaying = true;

			bet = GetBet(Cash);
			tableHands[PLAYER].bet = bet;
			Cash -= (int)tableHands[PLAYER].bet;

			system("cls");
			StillPlaying = true;

			//		DealCards();
			tableHands[DEALER].isDealer = true;
			DealOneCard(tableHands[DEALER]);
			DealOneCard(tableHands[DEALER]);

			DealOneCard(tableHands[PLAYER]);
			DealOneCard(tableHands[PLAYER]);

			DisplayTable(tableHands, NumOfHands, Cash);

			if (tableHands[PLAYER].handValue == 21)
			{
				cout << "BLACKJACK!! Congrats. You have won: $" << bet * 1.5;
				fixZeroes(bet * 1.5);
				cout << endl;
				Cash += (bet * 2.5);
			}
			else
			{
				cout << endl;
				if ((tableHands[DEALER].hand[1].value == 11) && (Cash >= bet / 2.0))
				{
					cout << "The Dealer has an Ace! Would you like to buy insurance? (Y/N) : ";

					if (YesKeyPressed())
					{
						tableHands[PLAYER].insurance = (float)bet / 2.0;
						Cash -= tableHands[PLAYER].insurance;
					}
				}
				/*
						int freeSplit = 2;
						int Check4Split = 1;
						while (tableHands[PLAYER + spltCnt].hand[0].face == tableHands[PLAYER + spltCnt].hand[1].face)
						{
							cout << "You got a pair! Do you wish to split? (Y/N): ";
							if (!YesKeyPressed())
							{
								break;
							}
							else  //redundant else for form
							{
								tableHands[PLAYER + spltCnt + 1].hand[0].face = tableHands[PLAYER + spltCnt].hand[1].face;
								tableHands[PLAYER + spltCnt + 1].hand[0].suit = tableHands[PLAYER + spltCnt].hand[1].suit;
								tableHands[PLAYER + spltCnt + 1].hand[0].value = tableHands[PLAYER + spltCnt].hand[1].value;
								tableHands[PLAYER + spltCnt + 1].cardsInHand = 1;
								tableHands[PLAYER + spltCnt + 1].handValue = tableHands[PLAYER + spltCnt + 1].hand[0].value;
								tableHands[PLAYER + spltCnt].cardsInHand = 1;
								tableHands[PLAYER + spltCnt].handValue = tableHands[PLAYER + spltCnt].hand[0].value;

								DealOneCard(tableHands[PLAYER]);
								DealOneCard(tableHands[PLAYER]);
							}
						}
				*/
				if (Cash >= bet)
				{
					cout << "Do you wish to Double Down? (Y/N): ";
					if (YesKeyPressed())
					{
						Cash -= bet;
						tableHands[PLAYER].bet += bet;
						tableHands[PLAYER].doubledDown = true;
					}
				}
				while (StillPlaying)
				{
					system("cls");

					DisplayTable(tableHands, NumOfHands, Cash);

					if (tableHands[PLAYER].doubledDown)
					{
						PlayerChoice = HIT;
						tableHands[PLAYER].doubledDown = false;				//player gets one card, so don't do this again
						tableHands[PLAYER].stayed = true;
					}
					else if (!tableHands[PLAYER].stayed)
					{
						cout << endl;
						PlayerChoice = PromptPlayer();
					}
					else
					{
						//sleep(250);
					}

					if (PlayerChoice == HIT)
					{
						DealOneCard(tableHands[PLAYER]);
						if (tableHands[PLAYER].handValue > 21)
						{
							system("cls");
							DisplayTable(tableHands, NumOfHands, Cash);
							cout << "You have busted! Dealer wins this hand." << endl;
							system("pause");
							StillPlaying = false;
							tableHands[PLAYER].busted = true;
						}
					}
					else if (PlayerChoice == STAY)
					{
						tableHands[PLAYER].stayed = true;
						StillPlaying = false;
					}
				} //while still playing
				system("cls");
				if (tableHands[DEALER].handValue == 21)			//first check for blackjack
				{
					DisplayTable(tableHands, NumOfHands, Cash);
					cout << "Dealer has BlackJack!";
					if (!tableHands[PLAYER].busted)
					{
						cout << "You lost $" << tableHands[PLAYER].bet;
						fixZeroes(tableHands[PLAYER].bet);
					}
					cout << endl;
					if (tableHands[PLAYER].insurance)
					{
						cout << "Your insurance payout is $" << tableHands[PLAYER].insurance * 2;
						fixZeroes(tableHands[PLAYER].insurance * 2);
						cout << endl;
						Cash = tableHands[PLAYER].insurance * 2;
					}
				}
				if (!tableHands[PLAYER].busted)
				{
					while (tableHands[DEALER].handValue < 17)
					{
						DealOneCard(tableHands[DEALER]);
					}
					DisplayTable(tableHands, NumOfHands, Cash);

					if (tableHands[DEALER].handValue > 21)
					{
						cout << "The Dealer has busted. You won $" << tableHands[PLAYER].bet;
						fixZeroes(tableHands[PLAYER].bet);
						Cash += (tableHands[PLAYER].bet * 2);
					}
					else if (tableHands[DEALER].handValue > tableHands[PLAYER].handValue)
					{
						cout << "The Dealer beat your hand. You lost $" << tableHands[PLAYER].bet;
						fixZeroes(tableHands[PLAYER].bet);
						cout << endl;
					}
					else if (tableHands[DEALER].handValue == tableHands[PLAYER].handValue)
					{
						cout << "Your hands are equal. You have regained your bet of $" << tableHands[PLAYER].bet;
						fixZeroes(tableHands[PLAYER].bet);
						cout << endl;
						Cash += tableHands[PLAYER].bet;
					}
					else
					{
						cout << "You beat the Dealer. You won $" << tableHands[PLAYER].bet;
						fixZeroes(tableHands[PLAYER].bet);
						Cash += (tableHands[PLAYER].bet * 2);
					}
				}//if not busted
			}	//else player did not have blackjack
		} //if betting (playing)
	} while (choice != 2);
}