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

bool enqueue(QUEUE *queue, void *item){
    QUEUE_NODE *newPtr;
    if(!(newPtr=(QUEUE_NODE *) malloc(sizeof(QUEUE_NODE)))){
        return false;
    }
    newPtr->dataPtr=item;
    newPtr->next=NULL;
    if(queue->count == 0)
        queue->front = newPtr;
    else
        queue->rear->next=newPtr;
    (queue->count)++;
    return true;
    
};
bool dequeue (QUEUE *queue, void **item){
    QUEUE_NODE* delLoc;
    if(!(queue->count))
        return false;
    *item = queue->front;
    delLoc = queue-> front;
    if(queue->count == 1){
        queue->front = NULL;
        queue->rear = NULL;
    }
    else
        queue->front=queue->front->next;
    (queue->count)--;
    free(delLoc);
    return true;
}   