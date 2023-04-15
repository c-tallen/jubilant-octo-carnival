#include <stdio.h>
#include <math.h>
#include "node.h"
#include "konwersja.h"

int eval(node **ONPeq);

int main(void)
{
    char equation[40];
    printf("Podaj równanie: ");
    scanf("%s", equation);
    node *equationONP = parseONP(equation);
    printf("%d\n", eval(&equationONP));
    return 0;
}

int eval(node **ONPeq)
{
    enum data_type type;
    node *ptr = *ONPeq;
    int eval_value;
    if (ptr == NULL)
    {
        return 0;
    }
    else if (ptr->next != NULL)
    {
        while (ptr->next->next != NULL)
        {
            ptr = ptr->next;
        }
        type = ptr->next->type;
        eval_value = ptr->next->value;
        free(ptr->next);
        ptr->next = NULL;
    }
    else
    {
        type = ptr->type;
        eval_value = ptr->value;
        free(ptr);
        *ONPeq = NULL;
    }

    if (type == integer)
    {
        return eval_value;
    }
    else
    {
        int value = 0, num1, num2;
        num2 = eval(ONPeq);
        num1 = eval(ONPeq);
        switch (eval_value)
        {
        case '+':
            value = num1 + num2;
            break;
        case '-':
            value = num1 - num2;
            break;
        case '/':
            value = num1/num2;
            break;
        case '*':
            value = num1 * num2;
            break;
        case '^':
            value = pow(num1, num2);
            break;
        case '%':
            value = num1 % num2;
            break;
        default:
            break;
        }
        return value;
    }
}