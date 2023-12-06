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

void printDeck(Card* wDeck);
void shuffle(Card* wDeck);

void fillDeck(Card* wDeck, const char* wFace[], const char* wSuit[]);
int evaluateValue(Card* deck, int* deckLength);
void dealerTurn(Card* deck, Card* dealerHand, int *dealerValue, int *dealerHandCardCount);
void playerTurn(Card* deck[], Card* hand[], int* handCardCount);

int main(void)
{
	int dealerValue = 0;
	int dealerHandCardCount = 0;
	int plyHandCardCount = 0;
	Card deck[CARDS];
	Card dealerHand[MAXCARDS];
	Card plyHand[MAXCARDS]; 
	const char* face[] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	const char* suit[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	srand(time(NULL));

	fillDeck(deck, face, suit);
	printf("Deck is filled and not shuffled!\n");
	printDeck(deck);
	shuffle(deck);
	printf("Deck is shuffled\n");

	dealerTurn(deck, dealerHand, &dealerValue, &dealerHandCardCount);

	printDeck(deck);
	// Player's turn
	playerTurn(deck, plyHand, &plyHandCardCount);
	system("pause");
}
void dealerTurn(Card* deck, Card* dealerHand, int *dealerValue, int *dealerHandCardCount)
{
	// Initial check
	if (*dealerValue > 17)
	{
		printf("The dealer holds...\n");
		printf("Dealer card count: %d\n", *dealerHandCardCount);
		printf("Dealer card value: %d\n", *dealerValue);
		return;
	}
	else
	{
		// Dealer loop
		int dealerDone = 0;
		while(dealerDone != 1)
		{
			int i = rand() % CARDS;
			dealerHand[*dealerHandCardCount] = deck[i];
			*dealerValue = evaluateValue(dealerHand, dealerHandCardCount);
			(*dealerHandCardCount)++;
      
			if (*dealerValue > 21)
			{
				printf("The dealer busts!\n");
				printf("Dealer card count: %d\n", *dealerHandCardCount);
				printf("Dealer card value: %d\n", *dealerValue);
				dealerDone = 1;
			}
			else if (*dealerValue > 17)
			{
				printf("The dealer holds...\n");
				printf("Dealer card count: %d\n", *dealerHandCardCount);
				printf("Dealer card value: %d\n", *dealerValue);
				dealerDone = 1;
			}
			// MAX CARD COUNT IS 5
			else if (*dealerHandCardCount == MAXCARDS)
			{
				printf("The dealer has reached the card cap!\n");
				printf("Dealer card count: %d\n", *dealerHandCardCount);
				printf("Dealer card value: %d\n", *dealerValue);
				dealerDone = 1;
			}
			
		}
	}
}
int evaluateValue(Card* deck, int *deckLength)
{
	int value = 0;
	for(int i = 0; i <= *deckLength; i++)
	{
		value += deck[i].value;  
	}
	return (value);
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

// Remove when finished
void printDeck(Card* wDeck)
{
	int i = 0;
	for (i = 0; i < CARDS; ++i) {
		printf("%5s of %-8s%s", wDeck[i].face, wDeck[i].suit, (i + 1) % 4 ? " " :
			"\n");
	}
}

void playerTurn(Card* deck[], Card* hand[], int* handCardCount) 
{
	char choice;
	do {
		// Draw card
		hand[*handCardCount] = deck[*handCardCount];
		(*handCardCount)++;

		// Display players hand
		printf("Player's hand: ");
		for (int i = 0; i < *handCardCount; i++) {
			printf("%s of %s ", hand[i]->face, hand[i]->suit);
		}
		printf("\n");

		// Check if busted
		if (evaluateValue(hand, *handCardCount) > 21) {
			printf("Busted! Player's hand value: %d\n", evaluateValue(hand, *handCardCount));
			return;
		}

		// Ask the player to draw or stay
		printf("Do you want to draw another card? (y/n): ");
		scanf(" %c", &choice);
	} while (choice == 'y' || choice == 'Y');
}