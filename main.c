#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"
#include <time.h>

int main(){
	// Initial declarations
	srand(time(0));
	int n = 5;
	short **gab, **m, **l, **c; 
	int x1, x2, y1, y2; 
	char str[12];
	char action;
	int vidas = 3;
	int lost;

	// alocs t odinamic variables
 	m 	= alocMat(n, n);
	gab	= alocMat(n, n);
	l		= alocMat(n, n/2);
	c		= alocMat(n/2, n);

	// Initializes matrixes	
	randMat(m, n);
	countLC(l, c, m, n);
	x1 = 0; x2 = 0; y1 = 0; y2 = 0;

	printMat(l, c, gab, n);
	printf("\n");
	fgets(str, 12, stdin);

	// Body of program
	while(genIntvls(str, &y1, &y2, &x1, &x2, &action) && vidas > 0){
		system("clear");
		lost = validatesPlay(x1, x2, y1, y2, action, &vidas, gab, m, n);
		printMat(l, c, gab, n);
		printLife(vidas, lost);
		if(vidas<=0) break;
		printf("\n");
		fgets(str, 12, stdin);
		if(!strcmp(str, "stop")) break;
		printf("\n");
		if(checkWin) break;
	}
	
	// Free of dinamic variables
	freeMat(l, n);
	freeMat(c, n/2);
	freeMat(gab, n);
	freeMat(m, n);
	return 0;
}
