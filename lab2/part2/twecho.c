/*
 * twecho
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char **duplicateArgs(int argc, char **argv)
{
        char **arr = argv;

        char** p = (char **)malloc(sizeof(char*) * (argc+1));
        if (p == NULL){
                perror("malloc returned NULL");
                exit(1);
        }
        p[argc] = '\0';
        for (int i=0; i<argc; i++){
                p[i]= (char *)malloc(strlen(arr[i])+1);
                if (p[i] == NULL){
                        perror("malloc returned NULL");
                        exit(1);
                }
                int j=0;
                while(arr[i][j]!= '\0'){
                        p[i][j]=toupper(arr[i][j]);
                        j++;
                        }
                p[i][j] = '\0';
                }
        return p;
}

static void freeDuplicatedArgs(char **copy)
{
        char **t = copy;
        int i=0;

        while (*(t+i) != NULL){
                free(*(t+i));
                i++;
        }
        free(copy);
}

/*
 * DO NOT MODIFY main().
 */
int main(int argc, char **argv)
{
    if (argc <= 1)
        return 1;

    char **copy = duplicateArgs(argc, argv);
    char **p = copy;

    argv++;
    p++;
    while (*argv) {
        printf("%s %s\n", *argv++, *p++);
    }

    freeDuplicatedArgs(copy);

    return 0;
}
                                                                                                                                                            68,1          Bot
