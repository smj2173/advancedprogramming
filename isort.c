#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int compare(const void *a,  const void *b){
        int x = *(const int *)a;
        int y = *(const int *)b;
        return x-y;
}

int compare2(const void *a, const void *b){
        int x = *(const int*)a;
        int y = *(const int *)b;
        return y-x;
}

void sort_integer_array(int *a, int *b, int ascending){
        int size = (b-a)+1;
        if (ascending == 1)
                qsort(a, size, sizeof(int),&compare);
        if (ascending == 0)
                qsort(a, size, sizeof(int),&compare2);
}


int main(){
        int x;
        srandom(time(NULL));
        scanf("%d", &x);
        int *a = (int *)malloc(x* sizeof(int));
        if (a == NULL){
                perror("malloc returned NULL");
                exit(1);
        }

        printf("original: ");
        //assignment and original
        for (int i=0; i<x; i++){
                a[i] = random() % 100;
                printf("%d ", a[i]);
        }
        printf("\n");
        int *ascend = (int*)malloc(x*sizeof(int));
        if (ascend == NULL){
                perror("malloc returned NULL");
                exit(1);
        }


        int *descending = (int*)malloc(x*sizeof(int));
        if (descending == NULL){
                perror("malloc returned NULL");
                exit(1);
        }

        for (int i=0; i<x; i++){
                ascend[i] = a[i];
                descending[i] = a[i];
        }

        int *b = (int*)(ascend+x-1);
        int *c = (int*)(descending+x-1);

        sort_integer_array(ascend,b, 1); //ascending
        printf("ascending: ");
        for (int i=0; i<x; i++){
                printf("%d ", ascend[i]);
        }
        printf("\n");

        sort_integer_array(descending,c, 0); //descending
        printf("descending: ");
        //descending
        for (int i=0; i<x; i++){
                printf("%d ", descending[i]);
        }
        printf("\n");
        free(a);
        free(ascend);
        free(descending);
        return 0;
  }
                                                                                                                                                            81,1-8        91%
