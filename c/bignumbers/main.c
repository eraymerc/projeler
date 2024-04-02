#include <stdlib.h>
#include "bignumbers.h"

int main(int argc, char const *argv[])
{
    struct Bignumber num1;
    initBignumber(&num1, "230102002009");
    printBignumberData(&num1);
    return 0;
}
