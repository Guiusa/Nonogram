#include "actionsLib.h"
/*
* Randomizes drawings in the matrix
* I think this is an interesting algorithm to study and make it better
*/
int randMat (short** m, int n){
	int count = 0;
	// randomizes unique cells
	for(int i = 0; i<n; i++)
		for(int j = 0; j<n; j++){
			m[i][j] = (rand()%100 > 45) ? 1 : 2;
		}

	// randomizes sequences of n cells
	int c = rand()%(n/4) + 1;
	for(int ip = 0; ip<c; ip++){
		int lc = rand()%2;
		if(lc){
			int j = rand()%n;
			for(int i = 0; i<n; i++)
				m[i][j] = 1;
		}
		else {
			int i = rand()%n;
			for(int j = 0; j<n; j++)
				m[i][j] = 1;
		}
	}
	
	// randomizes sequences of n/2 cells
	for(int ip = 0; ip<c; ip++){
		int lc = rand()%2;
		int init = rand()%(n/2);
		if(lc){
			int j = rand()%n;
			for(int i = 0; i<n/2; i++)
				m[i+init][j] = 1;
		}
		else {
			int i = rand()%n;
			for(int j = 0; j<n/2; j++)
				m[i][j+init] = 1;
		}
	}

}


/*
* Counts amount of consecutive squares on lines and columns and stores this info
* in l and c structures
*/
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

/*
* Interpretes player's input to stores x and y intervales on variables
* Also informs if is a add or removal action on "a" variable
*/
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
		if(!strcmp(entry, "stop\n")) return 0;	
		return 2;
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

/*
*	If all alive cells in a line or column were already found, reveals 
* automatically all dead cells in that line/column
*/
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

/*
* Takes player's input and discounts errors, also updates matrix to show already
* found cells
*/
int validatesPlay (int x1, int x2, int y1, int y2, char action, int* vidas, short** gab, short** m, int n){
	int errors = 0;
	for(int i = x1; i<=x2; i++)
		for(int j = y1; j<=y2; j++){
			if((action == 'r' || action == 'R') && m[i][j] != 2){
				*vidas = *vidas-1;
				errors++;
			} else if ((action == 'a' || action == 'A') && m[i][j] != 1){
				*vidas = *vidas-1;
				errors++;
			}
			gab[i][j] = m[i][j];
			revealsLC(gab,m,n,i,j);
		}
		return errors;
}

/*
*	Checks if player reach the end by winning
*/
int checkWin(short** gab, int n){
	for(int i = 0; i<n; i++)
		for(int j = 0; j<n; j++)
			if(!gab[i][j])
				return 0;
	return 1;
}

/*
* Reveals some dead cells in the begining so the game is easier
*/
int revealsX(short** gab, short** m, int n){
	int count = 0;
	for(int i = 0; i<n; i++)
		for(int j = 0; j<n; j++)
			if(m[i][j] == 2 && rand()%100 > 65)
				gab[i][j] = 2;
}
