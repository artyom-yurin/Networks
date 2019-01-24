#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <malloc.h>

struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

struct Stack {
    int curSize;
    struct Node *head;
};

struct Stack *stack;

int empty() {
    if (stack == NULL) {
        fprintf(stderr, "Stack doesn't created\n");
        return NULL;
    }

    return (stack->curSize == 0);
}

void display() {
    if (stack == NULL) {
        fprintf(stderr, "Stack doesn't created\n");
        return;
    }

    struct Node *tmp = stack->head;
    while (tmp != NULL) {
        fprintf(stdin, "%d\n", tmp->value);
        tmp = tmp->next;
    }
}


void pop() {

    if (stack == NULL) {
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

void clear() {
    if (stack == NULL) {
        return;
    }
    while (stack->head != NULL) {
        pop();
    }
}

void create() {
    clear();
    if (stack != NULL) {
        free(stack);
    }
    stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->curSize = 0;
    stack->head = NULL;
}

void stack_size() {
    if (stack == NULL) {
        fprintf(stderr, "Stack doesn't created\n");
        return;
    }

    fprintf(stdin, "Stack size is %d\n", stack->curSize);
}

void push(int value) {

    if (stack == NULL) {
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

int peek() {

    if (stack == NULL) {
        fprintf(stderr, "Stack doesn't created\n");
        return NULL;
    }

    if (stack->curSize == 0) {
        fprintf(stderr, "Stack is empty\n");
        return NULL;
    }

    return stack->head->value;
}

int main() {
    char buffer[1024];
    int fds[2];
    pipe(fds);

    if (fork() == 0) //child
    {
        while (strcmp(buffer, "quit\n") != 0)
        {
            close(fds[0]);
            fgets(buffer, 1024, stdin);
            write(fds[1], buffer, 1024);
            kill(getpid(), SIGSTOP);
        }
    } else //parent
    {
        while (strcmp(buffer, "quit\n") != 0)
        {
            close(fds[1]);
            read(fds[0], buffer, 1024);
            printf("%s", buffer);
            kill(0, SIGCONT);
        }


    }

    return 0;
}