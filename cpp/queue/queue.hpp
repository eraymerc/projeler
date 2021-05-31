#ifndef QUEUE
#define QUEUE

namespace QUEUE
{

    typedef struct queue
    {
        void *dataPtr;
    }QUEUE_NODE;
    typedef struct
    {
        QUEUE_NODE *front;
        QUEUE_NODE *rear;
    }QUEUE;
    
    

} 

#endif