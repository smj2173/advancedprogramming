#include <stdio.h>
#include <string.h>
#include "mylist.h"

int main(int argc, char** argv){

        struct List mylist;
        initList(&mylist); //initialize list
        int hasdude = 1;
        argv++;
        //to see if dude is in it and addFront()
        while (*argv != 0){
                addFront(&mylist, *argv);
                if (hasdude != 0){ //dude not found
                        hasdude = strcmp("dude", *argv); //will return zero if equivalent
                }
                argv++;
        }

        void function(void *string){
                printf("%s\n", (char *)string);
        }

        traverseList(&mylist, &function);
        printf("\n");
        if (hasdude == 0){ //true
                printf("dude found\n");
        }
        else{
                printf("dude not found\n");
        }

        removeAllNodes(&mylist);
        return 0;
}
~                                                                         
