#ifndef QU
#define QU

typedef struct queue
{
    void *dataPtr;
} QUEUE_NODE;

typedef struct QUEUE
{
    QUEUE_NODE *front;
    QUEUE_NODE *rear;
    int count;
};

QUEUE *createQueue(void);

bool enqueue(QUEUE *que, void *item);

#endif