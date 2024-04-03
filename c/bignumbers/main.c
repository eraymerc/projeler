#include <stdio.h>
#include <stdlib.h>

#include "bignumbers.h"

int main(int argc, char const *argv[]) {
    struct Bignumber num1, num2;
    // initBignumber(&num1, "230102002009");
    initBignumberFromInt(&num1, 0);//add negative number support, sifir oldugunda kiyaslama hata veriyor, coz
    initBignumberFromInt(&num2, 0);
    //printBignumberData(&num1);
    //addNumber(&num1, &num2);

    //complement(&num1);
    //complement(&num2);
    printf("num1 : \n");
    printBignumberData(&num1);
    printf("num2 : \n");
    printBignumberData(&num2);
    char result = compareNumbers(&num1, &num2);
    printf("result : %d", (int)result);
    return 0;
}
