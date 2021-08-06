#include <stdio.h>
#include <stdint.h>
#include "convert.h"

int convert(int x){
	//fourteen spaces
	printf("signed dec:   %d\n", x);
	printf("unsigned dec: %u\n", x);
	printf("hex:  \t      %x\n", x);	
	int counter = 0;
	printf("binary:\t      ");
	int i;
	for (i = 31; 0 <= i; i--)
	{ 
		if ((counter % 4) == 0 && counter != 0)
			printf(" ");
		if (x & (1 << i))
	       		printf("1");
		else
			printf("0");
		counter++;
	}
	printf("\n");
	return 0;
		
}
