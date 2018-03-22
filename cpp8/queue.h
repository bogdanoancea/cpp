#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queue *Queue;

//Queue Q_New(int);

Queue Q_New();

void Q_Delete(Queue *pQ);

int Q_Empty(Queue Q);

int Q_Full(Queue Q);

void Enq(Queue Q, void *x);

void* Front(Queue Q);

void* Back(Queue Q);

void* Deq(Queue Q);

#endif // QUEUE_H_INCLUDED
