#include <stdlib.h>
#include "bignumbers.h"

int main(int argc, char const *argv[])
{
    struct Bignumber num1,num2;
    //initBignumber(&num1, "230102002009");
    initBignumberFromInt(&num1, 13435);
    initBignumberFromInt(&num2, 13435);
    printBignumberData(&num1);
    subNumber(&num1,&num2);
    printBignumberData(&num1);
    printBignumberData(&num2);

    return 0;
}
