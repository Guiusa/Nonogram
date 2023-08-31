#include "fileLib.h"

void cleanComments(char* variabless){
	FILE* fp;
	char string[100];
	int vp = 0;
	fp = fopen(CFG, "r");
	while(fgets(string, 100, fp)){
		for(int i = 0; string[i] != '\0'; i++){
			if(string[i] == '#'){
				if(i > 0){
					variabless[vp] = '\n';
					vp++;
				}
				break;
			}
			variabless[vp] = string[i];
			vp++;
		}
	}
	fclose(fp);
	variabless[vp] = '\0';
}

void	getVariables(int* tc, int* n, char* variabless){
	char aux[80];	
}
