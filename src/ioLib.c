#include "ioLib.h"

// Manage memory occupied by a theme structure 
theme* alocTheme(){
	theme* t = malloc(sizeof(theme));
	t->HIDN 	= malloc(20 * sizeof(char));
	t->FOUND = malloc(20 * sizeof(char));
	t->XX 		= malloc(20 * sizeof(char));
	t->LTTRS = malloc(20 * sizeof(char));
	t->NRML 	= malloc(20 * sizeof(char));
	return t;
}

void freeTheme(theme* t){
	free(t->HIDN);
	free(t->FOUND);
	free(t->XX);
	free(t->LTTRS);
	free(t->NRML);
	free(t);
}
//##############################################################################

/*
* Interface to choose a theme to the game
*/
void chooseTheme(theme* t, int c){
	int k;
	if(c){
		k = c;
	 	goto switch_jump;
	}
	printf("CHOOSE A THEME:\n\n");
	printf("(1)\tHatsune Miku\t\t\t");
	printf("\e[0;90m██ \e[0;36m██ \e[0;107m\e[1;35mXX\e[0m\n"); 
	printf("(2)\tEverywhere is now Brazil\t");
	printf("\e[0;33m██ \e[0;34m██ \e[0;107m\e[1;32mXX\e[0m\n"); 
	printf("(3)\tOMG Miles Morales???\t\t");
	printf("\e[0;30m██ \e[0;31m██ \e[0;40m\e[1;34mXX\e[0m\n"); 
	printf("(4)\tBlack & White\t\t\t");
	printf("\e[0;30m██ \e[0;97m██ \e[0;40m\e[1;97mXX\e[0m\n"); 
	scanf("%d", &k);
	while(k<1 || k>4){
		printf("Wrong choice :(\n");
		scanf("%d", &k);
	}
	switch_jump:
	switch (k) {
		case 1:
			strcpy(t->HIDN, "\e[0;90m");
			strcpy(t->FOUND, "\e[0;36m");
			strcpy(t->XX, "\e[0;107m\e[1;35m");
			break;
		case 2:
			strcpy(t->HIDN, "\e[0;33m");
			strcpy(t->FOUND, "\e[0;34m");
			strcpy(t->XX, "\e[0;107m\e[1;32m");
			break;
		case 3:
			strcpy(t->HIDN, "\e[0;30m");
			strcpy(t->FOUND, "\e[0;31m");
			strcpy(t->XX, "\e[0;40m\e[1;34m");
			break;
		case 4:
			strcpy(t->HIDN, "\e[0;30m");
			strcpy(t->FOUND, "\e[0;97m");
			strcpy(t->XX, "\e[0;40m\e[1;97m");
			break;
		default:
			strcpy(t->HIDN, "\e[0;90m");
			strcpy(t->FOUND, "\e[0;36m");
			strcpy(t->XX, "\e[0;107m\e[1;35m");
	}
	strcpy(t->LTTRS, "\e[1;100m");
	strcpy(t->NRML, "\e[0m");
}

/*
*	Prints all sequences found in the matrix after the random algoritm found in
* actionsLib.h
*/
void printSeq(theme* t, short** l, short** c, int n){
	int gap_j = ((n/2+1)*3) + 2;
	for(int i = 0; i<n/2 + 1; i++){
		for(int j = 0; j<n; j++){
			printf("\e[%d;%dH", i+1, j*4 + gap_j + (j/5));
			if(c[i][j]){ 
				printf("%s%3d %s", t->LTTRS, c[i][j], t->NRML);
			} else printf("%s    %s", t->LTTRS, t->NRML);
		}
	}

	int gap_i = (n/2) + 3;
	for(int i = 0; i<n; i++){
		printf("\e[%d;1H", (i*2)+gap_i + (i/5));
		for(int j = 0; j<n/2 + 1; j++){
			if(l[i][j]){
				printf("%s%3d%s", t->LTTRS, l[i][j], t->NRML);
			} else printf("%s   %s", t->LTTRS, t->NRML);
		}
		printf("\e[%d;1H", (i*2)+gap_i+1+(i/5));
		for(int j = 0; j<n/2 + 1; j++)
			printf("%s   %s", t->LTTRS, t->NRML);
	}

	
	for(int k = 0; k<n; k++){
		printf("\e[%d;%dH%d", gap_i + (k*2) + (k/5), gap_j + n*4 + (n/5+1), k+1);
		printf("\e[%d;%dH %2d ", gap_i + (n*2) + (n/5), gap_j + (k*4) + (k/5), k+1);
	}
}

