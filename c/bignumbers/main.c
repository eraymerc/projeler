#include <stdlib.h>
#include "bignumbers.h"

int main(int argc, char const *argv[])
{
    struct Bignumber num1,num2;
    //initBignumber(&num1, "230102002009");
    initBignumberFromInt(&num1, 13435);
    initBignumberFromInt(&num2, 60000);
    printBignumberData(&num1);
    addNumber(&num1,&num2);
    printBignumberData(&num1);
    printBignumberData(&num2);

    return 0;
}
