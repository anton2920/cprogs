#include <stdio.h>


/* Month and season */
main() {

	/* Initializing variables */
	int month;

	/* I/O flow */
	printf("Type the number of month: ");
	scanf("%d", &month);

	/* Main part (switch) */
	switch (month) {
		case 1:
			printf("It's January, winter\n");
			break;
		case 2:
			printf("It's February, winter\n");
			break;
		case 3:
			printf("It's March, spring\n");
			break;
		case 4:
			printf("It's April, spring\n");
			break;
		case 5:
			printf("It's May, spring\n");
			break;
		case 6:
			printf("It's June, summer\n");
			break;
		case 7:
			printf("It's July, summer\n");
			break;
		case 8:
			printf("It's August, summer\n");
			break;
		case 9:
			printf("It's September, autumn\n");
			break;
		case 10:
			printf("It's October, autumn\n");
			break;
		case 11:
			printf("It's November, autumn\n");
			break;
		case 12:
			printf("It's December, winter\n");
			break;
		default:
			printf("You typed wrong number!\n");
			break;
	}
}