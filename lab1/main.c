#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <malloc.h>
#include <stdlib.h>
#include <values.h>

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
        printf(">Stack doesn't created\n");
        return INT_MAX;
    }

    return (stack->curSize == 0);
}

void display() {
    if (stack == NULL) {
        printf(">Stack doesn't created\n");
        return;
    }

    if (stack->curSize == 0) {
        printf(">Stack is empty\n");
        return;
    }

    struct Node *tmp = stack->head;
    while (tmp != NULL) {
        printf(">%d\n", tmp->value);
        tmp = tmp->next;
    }
}


void pop() {

    if (stack == NULL) {
        printf(">Stack doesn't created\n");
        return;
    }

    if (stack->curSize == 0) {
        printf(">Stack is empty\n");
        return;
    }

    struct Node *tmp = stack->head;
    stack->head = stack->head->next;
    if (stack->curSize != 1) {
        stack->head->prev = NULL;
    }
    printf(">Poped %d from stack\n", tmp->value);
    free(tmp);
    stack->curSize--;
}

void clear() {
    if (stack == NULL) {
        return;
    }

    printf(">Clearing the stack\n");
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
        printf(">Stack doesn't created\n");
        return;
    }

    printf(">Stack size is %d\n", stack->curSize);
}

void push(int value) {

    if (stack == NULL) {
        printf(">Stack doesn't created\n");
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

    printf(">Pushed %d\n", value);
}

int peek() {

    if (stack == NULL) {
        printf(">Stack doesn't created\n");
        return INT_MAX;
    }

    if (stack->curSize == 0) {
        printf(">Stack is empty\n");
        return INT_MAX;
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
            printf("\nEnter command: ");
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
                push(number);
            } else if (strcmp(token, "peek\n") == 0) {
                int i = peek();
                if(i != INT_MAX)
                {
                    printf(">Stack top value is %d\n", i);
                }
            } else if (strcmp(token, "pop\n") == 0) {
                pop();
            } else if (strcmp(token, "empty\n") == 0) {
                if(empty() != INT_MAX)
                {
                    if(empty())
                    {
                        printf(">The stack is empty\n");
                    } else {
                        printf(">The stack isn't empty\n");
                    }
                }
            } else if (strcmp(token, "display\n") == 0) {
                display();
            } else if (strcmp(token, "create\n") == 0) {
                create();
                printf(">The stack has been created\n");
            } else if (strcmp(token, "stack_size\n") == 0) {
                stack_size();
            } else if (strcmp(token, "help\n") == 0) {
                printf(">Commands:\n");
                printf(">create - create a stack\n");
                printf(">push *value* - push some integer value to the stack\n");
                printf(">pop - pop last element from the stack\n");
                printf(">peek - return the value of top element on the stack\n");
                printf(">empty - return 1 if the stack is empty, otherwise 0\n");
                printf(">display - print all elements from top to bottom\n");
                printf(">stack_size - print current size of the stack:\n");
                printf(">quit - quit from application\n");
            } else if (strcmp(token, "quit\n") != 0) {
                printf(">Unknown command. Use command help for look to commands list\n");
            }
            kill(0, SIGCONT);
        }


    }

    return 0;
}