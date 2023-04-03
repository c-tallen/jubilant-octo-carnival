#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

int is_operation (const char c);
void enqueue(node **queue, int value);
int dequeue(node **queue);
void push(node **stack, int value);
int pop(node **stack);
int priority(const char c);
int top(node **stack);



int main(void)
{
    char equation[] = "24*3/5";
    node *out = NULL;
    node *stack = NULL;
    int i = 0;
    int num;
    while (equation[i] != '\0')
    {
        if (isdigit(equation[i]))
        {
            num = atoi(equation + i);
            enqueue(&out, num);
            // Przesuwa i o długość liczby wczytanej z wejścia
            i += (int) log10(num);
        }
        else if (is_operation(equation[i]))
        {
            while (stack != NULL && priority(equation[i]) <= priority(top(&stack)) )
            {
                enqueue(&out, pop(&stack));
            }
            push(&stack, equation[i]);
        }
        i++;
    }
    while (stack != NULL)
    {
        enqueue(&out, pop(&stack));
    }
    for (node *ptr = out; ptr != NULL; ptr = ptr->next)
    {
        printf("%d\n", ptr->value);
    }
}

int priority(const char c)
{
    if (c == '(')
        return 0;
    else if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
}
int is_operation (const char c)
{
    char operations[] = "+-/*^";
    for (int i = 0; i < strlen(operations); i++)
    {
        if (c == operations[i])
            return 1;
    }
    return 0;
}
void enqueue(node **queue, int value)
{
    node *ptr = *queue;
    node *new = malloc(sizeof(node));
    new->value = value;
    new->next = NULL;

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
}

int top(node **stack)
{
    if (stack != NULL)
    {
        return (*stack)->value;
    }
    else
    {
        return 0;
    }
}