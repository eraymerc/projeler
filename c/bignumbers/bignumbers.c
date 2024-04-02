#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "bignumbers.h"

void initBignumber(struct Bignumber *num, const char *str){
    size_t length = strlen(str);
    size_t BignumberSize = (size_t) ceil(BIGNUMBER_RATIO*length);

    num->size = BignumberSize + 1; //1 byte gap
    num->next = NULL;

    struct BignumberTail *current = num->next;

    for (size_t i = 0; i < BignumberSize+1; i++)
    {
        struct BignumberTail *new = (struct BignumberTail *)malloc(sizeof(struct BignumberTail));
        if (new == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        new->next = NULL;
        new->data = 0;

        if (current == NULL) {

            num->next = new;
            current = new; 
        } else {
            current->next = new;
            current = new; 
        }
    }
}

void printBignumberData(struct Bignumber *num){
    struct BignumberTail *current = num->next;
    for (size_t i = 0; i < num->size; i++)
    {
        printf("[%u]",current->data);
        current = current->next;
    }
    
}