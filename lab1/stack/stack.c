#include <printf.h>
#include "stack.h"
#include "math.h"

struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

struct Stack
{
    int curSize;
    struct Node *head;
};

struct Stack* stack;

int empty()
{
    if(stack == NULL)
    {
        fprintf(stderr, "Stack doesn't created\n");
        return NULL;
    }

    return (stack->curSize == 0);
}

void display()
{
    if(stack == NULL)
    {
        fprintf(stderr, "Stack doesn't created\n");
        return;
    }

    struct Node* tmp = stack->head;
    while(tmp != NULL)
    {
        fprintf(stdin, "%d\n", tmp->value);
        tmp = tmp->next;
    }
}

void clear()
{
    if(stack == NULL)
    {
        return;
    }
    while (stack->head != NULL)
    {
        pop();
    }
}

void create()
{
    clear();
    if(stack != NULL)
    {
        free(stack);
    }
    stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->curSize = 0;
    stack->head = NULL;
}

void stack_size()
{
    if(stack == NULL)
    {
        fprintf(stderr, "Stack doesn't created\n");
        return;
    }

    fprintf(stdin, "Stack size is %d\n", stack->curSize);
}

void push(int value) {

    if(stack == NULL)
    {
        fprintf(stderr, "Stack doesn't created\n");
        return;
    }

    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->value = value;
    node->next = stack->head;
    node->prev = NULL;

    if (stack->head != NULL) {
        stack->head->prev = node;
    }

    stack->head = node;
    stack->curSize++;
}

void pop() {

    if(stack == NULL)
    {
        fprintf(stderr, "Stack doesn't created\n");
        return;
    }

    if (stack->curSize == 0) {
        fprintf(stderr, "Stack is empty\n");
        return;
    }

    struct Node *tmp = stack->head;
    stack->head = stack->head->next;
    if (stack->curSize != 1) {
        stack->head->prev = NULL;
    }
    free(tmp);
    stack->curSize--;
}

int peek(){

    if(stack == NULL)
    {
        fprintf(stderr, "Stack doesn't created\n");
        return NULL;
    }

    if (stack->curSize == 0) {
        fprintf(stderr, "Stack is empty\n");
        return NULL;    
    }

    return stack->head->value;
}