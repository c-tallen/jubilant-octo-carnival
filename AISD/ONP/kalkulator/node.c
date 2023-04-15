#include "node.h"
#include <stdio.h>
#include <stdlib.h>

void enqueue(node **queue, int value, enum data_type type)
{
    node *ptr = *queue;
    node *new = malloc(sizeof(node));
    new->value = value;
    new->next = NULL;
    new->type = type;
    if (ptr == NULL)
    {
        *queue = new;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new;
    }
}

int dequeue(node **queue)
{
    if (*queue != NULL)
    {
        node *ptr = *queue;
        if (ptr->next == NULL)
        {
            int value = ptr->value;
            free(ptr);
            *queue = NULL;
            return value;
        }
        else
        {
            while (ptr->next->next != NULL)
            {
                ptr = ptr->next;
            }
            int value = ptr->next->value;
            free(ptr->next);
            ptr->next = NULL;
            return value;
        }
    }
    return 0;
}

void push(node **stack, int value)
{
    node * new = malloc(sizeof(node));
    new->value = value;
    if (*stack == NULL)
    {
        new->next = NULL;
        *stack = new;
    }
    else
    {
        new->next = *stack;
        *stack = new;
    }

}

int pop(node **stack)
{
    if (*stack != NULL)
    {
        node *temp = (*stack)->next;
        int value = (*stack)->value;
        free(*stack);
        *stack = temp;
        return value;
    }
    return 0;
}

int top(node **stack)
{
    if (stack != NULL)
    {
        return (*stack)->value;
    }
    return 0;
}
