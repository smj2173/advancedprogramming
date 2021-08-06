#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"

struct Node *addFront(struct List *list, void *data){
        struct Node *node = malloc(sizeof(struct Node));
        if (!node){
                return NULL;
        }
        node->data = data;
        node->next = list->head;
        list->head = node;
        return node;

}

void traverseList(struct List *list, void (*f)(void *)){
        struct Node *temp = list->head;

        while (temp){
                f(temp-> data);
                temp = temp->next;
        }


}

void flipSignDouble(void *data){
        double *new_data = (double *)data;
        *new_data = (*new_data) * -1;
}


int compareDouble(const void *data1, const void *data2){
        if((*(double *)data1 - *(double *)data2) == 0)
                return 0;
        else
                return 1;
}

struct Node *findNode(struct List *list, const void *dataSought, int (*compar)(const void *, const void *)){
        struct Node *temp = list->head;

        while (temp){
                if (compar(dataSought, temp->data) == 0)
                        return temp;
                temp = temp->next;
        }
        return NULL; //if no match found !!


}

void *popFront(struct List *list){
        struct Node *temp = list->head;
        if (isEmptyList(list) != 0)
                return NULL;
        else{ //temp is not empty 
                list->head  = temp->next;
                void * deallocate = temp->data;
                free(temp);
                return deallocate;
        }
}


void removeAllNodes(struct List *list){
        while (!isEmptyList(list)){
                popFront(list);
        }
}


struct Node *addAfter(struct List *list, struct Node *prevNode, void *data){
        struct Node *temp = list->head;

        if (prevNode == NULL){
                temp = addFront(list, data);
        }
        else{
                temp = malloc(sizeof(struct Node));
                temp->data = data;
                temp->next = prevNode->next;
                prevNode->next = temp;
        }
        return temp;
}



void reverseList(struct List *list){
        struct Node *prv = NULL;
        struct Node *cur = list->head;
        struct Node *nxt;

        while (cur){
                nxt = cur->next;
                cur->next = prv;
                prv = cur;
                cur = nxt;
        }
        list->head = prv;
}
                                              
