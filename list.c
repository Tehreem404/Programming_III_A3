#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct Performance *newPerformance(){
    struct Performance *performance = malloc(sizeof(struct Node));
    if (performance == NULL){     /* New performance malloc check */
        printf("Error: Performance memory could not be allocated\n");
        exit(1);
    }
    performance->reads = 0;
    performance->writes = 0;
    performance->mallocs = 0;
    performance->frees = 0;

    return(performance);
}

void push(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
    struct Node *newHead = malloc(sizeof(struct Node));
    newHead->data = malloc(width);
    if (src == NULL){
        printf("Error: There is nothing to push\n");
        exit(2);
    } else if (newHead == NULL){
        printf("Error: New node memory could not be allocated\n");
        exit(3);
    }
    memcpy(newHead->data, src, width);
    
    if (*list_ptr == NULL){
        (*list_ptr) = newHead;
    } else {
        struct Node *tmpNode = *list_ptr;
        (*list_ptr) = newHead;
        newHead->next = tmpNode;
    }

    performance->mallocs++;
    performance->writes++;
}

void readHead(struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
    if (*list_ptr == NULL){
        printf("Error: List is empty\n");
        exit(4);
    }
    struct Node *tmpNode = *list_ptr;
    memcpy(dest, tmpNode->data, width);
    performance->reads++;
}

void pop(struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
    if (*list_ptr == NULL){
        printf("Error: List is empty\n");
        exit(5);
    }
    struct Node *tmpNode = *list_ptr;
    memcpy(dest, tmpNode->data, width);
    *list_ptr = tmpNode->next;

    performance->reads++;
    performance->frees++;
}

struct Node **next(struct Performance *performance, struct Node **list_ptr){
    if (*list_ptr == NULL){
        printf("Error: List is empty\n");
        exit(5);
    }
    performance->reads++;
    return(&(*list_ptr)->next);
}

int isEmpty(struct Performance *performance, struct Node **list_ptr){
    if (*list_ptr == NULL){
        return(1);
    } else {
        return(0);
    }
}

void freeList(struct Performance *performance, struct Node **list_ptr){
    void *emptyPtr = NULL;
    while(isEmpty(performance, list_ptr) != 1){
        pop(performance, list_ptr, emptyPtr, 0);
    }
}

void readItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width){
    struct Node **tmpList = list_ptr;
    int i;
    for (i = 0; i < index; i++){
        tmpList = next(performance, tmpList);
    }
    readHead(performance, tmpList, dest, width);
}

void appendItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
    struct Node **tmpList = list_ptr;
    while (isEmpty(performance, tmpList) != 1){
        tmpList = next(performance, tmpList);
    }
    push(performance, tmpList, src, width);
}

void insertItem(struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width){
    struct Node **tmpList = list_ptr;
    int i;
    for (i = 0; i < index; i++){
        tmpList = next(performance, tmpList);
    }
    push(performance, tmpList, src, width);
}

void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
    insertItem(performance, list_ptr, 0, src, width);
}

void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index){
    struct Node **tmpList = list_ptr;
    int i = 0;
    void *placholder = NULL;
    for (i = 0; i < index; i++){
        tmpList = next(performance, tmpList);
    }
    pop(performance, tmpList, placholder, 0);
}

int findItem(struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width){
    struct Node **tmpList = list_ptr;
    void *dest = malloc(width);
    int index = 0;
    while (isEmpty(performance, tmpList) != 1){
        readHead(performance, tmpList, dest, width);
        if (compar(dest, target) == 0){
            return(index);
        }
        index++;
        tmpList = next(performance, tmpList);
    }
    free(dest);
    return(0);
}