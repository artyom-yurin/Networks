#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <malloc.h>
#include <stdlib.h>

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
        while (strcmp(buffer, "quit\n") != 0) {
            close(fds[0]);
            printf("Enter command: ");
            fgets(buffer, 1024, stdin);
            write(fds[1], buffer, 1024);
            kill(getpid(), SIGSTOP);
        }
    } else //parent
    {
        while (strcmp(buffer, "quit\n") != 0) {
            close(fds[1]);
            read(fds[0], buffer, 1024);
            char *token = strtok(buffer, " ");;
            if (strcmp(token, "push") == 0) {
                token = strtok(NULL, "\n");
                int number = atoi(token);
                printf("Push %d\n", number);
            } else if (strcmp(token, "peek\n") == 0) {
                printf("Peek\n");
            } else if (strcmp(token, "pop\n") == 0) {
                printf("pop\n");
            } else if (strcmp(token, "empty\n") == 0) {
                printf("empty\n");
            } else if (strcmp(token, "display\n") == 0) {
                printf("display\n");
            } else if (strcmp(token, "create\n") == 0) {
                printf("create\n");
            } else if (strcmp(token, "stack_size\n") == 0) {
                printf("stack_size\n");
            } else if (strcmp(token, "help\n") == 0) {
                printf("Commands:\n");
                printf("create - create a stack\n");
                printf("push *value* - push some integer value to the stack\n");
                printf("pop - pop last element from the stack\n");
                printf("peek - return the value of top element on the stack\n");
                printf("empty - return 1 if the stack is empty, otherwise 0\n");
                printf("display - print all elements from top to bottom\n");
                printf("stack_size - print current size of the stack:\n");
                printf("quit - quit from application\n");
            } else if (strcmp(token, "quit\n") != 0) {
                printf("Unknown command. Use command help for look to commands list\n");
            }
            kill(0, SIGCONT);
        }


    }

    return 0;
}