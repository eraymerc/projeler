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

void initBignumberFromStr(struct Bignumber *, const char *);
void initBignumberFromInt(struct Bignumber *, int);
void printBignumberData(struct Bignumber *);
void addNumber(struct Bignumber *,struct Bignumber *);
void subNumber(struct Bignumber *, struct Bignumber *);
void multiplyNumber(struct Bignumber *, struct Bignumber *);
struct Bignumber *copyNumber(struct Bignumber *);

#endif