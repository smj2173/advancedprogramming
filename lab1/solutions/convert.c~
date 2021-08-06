#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);

    printf("signed dec:   %d\n", x);
    printf("unsigned dec: %u\n", x);
    printf("hex:          %x\n", x);
    printf("binary:       ");
    int i;
    for (i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
        if (i % 4 == 0)
            printf(" ");
    }
    printf("\n");
    return 0;
}
