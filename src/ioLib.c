#include "ioLib.h"

/*
HIDN 	"\e[0;90m";
FOUND "\e[0;36m";
XX		"\e[0;107m\e[1;35m";
LTTRS "\e[1;100m";
NRML 	"\e[0m";
*/

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

void chooseTheme(theme* t){
	printf("CHOOSE A THEME:\n\n");
	printf("(1)\tHatsune Miku\t\t\t");
	printf("\e[0;90m██ \e[0;36m██ \e[0;107m\e[1;35mXX\e[0m\n"); 
	printf("(2)\tEverywhere is now Brazil\t");
	printf("\e[0;33m██ \e[0;34m██ \e[0;107m\e[1;32mXX\e[0m\n"); 
	printf("(3)\tOMG Miles Morales???\t\t");
	printf("\e[0;30m██ \e[0;31m██ \e[0;40m\e[1;34mXX\e[0m\n"); 
	printf("(4)\tBlack & White\t\t\t");
	printf("\e[0;30m██ \e[0;97m██ \e[0;40m\e[1;97mXX\e[0m\n"); 
	int k;
	scanf("%d", &k);
	while(k<1 || k>4){
		printf("Wrong choice :(\n");
		scanf("%d", &k);
	}
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

void printMat(theme* t, short** l, short** c, short** m, int n){
	/*
	# This loop iters over columns array (c) to print sections found
	# in each column
	*/
	for(int i = 0; i<n/2; i++){
		for(int i = 0; i<n/2; i++) printf("   ");
		printf("\t");
		for(int j = 0; j<n; j++)
			if(c[i][j]){ 
				printf("%s%3d %s", t->LTTRS, c[i][j], t->NRML);
			} else printf("%s    %s", t->LTTRS, t->NRML);
		printf("\n");
	}
	printf("\n");
	/*
	# For each line, prints the sections found in (l) and then prints the
	# squares
	*/
	for(int i = 0; i<n; ++i){
		for(int jp = 0; jp < n/2; jp++)
			if(l[i][jp]){ 
				printf("%s%3d%s", t->LTTRS, l[i][jp], t->NRML);
			} else printf("%s   %s", t->LTTRS, t->NRML);
		printf("\t");
		for(int j = 0; j<n; ++j){
			if(!m[i][j]){
				printf("%s████%s", t->HIDN, t->NRML);
			} else if (m[i][j] == 1){
				printf("%s████%s", t->FOUND, t->NRML);
			} else
				printf("%sXXXX%s", t->XX, t->NRML);
		}
		printf(" %2d\n", i+1);
		for(int ip = 0; ip<n/2; ip++) printf("%s   %s", t->LTTRS, t->NRML);
		printf("\t");
		for(int j = 0; j<n; j++){
			if(!m[i][j]){
				printf("%s████%s", t->HIDN, t->NRML);
			} else if (m[i][j] == 1){
				printf("%s████%s", t->FOUND, t->NRML);
			} else
				printf("%sXXXX%s", t->XX, t->NRML);	
		}
		printf("\n");
	}
	for(int i = 0; i<n/2; i++) printf("   ");
	printf("\t");
	for(int i = 0; i<n; ++i)
		printf("%3d ", i+1);
	printf("\n\n");
}

void printLife(theme* t, int life, int lost){
	if(lost==1)
		printf("%sYOU LOST %d LIFE IN THE LAST PLAY%s\n", t->XX, lost, t->NRML);
	if(lost>1)
		printf("%sYOU LOST %d LIFES IN THE LAST PLAY%s\n", t->XX, lost, t->NRML);
	printf("%sLIFES LEFT: %d%s\n", t->XX, life, t->NRML);
}

void printEnd(theme* t, int WL, short** m, int n){
	printf("\n");
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
		printf("%s\nYOU WON!!%s\n", t->XX, t->NRML);
	} else
		printf("%s\nYOU LOST ALL YOUR LIFES!!%s\n", t->XX, t->NRML);
}

void clear(){
	printf("\e[2J\e[H");
}

int chooseSize(theme* t){
	int k;
	printf("%sCHOOSE THE GRID SIZE:\n(1) - 5\n(2) - 10\n(3) - 15%s\n", t->XX, t->NRML);
	scanf("%d", &k);
	while(k<1 || k>3){
		printf("%sWRONG CHOICE :(%s\n", t->XX, t->NRML);
		scanf("%d", &k);
	}
	return k*5;
}
