#include <stdio.h>
#include <stdlib.h>
#include "bPas1.h"

#ifndef LIST_H
#define LIST_H

typedef struct Node
{
    participant p;
    struct Node* next;
}Node;

Node* createNode(participant p);

#endif