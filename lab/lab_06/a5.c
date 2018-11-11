#include <stdio.h>

int angleChange (int com);


/* Location */
int main() {

	/* Initializing variables */
	int com1, com2, angle;
	char pos;

	/* I/O flow */
	printf("Type the position [N, S, W, E]: ");
	scanf("%c", &pos);
	printf("Type first command: ");
	scanf("%d", &com1);
	printf("Type second command: ");
	scanf("%d", &com2);

	/* VarCheck */
	if ((com1 != 1 && com1 != -1 && com1 != 2) || (com2 != 1 && com2 != -1 && com2 != 2)) {
		printf("Wrong command!\n");
		return 0;
	}

	/* Main part */
	switch (pos) {
		case 'N':
			angle = 0;
			break;
		case 'S':
			angle = 180;
			break;
		case 'W':
			angle = -90;
			break;
		case 'E':
			angle = 90;
			break;
		default:
			printf("Wrong position!\n");
			return 0;
	}
	angle = angle + angleChange(com1);
	angle = angle + angleChange(com2);

	/* Decoding */
	switch (angle) {
		case 0: case 360: case -360: 
			printf("Answer: North\n");
			break;
		case -90: case 270: 
			printf("Answer: West\n");
			break;
		case 90: case -270:
			printf("Answer: East\n");
			break;
		case 180: case -180: 
			printf("Answer: South\n");
			break;
	}

	return 0;
}


/* Custom function for changing angle */
int angleChange (int com) {
	switch (com) {
		case 1:
			return -90;
		case -1:
			return 90;
		case 2:
			return 180;
	}
}