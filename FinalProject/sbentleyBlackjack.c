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
void fillDeck(Card* WDec, const char* wFace[], const char* wSuit[]);

int main(void)
{
	Card deck[CARDS];
	Card dealerHand[MAXCARDS];
	Card plyHand[MAXCARDS];
	const char* face[] = { "Ace", "Deuce", "Three", "Four", "Five", "Six",
	"Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	const char* suit[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	srand(time(NULL));

	fillDeck(deck, face, suit);
	printf("Deck is filled and not shuffled!\n");
	printDeck(deck);
	shuffle(deck);
	printf("Deck is shuffled\n");
	printDeck(deck);
	system("pause");
}
void fillDeck(Card* wDeck, const char* wFace[], const char* wSuit[])
{
	for (int i = 0; i < CARDS; ++i) {
		wDeck[i].face = wFace[i % FACES];
		wDeck[i].suit = wSuit[i / FACES];
		if (strcmp(wDeck[i].face, "Ace") == 0)
			wDeck[i].value = 11;
		else if ((strcmp(wDeck[i].face, "King") == 0) || (strcmp(wDeck[i].face,
			"Queen") == 0) || (strcmp(wDeck[i].face, "Jack") == 0))
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
void printDeck(Card* wDeck)
{
	int i = 0;
	for (i = 0; i < CARDS; ++i) {
		printf("%5s of %-8s%s", wDeck[i].face, wDeck[i].suit, (i + 1) % 4 ? " " :
			"\n");
	}
}