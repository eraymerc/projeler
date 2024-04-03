#include <stdio.h>
#include <stdlib.h>

#include "bignumbers.h"

int main(int argc, char const *argv[]) {
    struct Bignumber num1, num2, num3;
    // initBignumber(&num1, "230102002009");
    initBignumberFromInt(&num1, 1984);  // add negative number support, sifir
                                        // oldugunda kiyaslama hata veriyor, coz
    initBignumberFromInt(&num2, 63488);
    initBignumberFromInt(&num3, 10);
    complement(&num1);
    //complement(&num2);
    printf("63488 : ");
    printBignumberData(&num2);
    printf("-63488 : ");
    complement(&num2);
    printBignumberData(&num2);
    // addNumber(&num1, &num2);

    // complement(&num1);
    // complement(&num2);
    //subNumber(&num1, &num2);
    for (size_t i = 0; i < 20; i++)
    {
        printf("%zu : \n", i);
        printBignumberData(&num1);
        complement(&num1);
        printBignumberData(&num1);
        complement(&num1);
        addNumber(&num1, &num1);
    }/*
    for (size_t i = 0; i < 20; i++)
    {
        printf("%zu : ", i);
        printBignumberData(&num1);
        addNumber(&num1, &num1);
        
    }*/
    
    printf("num1 : \n");

    printBignumberData(&num1);
    printf("num2 : \n");
    printBignumberData(&num2);
    char result = compareNumbers(&num1, &num2);
    printf("result : %d", (int)result);
    return 0;
}
