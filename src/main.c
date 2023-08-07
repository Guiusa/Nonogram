#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"
#include <time.h>

// To be used
void show_help(){
	printf("\
	[USAGE] nonogram\n\
	-h\t\tShows this message\n\
	-d [5,10,15]\tSets the grid's size\n\
	");
}

int main(int argc, char **argv){
	// Initial declarations
	srand(time(0));
	int n;
	short **gab, **m, **l, **c; 
	int x1, x2, y1, y2; 
	char str[12];
	char action;
	int vidas = 3;
	int lost;
	theme* tm;

	clear();
	
	// alocs dinamic variables
	tm 	= alocTheme();
	chooseTheme(tm);
	n = chooseSize(tm);
 	m 	= alocMat(n, n);
	gab	= alocMat(n, n);
	l		= alocMat(n, n/2 + 1);
	c		= alocMat(n/2 + 1, n);
	
	// Initializes matrixes	
	randMat(m, n);
	countLC(l, c, m, n);
	revealsX(gab, m, n);

	clear();
	/*
		this getchar is taking residue input from above functions, i don't really
		know what this does but if a take it off the pogram breaks with segfault
		:) 
	*/
	getchar();
	
	// Static graphics that needs to be printed just once
	printSeq(tm, l, c, n);
	printGrid(n);

	// These need to be printed at each play on the game
	printMat(tm, gab, n);
	printLife(tm, vidas, lost, n);
	printInputLine();

	// Gets the player input to be interpreted by genIntvls
	fgets(str, 12, stdin);
	
	/* 
		genIntvls take the input string and translates in x and y intervals
		also says if a play is for adding or removing
	*/
	while(genIntvls(str, &y1, &y2, &x1, &x2, &action) && vidas > 0){
		if(x1<0 || y1<0 || x2>=n || y2>=n){
			printf("Bad interval given\n");
			fgets(str, 12, stdin);
			continue;
		}
	
		/*
			Validates a play and stores the total of lifes lost in the variable
		*/
		lost = validatesPlay(x1, x2, y1, y2, action, &vidas, gab, m, n);
		if(vidas<=0){
			printEnd(tm, 0, m, n);
			break;
		}
		if(checkWin(gab, n)){
			printEnd(tm, 1, m, n);
			break;
		}
		printMat(tm, gab, n);
		printLife(tm, vidas, lost, n);
		printInputLine();
		fgets(str, 12, stdin);
		if(!strcmp(str, "stop")) break;
		printf("\n");
	}
	
	// Free of dinamic variables
	freeTheme(tm);
	freeMat(l, n);
	freeMat(c, n/2);
	freeMat(gab, n);
	freeMat(m, n);
	return 0;
}
