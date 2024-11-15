#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "processDef.h"
#include "queueDef.h"

void enQueue(QL **front, QL **rear, Pr val)
{
    QL *newNode = (QL *)malloc(sizeof(QL));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        return;
    }

    val.enqueued = 1;
    newNode->data = val;
    newNode->link = NULL;

    if (*front == NULL)
    {
        *front = newNode;
        *rear = newNode;
    }
    else
    {
        (*rear)->link = newNode;
        *rear = newNode;
    }
}

Pr deQueue(QL **front)
{
    Pr val;

    if (*front == NULL)
    {
        val.index = -1;
        return val;
    }

    QL *temp = *front;
    val = temp->data;
    *front = (*front)->link;

    val.enqueued = 0;
    free(temp);

    return val;
}
