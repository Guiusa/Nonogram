#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"
#include "fileLib.h"

int main(){
	int* n;
	int* tc;
	char *variabless = (char*) malloc(100 * sizeof(char));
	cleanComments(variabless);
	printf("%s", variabless);
	getVariables(tc, n, variabless);		
	return 0;
}
