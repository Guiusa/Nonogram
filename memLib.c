#include "memLib.h" 
#include <stdio.h>

short** alocMat (int l, int c){
	short** m = (short**) malloc(l * sizeof(short*));
	for(int i = 0; i<l; i++){
		m[i] = (short*) malloc(c * sizeof(short));
		for(int j = 0; j<c; j++)
			m[i][j] = 0;
	}
	
	return m;
}
void freeMat (short** m, int l){
	for(int i = 0; i<l; i++)
		free(m[i]);
	free(m);
}
