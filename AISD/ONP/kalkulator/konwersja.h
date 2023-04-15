#ifndef KONWERSJA_H
#define KONWERSJA_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

node * parseONP(const char *equation);
int is_operation (const char c);
int priority(const char c);
void queue_to_string(node **queue, char *output);

#endif // KONWERSJA_H