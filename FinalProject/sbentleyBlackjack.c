// FINAL PROJECT CSCI112		Alexander England		Sayge Bentley		Svara Jayasinghe -- View readme.md on the repo for extra details on who did what
//		Palomar College	Fall 23
//														BLACKJACK
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SUITS 4
#define FACES 13
#define CARDS 52
#define MAXCARDS 5
typedef struct {
	char* face;
	char* suit;
	int value;
} Card;


void printInstructions(void);
void printDeck(Card* wDeck);
void shuffle(Card* wDeck);
void fillDeck(Card* wDeck, const char* wFace[], const char* wSuit[]);
int evaluateValue(Card* deck, int* deckLength);
int dealerTurn(Card* deck, Card* dealerHand, int *dealerHandCardCount, int* cardNumber);
int playerTurn(Card* deck, Card* hand, int* handCardCount);
void playRound(Card* wDeck, Card* dealerHand, Card* plyHand, int* cardNumber);


int main(void)
{
	char playAgain;
	int cardNumber, dealerHandCardCount, plyHandCardCount, dealerValue = 0;

	int playerWins = 0, dealerWins = 0, gamesPlayed = 0, validChoice = 0;
	
	int playerResult = 0, dealerResult = 0;

	Card deck[CARDS];
	Card dealerHand[MAXCARDS];
	Card plyHand[MAXCARDS]; 
	const char* face[] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	const char* suit[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	srand(time(NULL));


	printInstructions();

	// MAIN GAME LOOP
	while (gamesPlayed < 5 && (playerWins < 3 || dealerWins < 3))
	{
		// Begin game readout. Fills deck, shuffles, organized.
		printf("\n*---------*BEGIN GAME %d*------------*\n", gamesPlayed + 1);
		fillDeck(deck, face, suit);
		printf("Deck is filled and not shuffled!\n");
		shuffle(deck);
		printf("Deck is shuffled\n");


		// Initial turn, passes out 2 cards to each deck.
		printf("\n*---------*INITAL TURN*------------*\n");
		playRound(deck, dealerHand, plyHand, &cardNumber);
		plyHandCardCount = 2;
		dealerHandCardCount = 2;
		
		// Player turn. Returns 0 if held or hit the card cap, returns 1 if busted.
		printf("\n*---------*PLAYER TURN*------------*\n");
		playerResult = playerTurn(deck, plyHand, &plyHandCardCount, &cardNumber);
		if (playerResult == 1)
		{
			printf("You lose!\n");
			dealerWins++;
			gamesPlayed++;
		}


		// Dealer turn. Only goes into the conditional if player held, other wise defaults to winning (the dealer wins if the player busts)
		// Returns 0 if held or hit the card cap, returns 1 if busted.
		else if (playerResult == 0)
		{
			printf("\n*---------*DEALER TURN*------------*\n");
			dealerResult = dealerTurn(deck, dealerHand, &dealerHandCardCount, &cardNumber);
			if (dealerResult == 1)
			{
				printf("You win!\n");
				playerWins++;
				gamesPlayed++;
			}
		}


		// Only goes through these conditionals if both the player & the dealer held.
		if (playerResult == 0 && dealerResult == 0)
		{
			if (evaluateValue(plyHand, &plyHandCardCount) > evaluateValue(dealerHand, &dealerHandCardCount))
			{
				printf("You win!\n");
				playerWins++;
			}
			else if (evaluateValue(plyHand, &plyHandCardCount) == evaluateValue(dealerHand, &dealerHandCardCount))
			{
				printf("A tie! A win will be tallied in both favors.\n");
				playerWins++;
				dealerWins++;
				gamesPlayed++;
			}
			else
			{
				printf("You lose!\n");
				dealerWins++;
				gamesPlayed++;
			}
		}

		printf("\n*---------*END OF MATCH*-----------*\n");
		printf("Player wins: %d | Dealer wins: %d \n", playerWins, dealerWins);


		// Loop to ensure validity of choice.
		validChoice = 0;
		while (validChoice == 0)
		{

			printf("Would you like to play again?(y/n)");
			scanf(" %c", &playAgain);
			if (playAgain == 'y' || playAgain == 'Y')
				validChoice = 1;
			else if (playAgain == 'n' || playAgain == 'N')
				break;
		}

		if (validChoice == 0)
			break;
	}

	if (playerWins > dealerWins)
	{
		printf("Good game, you won the set of 5 matches!\n");
	}
	else
	{
		printf("Sorry, you lost the set of 5 matches!\n");
	}
	
	system("pause");
}

void printInstructions()
{
	char choice;
	int validChoice = 0;
	printf("Welcome to blackjack! Written by Sayge Bentley, Svara Jayasinghe, and Alexander England.\n");
	printf("\n*---------*   RULES   *------------*\n");
	printf("You will play against the dealer AI, with 2 cards being handed out at the start. One of the dealer cards is hidden until their turn!\n");
	printf("Once begun, the player will be able to either draw more cards or hold. The players turn is over if they go over 21, or if they hold.\n");
	printf("If the player didn't 'bust', the dealer will have a turn. The dealer will not draw once over 17. The player wins if they have a higher number, or if the dealer busts.\n");

	// Loop to ensure validity of choice.
	while (validChoice == 0)
	{
		printf("Do you wish to play? (y/n): \n");
		scanf(" %c", &choice);
		if (choice == 'y' || choice == 'Y')
			return;
		else if (choice == 'n' || choice == 'N')
			exit(EXIT_SUCCESS);
	}
}

void playRound(Card* wDeck,Card* dealerHand, Card* plyHand, int* cardNumber)
{
	// Fills each hand with 2 cards each, and updates the cardNumber currently on top of the deck. Prints initial handouts.
 	for (*cardNumber = 0; *cardNumber < 2; (*cardNumber)++) {
		dealerHand[*cardNumber] = wDeck[*cardNumber];
		plyHand[*cardNumber] = wDeck[*cardNumber + 2];
	}
	(*cardNumber) += 2;
	printf("\n-> Dealer's hand: %s of %s, hidden\n", dealerHand[0].face, dealerHand[0].suit);
	printf("-> Your hand: %s of %s, %s of %s\n", plyHand[0].face, plyHand[0].suit, plyHand[1].face, plyHand[1].suit);
}


int dealerTurn(Card* deck, Card* dealerHand, int *dealerHandCardCount, int *cardNumber)
{
	// Initial readout
	printf("\n-> Dealer's hand: %s of %s, %s of %s\n", dealerHand[0].face, dealerHand[0].suit, dealerHand[1].face, dealerHand[1].suit);
	printf("---------------------\n");

	// Initial check
	if (evaluateValue(dealerHand, dealerHandCardCount) > 17)
	{
		printf("The dealer holds...\n");
		printf("Dealer's hand value: %d\n", evaluateValue(dealerHand, dealerHandCardCount));
		return (0);
	}
	else
	{
		for(int i = 0; i < MAXCARDS; i++)
		{
			printf("The dealer draws a card.\n");
			// Draw card
			dealerHand[*dealerHandCardCount] = deck[*cardNumber];
			(*dealerHandCardCount)++;
			(*cardNumber)++;


			// Display dealers hand
			printf("-> Dealer's hand: ");
			for (int i = 0; i < *dealerHandCardCount; i++) {
				printf("%s of %s ", dealerHand[i].face, dealerHand[i].suit);
			}
			printf("\n");
			printf("---------------------\n");

			// If the dealer hand is more than 21, bust. If more than 17, hold.
			if (evaluateValue(dealerHand, dealerHandCardCount) > 21)
			{
				printf("Busted! Dealer's hand value: %d\n", evaluateValue(dealerHand, dealerHandCardCount));
				return(1);
			}
			else if (evaluateValue(dealerHand, dealerHandCardCount) > 17)
			{
				printf("The dealer holds...\n");
				printf("Dealer's hand value: %d\n", evaluateValue(dealerHand, dealerHandCardCount));
				return(0);
			}

		}
	}
		// MAX CARDS IS 5
		printf("The dealer has reached the card cap, and must hold!\n");
		printf("Dealer's hand value: %d\n", evaluateValue(dealerHand, dealerHandCardCount));
		return(0);
	
}
int evaluateValue(Card* deck, int *deckLength)
{
	int deckValue = 0;
	int numAces = 0;
	// Count how many cards are "Ace", along with add the value of each card to a total ("Ace" default is 11)
	for (int i = 0; i < *deckLength; i++)
	{
		if (strcmp(deck[i].face, "Ace") == 0)
		{
			numAces++;
		}
		deckValue += deck[i].value;
	}
	// Dynamically chance "Ace" cards from 11 to 1 by updating the TOTAL, depending on which one busts the player or not
	for(int i = 0; i < numAces; i++)
	{
		if (deckValue <= 21)
			break;
		else
		{
			deckValue -= 10;
		}
	}
	return (deckValue);
}

int playerTurn(Card* deck, Card* hand, int* handCardCount, int* cardNumber)
{
	char choice;
	// Initial check.

	printf("\nDo you want to draw another card? (y/n):");
	scanf(" %c", &choice);

	while (choice == 'y' || choice == 'Y') {
		// Draw card
		hand[*handCardCount] = deck[*cardNumber];
		(*handCardCount)++;
		(*cardNumber)++;

		// Display players hand
		printf("-> Player's hand: ");
		for (int i = 0; i < *handCardCount; i++) {
			printf("%s of %s ", hand[i].face, hand[i].suit);
		}
		printf("\n");

		// Check if busted
		if (evaluateValue(hand, handCardCount) > 21) {
			printf("Busted! Player's hand value: %d\n", evaluateValue(hand, handCardCount));
			return (1);
		}
		else if (*handCardCount >= MAXCARDS)
		{
			printf("Card cap reached! Forcing a hold...\n");
			printf("---------------------\n");
			break;
		}
		printf("---------------------\n");

		// Ask the player to draw or stay
		printf("Do you want to draw another card? (y/n): ");
		scanf(" %c", &choice);
	}
	// Final print, if player declined drawing.
	printf("\n---------------------\n");
	printf("Player's hand value: %d\n", evaluateValue(hand, handCardCount));
	return(0);
}

void fillDeck(Card* wDeck, const char* wFace[], const char* wSuit[])
{
	for (int i = 0; i < CARDS; ++i) {
		wDeck[i].face = wFace[i % FACES];
		wDeck[i].suit = wSuit[i / FACES];
		if (strcmp(wDeck[i].face, "Ace") == 0)
			wDeck[i].value = 11;
		else if ((strcmp(wDeck[i].face, "King") == 0) || (strcmp(wDeck[i].face, "Queen") == 0) || (strcmp(wDeck[i].face, "Jack") == 0))
			wDeck[i].value = 10;
		else
			wDeck[i].value = (i + 1) % FACES;
	}
}

void shuffle(Card* wDeck)
{
	Card temp;
	int i = 0, j = 0;
	for (i = 0; i < CARDS; ++i) {
		j = rand() % CARDS;
		temp = wDeck[i];
		wDeck[i] = wDeck[j];
		wDeck[j] = temp;
	}
}
