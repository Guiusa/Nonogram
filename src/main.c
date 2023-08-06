#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"
#include <time.h>

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
	
	// alocs t odinamic variables
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
	x1 = 0; x2 = 0; y1 = 0; y2 = 0;

	clear();
	getchar();
	printSeq(tm, l, c, n);
	printGrid(n);
	printMat(tm, gab, n);
	printLife(tm, vidas, lost, n);
	printInputLine();
	fgets(str, 12, stdin);
	
	//Body of program
	while(genIntvls(str, &y1, &y2, &x1, &x2, &action) && vidas > 0){
		if(x1<0 || y1<0 || x2>=n || y2>=n){
			printf("Bad interval given\n");
			fgets(str, 12, stdin);
			continue;
		}
		//clear();
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
