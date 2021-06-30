#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	
	int i;
	
	srand(time(0));
	
	do{
		i = rand()%15;
		printf("%d ", i);
	}while (i != 9);
	
return(0);
 }