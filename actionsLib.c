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
int genIntvls (char* entry, int *x1, int *x2, int *y1, int *y2, char* a){
	char tmp[12];
	int x1a, x2a, y1a, y2a;
	if(strchr(entry, ' ') != NULL){
		sscanf(entry, "%[^ ]%s", &tmp, a);
	} else { 
		strcpy(tmp, entry); 
		*a = 'a';
	}
	char xstr[6], ystr[6];
	if(strchr(entry, ',') == NULL){
		printf("Parando programa\n");
		return 0;
	}
	sscanf(entry, "%[^,],%s", &xstr, &ystr);
	
	if(strchr(xstr, '-') != NULL){
		sscanf(xstr, "%d-%d", &x1a, &x2a);
	} else {
		sscanf(xstr, "%d", &x1a);
		sscanf(xstr, "%d", &x2a);
	}

	if(strchr(ystr, '-') != NULL){
		sscanf(ystr, "%d-%d", &y1a, &y2a);
	} else {
		sscanf(ystr, "%d", &y1a);
		sscanf(ystr, "%d", &y2a);
	}
	if(x1a < 0 || x2a < 0 || y1a < 0 || y2a < 0){
		printf("x1: %d x2: %d\ny1: %d y2: %d\n", x1a, x2a, y1a, y2a);
		return 0;
	}
	*x1 = x1a-1;
	*x2 = x2a-1;
	*y1 = y1a-1;
	*y2 = y2a-1;
	return 1;
}

void revealsLC (short** m, short** gab, int n, int i, int j){
	int rl = 1;
	int rc = 1;
	for(int ia = 0; ia<n; ia++)
		if(gab[ia][j] == 1 && m[ia][j] != 1) rc = 0;
	for(int ja = 0; ja<n; ja++)
		if(gab[i][ja] == 1 && m[i][ja] != 1) rl = 0;

	if(rc)
		for(int ia = 0; ia<n; ia++)
			m[ia][j] = gab[ia][j];
	if(rl)
		for(int ja = 0; ja<n; ja++)
			m[i][ja] = gab[i][ja];
}
