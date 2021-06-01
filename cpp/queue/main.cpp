#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    char str[100], *u = (char *)malloc(sizeof(char));
    int i;

    QUEUE *sPr;
    sPr = createQueue();
    std::cout << "Bir cumle lutfen" << std::endl;
    gets(str);
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
        {
            enqueue(sPr, &str[i]);
        }
    }
    std::cout << "elemanlar yerlesti" << std::endl;
    while(sPr->count != 0){
        dequeue(sPr,(void **)&u);
        std::cout<< *u <<std::endl;
        u=(char*)malloc(sizeof(char));
    }

    return 0;
}
