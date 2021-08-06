#include <stdio.h>
#include "gcd.h"
#include "prime.h"

int main()
{
	int x, y;
	scanf("%d", &x);
	scanf("%d", &y);

	printf("You typed in %d and %d\n", x, y);

	float average = (float)(x+y)/2;
 	
	printf("The average is: %f\n", average);

	int z = gcd(x, y);

	if (z == 1)
	{
		printf("%d and %d are relatively prime\n", x, y);
	}
	else
	{
		printf("%d and %d are not relatively prime\n", x, y);
	}

	prime(x);
	prime(y);

	return 0;

}
