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

void	getVariables(int* tc, int* n){
	char *variabless = (char*) malloc(100 * sizeof(char));
	cleanComments(variabless);
	char* tk = strtok(variabless, "\n");
	while(tk != NULL){
		char key[30];
		int value;

		if(sscanf(tk, "%s %d", key, &value) == 2){
			if(! strcmp(key, "THEME")) *tc = value;
			if(! strcmp(key, "SIZE")) *n = value;
		}	
		tk = strtok(NULL, "\n"); 
	}
}


