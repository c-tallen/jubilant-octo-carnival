//
// Created by Krzysztof Wilczewski on 15/04/2023.
//

#include <iostream>
#include <stack>
#include <queue>
#include <cmath>

typedef enum {
    c, i
} element_type;

struct eq_element {
    element_type elementType;
    int value;
    eq_element(int a_val, element_type a_elem){
        elementType = a_elem;
        value = a_val;
    }
};
std::queue<eq_element> ONPparse (const std::string& equation);
void print_eq(std::queue<eq_element> eq);

int main(){
    std::queue<eq_element> onp = ONPparse("24/3^3");
    print_eq(onp);

}

void print_eq(std::queue<eq_element> eq)
{
    while(!eq.empty())
    {
        if (eq.front().elementType == i)
            std::cout << eq.front().value << "\t";
        else
            std::cout << (char) eq.front().value << "\t";
        eq.pop();
    }
}

int priority(const char c)
{
    if (c == '(')
        return 0;
    else if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/' || c == '%')
        return 2;
    else if (c == '^')
        return 3;
    else return -1;
}

std::queue<eq_element> ONPparse (const std::string& equation)
{
    std::queue<eq_element> output;
    std::stack<char> operations;
    if (equation.empty())
        return output;
    char *eq = const_cast<char *>(equation.data());
    int curr_char;
    int j = 0;
    int eq_len = equation.size();
    while (j < eq_len)
    {
        if (isdigit(eq[j]))
        {
           sscanf(eq+j, "%d", &curr_char);
           output.push(eq_element(curr_char, i));
           j += (int)log10(curr_char);
        } else if (priority(eq[j]) != -1)
        {
            while(!operations.empty() && priority(eq[j]) <= priority(operations.top()))
            {
                output.push(eq_element(operations.top(), c));
                operations.pop();
            }
            operations.push(eq[j]);
        }
        else if (eq[j] == '(')
        {
            operations.push('(');
        } else if (eq[j] == ')')
        {
            int op;
            while (!operations.empty())
            {
                op = (unsigned char)operations.top();
                operations.pop();
                if (op == '(')
                {
                    break;
                }
                else
                {
                    output.push(eq_element(op, c));
                }
            }
            if (operations.empty() && op != '(')
            {
                printf("Złe rownianie.\n");
                return output;
            }
        }
        j++;
    }
    while (!operations.empty())
    {
        output.push(eq_element(operations.top(), c));
        operations.pop();
    }
    return output;
}