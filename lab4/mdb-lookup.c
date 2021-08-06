//mdb-lookup.c
//
#include <stdio.h>
#include <stdlib.h>
#include "mdb.h"
#include "mylist.h"
#include <string.h>


int main(int argc, char **argv){

        struct List mylist;
        initList(&mylist);
        struct MdbRec x;
        struct Node *node = NULL;
        const char *error = NULL;

        if (argc != 2){
                fprintf(stderr, "%s\n", "usage: ncat <file_name>");
                exit(1);

        }

        char *myfile = argv[1];
        FILE *p = fopen(myfile, "rb");
        if (p == NULL){
                perror(myfile);
                exit(1);
        }

        while (fread(&x, sizeof(x), 1, p) != 0){
                struct MdbRec *new = (struct MdbRec *)malloc(sizeof(x));
                if (new == NULL){
                        perror(error);
                        exit(1);
                }
                memcpy(new, &x, sizeof(x));
                node = addAfter(&mylist, node, new);
                if (node == NULL){
                        perror(error);
                        exit(1);
                }
        }

        if (ferror(p)){
                perror(error);
                exit(1);
        }

        //now doing lookup process
        printf("lookup: ");
        char input[1000];
        char new_input[6];
        while(fgets(input, sizeof(input), stdin) != NULL){
             strncpy(new_input, input, sizeof(new_input)-1);
                new_input[sizeof(new_input)-1] = '\0';
                if (new_input[strlen(new_input) - 1] == '\n')
                        new_input[strlen(new_input)-1] = '\0';
                //now print/find result
                struct Node *temp = mylist.head;
                int line_number = 1;
                while (temp != NULL){
                        struct MdbRec *pointer = (struct MdbRec *)temp->data;
                        char *string_message = strstr(pointer->msg, new_input);
                        char *string_name = strstr(pointer->name, new_input);
                        if (string_message || string_name)
                                printf("%d: {%s} said {%s}\n", line_number, pointer->name, pointer->msg);
                        line_number++;
                        temp = temp->next;
                }
                printf("\nlookup: ");
        }

        if (ferror(stdin)){
                perror(error);
                exit(1);
        }

        traverseList(&mylist, &free);
        removeAllNodes(&mylist);
        fclose(p);
        return 0;
}
                                                                    
