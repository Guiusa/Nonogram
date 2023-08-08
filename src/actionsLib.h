#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int randMat (short** m, int n);
int countLC (short** l, short** c, short** m, int n);
int genIntvls (char* entry, int *x1, int *x2, int *y1, int *y2, char* a);
int validatesPlay (int x1, int x2, int y1, int y2, char action, int* vidas, short** gab, short** m, int n);
int checkWin(short** gab, int n);
int revealsX(short** gab, short** m, int n);
