//Reggie Barnett
//Project 3
//Main File

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "mymalloc.h"
 
NODE *first = NULL;
NODE *last = NULL;
NODE *new = NULL;
NODE *curr = NULL;
int nodesize = sizeof(NODE);
 
void *my_nextfit_malloc(int size){   
    int size_addr = size + nodesize;
    NODE * begin_addr = (NODE*) sbrk(0);
    //Checking if anything is in the linked list
    if (first == NULL) {
        sbrk(size_addr);
        first = begin_addr;
        first->size = size;
        first->used = 1;
        first->previous = NULL;
        first->next = NULL;
        last = first;
        curr = first;
        return ((void*)begin_addr + nodesize); 
    }
    //Searching through list looking for free block that is big enough big enough
    while (curr != NULL) {
        if ((curr->used == 0) && curr->size >= size) {
            curr->used = 1;
            new = curr + size_addr;
            new->used = 0;
            new->size = ((curr->size) - size_addr);
            curr->size = size;
            new->next = curr->next;
            new->previous = curr;
            curr->next->previous = new;
            curr->next = new;
            return ((void*)curr + nodesize);
        }
        else {
            curr->used = 1;
            return ((void*)curr + nodesize);
        }
        curr = curr->next;
    }
    //Adding to the end
    sbrk(size_addr);
    new = begin_addr;
    new->size = size;
    new->used = 1;
    new->previous = last;
    new->next = NULL;
    last->next = new;
    last = new;
    return ((void*)last + nodesize);
}

void my_free(void *ptr){ 
    NODE *begin_addr = ptr - nodesize;
    if (begin_addr == first) {
        curr = first->next;
        if (curr->used == 0) {
            first->size = ((first->size) + nodesize + (curr->size));
            first->next = curr->next;
            first->used = 0;
            return;
        }
        first->used = 0;
        return;
    }
    if (begin_addr == last) {
        if (last == first) {
            sbrk(-(first->size + nodesize));
            first = NULL;
            last = NULL;
            return;
        }
        if (last->previous->used == 0) {
            curr = last->previous;
            curr->size = ((curr->size) + nodesize + (last->size));
            last = curr->previous;
            last->next = NULL;
            sbrk(-((curr->size) + nodesize));
            return;
        }
        last = last->previous;
        sbrk(-((last->next->size) + nodesize));
        last->next = NULL;
        return;
    }
    curr = begin_addr;
    curr->used = 0;
    if (curr->next->used == 0) {
        curr->size = (curr->size + nodesize + (curr->next->size));
        curr->next = curr->next->next;
        curr->next->previous = curr;
    }
    if (curr->previous->used == 0) {
        curr = curr->previous;
        curr->size = (curr->size + nodesize + (curr->next->size));
        curr->next = curr->next->next;
        curr->next->previous = curr;
    }  
}