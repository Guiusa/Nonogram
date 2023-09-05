#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"
#include "fileLib.h"
#include <time.h>
#include <unistd.h>
#include <getopt.h>

void show_help(char* name){
	printf("[USAGE] %s\n\
-h\t\tShows this message\n\
-t [1-4]\t\tSets theme automatically\n\
-s [5,10,15]\tSets the grid's size\n\
", name);
}

int main(int argc, char **argv){
	// Initial declarations
	srand(time(0));
	int n = 0;
	int tc = 0;
	int opt;
	short **gab, **m, **l, **c; 
	int x1, x2, y1, y2; 
	char str[12];
	char action;
	int vidas = 3;
	int lost = 0;
	int intvlsRet;
	theme* tm;
	int flag_size = 0;
	int flag_theme = 0;
	char *variabless = (char*) malloc(100 * sizeof(char));

	while((opt = getopt(argc, argv, "s:t:h")) > 0){
		switch(opt){
			case 'h':
				show_help(argv[0]);
				return 0;
			case 's':
				n = atoi(optarg);
				if( n != 5 && n != 10 && n != 15){
					fprintf(stderr, "Size value should be 5, 10 or 15\n");
					return 1;
				}
				break;
			case 't':
				tc = atoi(optarg);
				if(tc<1 || tc>4){
					fprintf(stderr, "Theme codes are only 1, 2, 3 or 4");
					return 1;
				}
				break;
			default:
				fprintf(stderr, "Invalid option\n");
				return -1;
		}
	}
	
	getVariables(&tc, &n);
	if(tc) flag_theme = 1;
	if(n) flag_size = 1;

	clear();
	
	// alocs dinamic variables
	tm 	= alocTheme();
	chooseTheme(tm, tc);
	if(!n){ 
		n = chooseSize(tm);
	}
	
	m 	= alocMat(n, n);
	gab	= alocMat(n, n);
	l		= alocMat(n, n/2 + 1);
	c		= alocMat(n/2 + 1, n);
	
	// Initializes matrixes	
	randMat(m, n);
	countLC(l, c, m, n);
	revealsX(gab, m, n);

	clear();
	
	// Static graphics that needs to be printed just once
	printSeq(tm, l, c, n);
	printGrid(n);

	// These need to be printed at each play on the game
	printMat(tm, gab, n);
	printLife(tm, vidas, lost, n);
	printInputLine(0);

	
	int p;
	if(!flag_size || !flag_theme) while ((p = getchar()) != '\n' && p != EOF);
	// Gets the player input to be interpreted by genIntvls
	fgets(str, 12, stdin);
	
	/* 
		genIntvls take the input string and translates in x and y intervals
		also says if a play is for adding or removing
	*/
	intvlsRet = genIntvls(str, &y1, &y2, &x1, &x2, &action);
	while(intvlsRet && vidas > 0){
		if(intvlsRet == 2){
			printf("\e[F");
			printInputLine(2);
			fgets(str, 12, stdin);
			intvlsRet = genIntvls(str, &y1, &y2, &x1, &x2, &action);
			continue;
		}	
		if(x1<0 || y1<0 || x2>=n || y2>=n){
			printf("\e[F");
			printInputLine(1);
			fgets(str, 12, stdin);
			intvlsRet = genIntvls(str, &y1, &y2, &x1, &x2, &action);
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
		printInputLine(0);
		fgets(str, 12, stdin);
		intvlsRet = genIntvls(str, &y1, &y2, &x1, &x2, &action);
	}
	
	// Free of dinamic variables
	freeTheme(tm);
	freeMat(l, n);
	freeMat(c, n/2 + 1);
	freeMat(gab, n);
	freeMat(m, n);
	free(variabless);
	return 0;
}
