#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node
{

    int Element;
    PtrToNode Next;
};

int isEmpty(Stack);
Stack CreateStack();
void MakeEmpty(Stack);
void Pop(Stack);
int Top(Stack);
int Top(Stack);
void Push(int X, Stack);
void DisposeStack(Stack);

int main()
{

    Stack myStack = CreateStack();
    Push(1, myStack);
    printf("The top is: %d\n", Top(myStack));

    Push(2, myStack);
    Push(3, myStack);
    printf("The top is: %d\n", Top(myStack));

    Pop(myStack);
    printf("The top is: %d\n", Top(myStack));

    MakeEmpty(myStack);
    printf("The top is: %d\n", Top(myStack));

    DisposeStack(myStack);
    printf("The top is: %d\n", Top(myStack));

    printf("\nDone!\n");
    return 0;
}

int isEmpty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack()
{
    Stack S = (Stack)malloc(sizeof(struct Node));

    if (S == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }

    S->Next = NULL;
    MakeEmpty(S);

    return S;
}

void MakeEmpty(Stack S)
{
    if (S == NULL)
    {
        printf("Out of memory!\n");
    }
    else
    {
        while (!isEmpty(S))
            Pop(S);
    }
}

void Pop(Stack S)
{
    PtrToNode firstCell;

    if (isEmpty(S))
    {
        printf("Empty stack!\n");
    }
    else
    {
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free(firstCell);
    }
}

int Top(Stack S)
{

    if (!isEmpty(S))
    {
        return S->Next->Element;
    }
    else
    {
        printf("Empty stack!\n");
        exit(1);
    }
}

void Push(int X, Stack S)
{
    PtrToNode temp;
    temp = (Stack)malloc(sizeof(struct Node));

    if (temp == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }

    temp->Element = X;
    temp->Next = S->Next;
    S->Next = temp;
}

void DisposeStack(Stack S)
{
    MakeEmpty(S);
    free(S);
}
