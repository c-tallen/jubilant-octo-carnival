#ifndef NODE_H
#define NODE_H

enum data_type {
    integer, operation
};

typedef struct node {
    int value;
    struct node *next;
    enum data_type type;
} node;

void enqueue(node **queue, int value, enum data_type type);
int dequeue(node **queue);
void push(node **stack, int value);
int pop(node **stack);
int top(node **stack);

#endif // NODE_H