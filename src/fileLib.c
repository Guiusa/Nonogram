#include "fileLib.h"

void printFile(){
	int i;
	FILE* fp;
	char string[100];
	fp = fopen(CFG, "r");
	while(fgets(string, 100, fp)){
		i = 0;
		while(string[i] != '\0'){
			if(string[i] == '#'){
				if(i > 0) printf("\n");
				break;
			}
			printf("%c", string[i]);
			i++;
		}
	}
	fclose(fp);
}
