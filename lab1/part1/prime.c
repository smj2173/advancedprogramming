#include "prime.h"
#include <stdio.h>

int prime(int x)
{
	int i;
	int isprime = 0;
	if (x <= 1)
	{
		printf("%d is not prime\n", x);
	}
	else{
		for (i=2; i < x; ++i)
		{
			if ((x % i) == 0){
				isprime = 1;
			}
		}
	}		
	if (isprime == 1)
		printf("%d is not prime\n", x);
	else
		printf("%d is prime\n", x); 

	return 0;
}
