#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"
#include "fileLib.h"

int main(){
	int n = 0;
	int tc = 0;
	char *variabless = (char*) malloc(100 * sizeof(char));
	cleanComments(variabless);
	getVariables(&tc, &n, variabless);		
	printf("tc: %d\nn:  %d\n", tc, n);
	return 0;
}
