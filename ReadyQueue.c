#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "processDef.h"
#include "queueDef.h"

void enQueue(QL **front, QL **rear, Pr val)
{
    QL *new = (QL *)malloc(sizeof(QL));
    val.enqueued = 1;
    new->data = val;
    new->link = NULL;
    if (*front == NULL)
    {
        *front = new;
        *rear = new;
    }
    else
    {
        (*rear)->link = new;
        *rear = new;
    }
}

Pr deQueue(QL **front)
{
    QL *h = *front;
    Pr val;
    if (h == NULL)
    {
        printf("Empty Queue\n");
        return val;
    }
    else
    {
        QL *temp = h;
        h = h->link;
        val = temp->data;
        val.enqueued = 0;
        free(temp);
        *front = h;
        return val;
    }
}

void printQueue(QL *front)
{
    QL *curr = front;
    if (curr == NULL)
    {
        printf("Empty Queue\n");
    }
    else
    {
        while (curr != NULL)
        {
            printf("%s ", curr->data.name);
            curr = curr->link;
        }
        printf("\n");
    }
}
