#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"
#include <time.h>

int main(){
	// Initial declarations
	srand(time(0));
	int n = 10;
	short **gab, **m, **l, **c; 
	int x1, x2, y1, y2; 
	char str[12];
	char action;

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
	scanf("%s %c", &str, &action);
	// Body of program
	while(genIntvls(str, &y1, &y2, &x1, &x2)){
		system("clear");
		for(int i = x1; i<=x2; i++)
			for(int j = y1; j<=y2; j++){
				if(action == 'r' || action == 'R'){
					if(m[i][j] == 2) printf("ACERTOUi\n");
				}
				else if(action == 'a' || action == 'A'){
					if(m[i][j] == 1) printf("ACERTOU\n");
				}
				gab[i][j] = m[i][j];
			}
		printMat(l, c, gab, n);
		printf("\n");
		scanf("%s", &str);
		printf("\n");
	}
	
	// Free of dinamic variables
	freeMat(l, n);
	freeMat(c, n/2);
	freeMat(gab, n);
	freeMat(m, n);
	return 0;
}
