#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char* HIDN;
	char* FOUND;
	char* XX;
	char* LTTRS;
	char* NRML;
} theme;

theme* alocTheme();
void freeTheme(theme* t);
void chooseTheme(theme* t);
void printMat(theme* t, short**l, short** c, short** m, int n);
void printLife(theme* t, int life, int lost);
void printEnd(theme* t, int WL, short** m, int n);
void clear();
int chooseSize(theme* t);
