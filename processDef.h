#ifndef PROCESS_H
#define PROCESS_H

typedef struct process {
    int bt;
    int at;
    int ct;
    int remt;
    int tat;
    int wt;
    int rt;
    int start;
    char *name;
    int index;
    int enqueued;
    int cpu;
} Pr;

#endif
