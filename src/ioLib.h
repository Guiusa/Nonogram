#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_H		"━━━━" 
#define LINE_V		"┃"
#define CORNER_TL	"┏━━"
#define CORNER_TR "━━┓"
#define CORNER_BL	"┗━━"
#define CORNER_BR "━━┛"
#define MIDDLE_L	"┣━━"
#define MIDDLE_R	"━━┫"
#define MIDDLE_T	"━━┳━━"
#define MIDDLE_B	"━━┻━━"
#define MIDDLE_C  "━━╋━━"
#define EMPTY			"    "

/*
* Stores all different types of character a chosen theme has
*/
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

void printMat(theme* t, short** m, int n);

void printSeq(theme* t, short** l, short** c, int n);

void printLife(theme* t, int life, int lost, int n);

void printEnd(theme* t, int WL, short** m, int n);

void printInputLine();

void clear();

int chooseSize(theme* t);

void error(theme* t, char* err, char* usg);

void printGrid(int n);
