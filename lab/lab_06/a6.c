#include <stdio.h>


/* Pick a card */
int main() {

	/* Initializing variables */
	int n, m;

	/* I/O flow */
	printf("Type the card's number [6..14]: ");
	scanf("%d", &n);
	printf("Type the card's suit [1..4]: ");
	scanf("%d", &m);

	/* Main part */
	switch (n) {
		case 6:
			printf("Six");
			break;
		case 7:
			printf("Seven");
			break;
		case 8:
			printf("Eight");
			break;
		case 9:
			printf("Nine");
			break;
		case 10:
			printf("Ten");
			break;
		case 11:
			printf("Jack");
			break;
		case 12:
			printf("Queen");
			break;
		case 13:
			printf("King");
			break;
		case 14:
			printf("Ace");
			break;
		default:
			printf("Wrong number!\n");
			return 0;
	}
	switch (m) {
		case 1:
			printf(" of spades\n");
			break;
		case 2:
			printf(" of clubs\n");
			break;
		case 3:
			printf(" of diamonds\n");
			break;
		case 4:
			printf(" of hearts\n");
			break;
		default:
			printf("Wrong suit!\n");
			return 0;
	}


	return 0;
}