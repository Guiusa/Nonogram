#include "actionsLib.h"
#include <stdio.h>
// Randomizes drawings in the matrix
int randMat (short** m, int n){
	int bounds[2] = {30, 90};
	int count = 0;
	int prob;
	for(int i = 0; i<n; i++)
		for(int j = 0; j<n; j++){
			int summ = 0;
			if((i>0) && (j>0 && j<n-1)){
				for(int iaux = -1; iaux<=1; ++iaux)
					summ += m[i-1][j+iaux];
				summ += m[i][j-1];
			}
			prob = (summ) ? bounds[0] : bounds[1];
			m[i][j] = (rand()%100 > prob) ? 1 : 2;
		}
}

// Counts amount of consecutive squares on line and column
int countLC (short** l, short** c, short** m, int n){
	int count = 0;
	for(int i = 0; i<n; i++){
		int icAux = 0;
		for(int jp = 0; jp<n; jp++){
			if(m[i][jp] == 1){
				count++;
				jp++;
				while(jp < n && m[i][jp] == 1) {
					count++;
					jp++;
				}
				l[i][icAux] = count;
				icAux++;
				count = 0;	
			}
		}
	}
	
	count = 0;
	for(int j = 0; j<n; j++){
		int jcAux = 0;
		for(int ip = 0; ip<n; ip++){
			if(m[ip][j] == 1){
				count++;
				ip++;
				while(ip < n && m[ip][j] == 1){
					count++;
					ip++;
				}
				c[jcAux][j] = count;
				jcAux++;
				count = 0;
			}
		}
	}
}

// Generates x and y intervals given the program entry
int genIntvls (char* entry, int *x1, int *x2, int *y1, int *y2){
	char xstr[6], ystr[6];
	if(strchr(entry, ',') == NULL) return 0;
	sscanf(entry, "%[^,],%s", &xstr, &ystr);
	
	if(strchr(xstr, '-') != NULL){
		sscanf(xstr, "%d-%d", x1, x2);
	} else {
		sscanf(xstr, "%d", x1);
		sscanf(xstr, "%d", x2);
	}

	if(strchr(ystr, '-') != NULL){
		sscanf(ystr, "%d-%d", y1, y2);
	} else {
		sscanf(ystr, "%d", y1);
		sscanf(ystr, "%d", y2);
	}
	
	if(*x1 < 0 || *x2 < 0 || *y1 < 0 || *y2 < 0)
		return 0;
	return 1;
}
