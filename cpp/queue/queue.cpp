#include "queue.h"
#include "stdio.h"
#include "stdlib.h"

QUEUE *createQueue(void)
{
    QUEUE *queue;
    queue = (QUEUE *)malloc(sizeof(QUEUE));
    if (queue)
    {
        queue->front = NULL;
        queue->rear = NULL;
        queue->count =0;
    }
    return queue;
}

bool enqueue(QUEUE *que, void *item){
    QUEUE_NODE *newPtr;
    if(!(newPtr=(QUEUE_NODE *) malloc(sizeof(QUEUE_NODE)))){
        return false;
    }
    newPtr->dataPtr=item;
    newPtr->next=NULL;
    if(queue->count == 0){

    }
};