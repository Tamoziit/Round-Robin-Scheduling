#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue
{
    Pr data;
    struct queue *link;
} QL;

#endif
