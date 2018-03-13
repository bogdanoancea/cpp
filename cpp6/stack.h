#ifndef _STACK_H
#define _STACK_H
/*
* Type: stackElementT
*/
typedef char stackElementT;

/*
* Type: stackT
*/
typedef struct {
	stackElementT *contents;
	int maxSize;
	int top;
} stackT;

/*
* Function: StackNew
* Usage: StackNew(&stack, maxSize);
*/
void StackNew(stackT *stackP, int maxSize);

/* Function: StackDestroy
* Usage: StackDestroy(&stack);
*/
void StackDestroy(stackT *stackP);

/*
* Functions: StackPush, StackPop
* Usage: StackPush(&stack, element); element = StackPop(&stack);
*/
void StackPush(stackT *stackP, stackElementT element);
stackElementT StackPop(stackT *stackP);

/*
* Functions: StackIsEmpty, StackIsFull
* Usage: if (StackIsEmpty(&stack)) ...
*/
int StackIsEmpty(stackT *stackP);
int StackIsFull(stackT *stackP);

#endif  /* not defined _STACK_H */
