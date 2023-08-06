#include "memLib.h"
#include "ioLib.h"
#include "actionsLib.h"

int main(){
	printf("\e[2J\e[H");
	print5Grid();
	
	/*print10Grid();
	print15Grid();
	*/	
	for(int i = 0; i<10; i++)
		for(int j = 0; j<5; j++)
			printf("\e[%d;%dH████", i+2, j*4+2);
		
	printf("\e[13;0H");
	return 0;
}