/*
* Prints the squares visible by player accordingly to the value in each cell
* of the matrix
*/
void printMat(theme* t, short** m, int n){
	int gap_i = n/2 + 3;
	int gap_j = 3*(n/2 + 1) + 2;
	for(int i = 0; i < n * 2; i++){
		for(int j = 0; j<n; j++){
			printf("\e[%d;%dH", i + gap_i + i/10, j*4 + gap_j + j/5);
			if(!m[i/2][j]){
				printf("%s████%s", t->HIDN, t->NRML);
			} else if (m[i/2][j] == 1){
				printf("%s████%s", t->FOUND, t->NRML);
			} else
				printf("%sXXXX%s", t->XX, t->NRML);
		}
	}
}

/*
* Prints available lives and, if the player lost any life in last play, prints
* that info too
*/
void printLife(theme* t, int life, int lost, int n){
	int gap_i = (n/2+1) + (n*2) + (n/5+1) + 2;
	printf("\e[%d;1H", gap_i); 
	if(lost==1)
		printf(" %s \e[1;31mYOU LOST %d LIFE IN THE LAST PLAY%s\n", t->XX, lost, t->NRML);
	if(lost>1)
		printf(" %s \e[1;31mYOU LOST %d LIVES IN THE LAST PLAY%s\n", t->XX, lost, t->NRML);
	if(!lost)
		printf(" %s                                  %s\n", t->XX, t->NRML);
	 printf(" %s          LIVES LEFT: %d           %s\n", t->XX, life, t->NRML);
}

/*
* Clears the screen with ansii sequences
*/
void clear(){
	printf("\e[2J\e[H");
}

/*
* Interface so the player can choose if the matrix will have 5, 10 or 15 lines
* and column
*/

/*
* Reveals all cells to player and a message of win or loss
*/
void printEnd(theme* t, int WL, short** m, int n){
	clear();
	for(int i = 0; i<n; i++)
		for(int k = 0; k<2; k++){
			for(int j = 0; j<n; j++)
				if(m[i][j] == 1){
					printf("%s████%s", t->FOUND, t->NRML);
				} else
					printf("%sXXXX%s", t->XX, t->NRML);
			printf("\n");
		}
	if(WL){
		printf("%s\nYOU WON!!%s \n", t->XX, t->NRML);
	} else
		printf("%s\nYOU LOST ALL YOUR LIFES!!%s \n", t->XX, t->NRML);
}


int chooseSize(theme* t){
	int k;
	printf("%sCHOOSE THE GRID SIZE:\n(1) - 5\n(2) - 10\n(3) - 15%s\n", t->XX, t->NRML);
	scanf("%d", &k);
	while(k<1 || k>3){
		printf("%sWRONG CHOICE :(%s\n", t->XX, t->NRML);
		scanf(" %d", &k);
	}
	return k*5;
}

/*
* Debug function, prints error and correct usage in program calling
*/
void error(theme* t, char* err, char* usg){
	printf("\e[1;31m%s\e[0m\n", err);
	if(usg)
		printf("%s%s%s\n", t->XX, usg, t->NRML);
}

void print5Grid(){
	int gap_i = 4;
	int gap_j = 10;

	//	┏━━━━━━━━━━━━━━━━━━━━━━━━┓
	printf("\e[%d;%dH%s%s%s%s%s%s\n", gap_i, gap_j, CORNER_TL, LINE_H, LINE_H, LINE_H, LINE_H, CORNER_TR);
	
	//	┃                        ┃
	for(int i = 0; i<10; i++)
		printf("\e[%d;%dH%s  %s%s%s%s  %s\n", gap_i + i + 1, gap_j, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V);
	
	//	┗━━━━━━━━━━━━━━━━━━━━━━━━┛
	printf("\e[%d;%dH%s%s%s%s%s%s\n", gap_i + 11, gap_j, CORNER_BL, LINE_H, LINE_H, LINE_H, LINE_H, CORNER_BR);
}

