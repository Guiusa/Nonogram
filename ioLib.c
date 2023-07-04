#include "ioLib.h"
#define HIDN 	"\e[0;90m"
#define FOUND "\e[0;36m"
#define XX		"\e[0;107m\e[1;35m"
#define LTTRS	"\e[1;100m"
#define NRML	"\e[0m"
#define GRID	"\e[1;35m"

void printMat(short** l, short** c, short** m, int n){
	/*
	# This loop iters over columns array (c) to print sections found
	# in each column
	*/
	for(int i = 0; i<n/2; i++){
		for(int i = 0; i<n/2; i++) printf("   ");
		printf("\t");
		for(int j = 0; j<n; j++)
			if(c[i][j]){ 
				printf("%s%4d%s", LTTRS, c[i][j], NRML);
			} else printf("%s    %s", LTTRS, NRML);
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
				printf("%s%3d%s", LTTRS, l[i][jp], NRML);
			} else printf("%s   %s", LTTRS, NRML);
		printf("\t");
		for(int j = 0; j<n; ++j){
			if(!m[i][j]){
				printf("%s████%s", HIDN, NRML);
			} else if (m[i][j] == 1){
				printf("%s████%s", FOUND, NRML);
			} else
				printf("%sXXXX%s", XX, NRML);
		}
		printf(" %2d\n", i);
		for(int ip = 0; ip<n/2; ip++) printf("%s   %s", LTTRS, NRML);
		printf("\t");
		for(int j = 0; j<n; j++){
			if(!m[i][j]){
				printf("%s████%s", HIDN, NRML);
			} else if (m[i][j] == 1){
				printf("%s████%s", FOUND, NRML);
			} else
				printf("%sXXXX%s", XX, NRML);	
		}
		printf("\n");
	}
	for(int i = 0; i<n/2; i++) printf("   ");
	printf("\t");
	for(int i = 0; i<n; ++i)
		printf("%4d", i);
	printf("\n\n");
}
