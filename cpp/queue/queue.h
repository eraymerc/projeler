#ifndef QU
#define QU

typedef struct node
{
    void *dataPtr;
    struct node *next;
} QUEUE_NODE;

typedef struct QUEUE
{
    QUEUE_NODE *front;
    QUEUE_NODE *rear;
    int count;
};

QUEUE *createQueue(void);

bool enqueue(QUEUE *queue, void *item);

bool dequeue(QUEUE *queue, void **item);
#endif