#include <stdlib.h>

#include "bignumbers.h"

int main(int argc, char const *argv[]) {
    struct Bignumber num1, num2;
    // initBignumber(&num1, "230102002009");
    initBignumberFromInt(&num1, 360);
    initBignumberFromInt(&num2, 360);
    printBignumberData(&num1);
    struct Bignumber *copy1 = copyNumber(&num1);
    //for (size_t i = 0; i < 6; i++) {
    //    addNumber(&num1, &num1);
    //}


    printBignumberData(copy1);
    printBignumberData(&num1);

    return 0;
}