void print10Grid(){
	int gap_i = 7;
	int gap_j = 19;
	//	┏━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┓
	printf("\e[%d;%dH%s%s%s%s%s%s%s%s%s%s%s\n", gap_i, gap_j, CORNER_TL, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_T, LINE_H, LINE_H, LINE_H, LINE_H, CORNER_TR);

	//	┃                        ┃                        ┃
	for(int i = 0; i<10; i++)
		printf("\e[%d;%dH%s  %s%s%s%s  %s  %s%s%s%s  %s\n", gap_i + i + 1, gap_j,  LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V); 

	gap_i += 11;
	//	┣━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━┫
	printf("\e[%d;%dH%s%s%s%s%s%s%s%s%s%s%s\n", gap_i, gap_j,  MIDDLE_L, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_C, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_R);

	//	┃                        ┃                        ┃
	for(int i = 0; i<10; i++)
		printf("\e[%d;%dH%s  %s%s%s%s  %s  %s%s%s%s  %s\n", gap_i + i + 1, gap_j,  LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V); 
	
	gap_i += 11;
	//	┗━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┛
	printf("\e[%d;%dH%s%s%s%s%s%s%s%s%s%s%s\n", gap_i, gap_j, CORNER_BL, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_B, LINE_H, LINE_H, LINE_H, LINE_H, CORNER_BR);
}

void print15Grid(){
	int gap_i = 9;
	int gap_j = 25;

	//	┏━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┓
	printf("\e[%d;%dH%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", gap_i, gap_j,  CORNER_TL, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_T, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_T, LINE_H, LINE_H, LINE_H, LINE_H, CORNER_TR);

	//	┃                        ┃                        ┃                        ┃
	for(int i = 0; i<10; i++)
		printf("\e[%d;%dH%s  %s%s%s%s  %s  %s%s%s%s  %s  %s%s%s%s  %s\n", gap_i + i + 1, gap_j, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V); 

	gap_i += 11;

	//	┣━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━┫
	printf("\e[%d;%dH%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", gap_i, gap_j, MIDDLE_L, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_C, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_C, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_R);

	//	┃                        ┃                        ┃                        ┃
	for(int i = 0; i<10; i++)
		printf("\e[%d;%dH%s  %s%s%s%s  %s  %s%s%s%s  %s  %s%s%s%s  %s\n", gap_i + i + 1, gap_j, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V); 

	gap_i += 11;
	
	//	┣━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━┫
	printf("\e[%d;%dH%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", gap_i, gap_j, MIDDLE_L, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_C, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_C, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_R);

	for(int i = 0; i<10; i++)
		printf("\e[%d;%dH%s  %s%s%s%s  %s  %s%s%s%s  %s  %s%s%s%s  %s\n", gap_i + i + 1, gap_j, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V, EMPTY, EMPTY, EMPTY, EMPTY, LINE_V); 

	gap_i += 11;
	
		//	┗━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━┛
	printf("\e[%d;%dH%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n", gap_i, gap_j, CORNER_BL, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_B, LINE_H, LINE_H, LINE_H, LINE_H, MIDDLE_B, LINE_H, LINE_H, LINE_H, LINE_H, CORNER_BR);
}

/*
* Accordingly with to matrix size, calls one of the tree imediatly above 
* functions to print the grid with special character
* Yeah i know it could be better done
*/
void printGrid(int n){
	if(n == 5){
		print5Grid();
	}	else if (n == 10) {
		print10Grid();
	} else
		print15Grid();
}

/*
* prints the line were the player's input will be drawn
*/
void printInputLine(int missed){
	printf("               <-- YOUR INPUT HERE");
	if(missed == 1){
		printf(" | \e[1;41minput must be between boundaries\e[0m             \r");
	} else if(missed == 2) {
		printf(" | \e[1;42mUse <x | x1-x2>,<y | y1-y2> <(A) | r> OR stop\e[0m\r");
	} else
		printf(" |                                              \r");
}
