#include <printf.h>
#include "stack.h"
#include "math.h"

struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

int curSize;
struct Node *head;

int empty()
{
    return (curSize == 0);
}

void display()
{
    struct Node* tmp = head;
    while(tmp != NULL)
    {
        fprintf(stdin, "%d\n", tmp->value);
        tmp = tmp->next;
    }
}

void clear()
{
    while (head != NULL)
    {
        pop();
    }
}

void create()
{
    clear();
    curSize = 0;
    head = NULL;
}

void stack_size()
{
    fprintf(stdin, "Stack size is %d\n", curSize);
}

void push(int value) {

    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->value = value;
    node->next = head;
    node->prev = NULL;

    if (head != NULL) {
        head->prev = node;
    }

    head = node;
    curSize++;
}

void pop() {

    if (curSize == 0) {
        fprintf(stderr, "Stack is empty\n");
    }

    struct Node *tmp = head;
    head = head->next;
    if (curSize != 1) {
        head->prev = NULL;
    }
    free(tmp);
    curSize--;
}

int peek(){

    if (curSize == 0) {
        fprintf(stderr, "Stack is empty\n");
        return INFINITY;
    }

    return head->value;
}