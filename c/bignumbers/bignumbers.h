#include <stdlib.h>

#ifndef BIGNUMBERS_H
#define BIGNUMBERS_H
#define BIGNUMBER_RATIO (0.415) //log2(10)/log2(256)

struct BignumberTail
{
    unsigned char data;
    struct BignumberTail *next;
};


struct Bignumber
{
    size_t size;
    struct BignumberTail *next;
};

void initBignumber(struct Bignumber *, const char *);
void printBignumberData(struct Bignumber *);

#endif