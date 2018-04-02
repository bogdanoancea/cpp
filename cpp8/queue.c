#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct node{
	void	*data;
 	struct	node *next;
};

struct queue{
	int len;
	struct node *first;
	struct node *last;
};

Queue Q_New (){
	Queue Q=(Queue)malloc(sizeof(struct queue));
	Q->len=0;
	Q->first = Q->last = 0;
	return Q;
}

int Q_Size(Queue Q){
	return Q->len;
}

int Q_Empty(Queue Q){
	return Q->len==0;
}

void *Front(Queue Q){
	assert(!Q_Empty(Q));
	return Q->first->data;
}

void *Back(Queue Q){
	assert(!Q_Empty(Q));
	return Q->last->data;
}

void Enq(Queue Q, void *x){
	struct node *nou = (struct node*)malloc(sizeof(struct node));
	nou->data = x;
	nou->next = 0;
	if(Q->last==0)
	        Q->first = nou;
	else
	        Q->last->next = nou;
	Q->last = nou;
	Q->len++;
}

void *Deq(Queue Q){
    assert(!Q_Empty(Q));
     void *x = Q->first->data;
     struct node *del = Q->first;
     Q->first = Q->first->next;
     if(Q->first == 0)
        Q->last = 0;
     free(del);
     Q->len--;
     return x;
}

void display(Queue Q) {
    assert(!Q_Empty(Q));
    struct node* p = Q->first;
    printf("%d\n", *(int*)p->data);
    while(p->next != NULL) {
        p = p->next;
        printf("%d\n", *(int*)p->data);
    }
}
