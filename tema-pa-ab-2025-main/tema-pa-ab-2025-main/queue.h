#include <stdio.h>
#include <stdlib.h>
#include "list.h" //daca in lista.h am inclus bib pas1 pentru ca acolo am definita structura participant 
                    //mai trb apelata si aici biblioteca cu structua participant?

#ifndef QUEUE_H
#define QUEUE_H

typedef struct
{
    Node *front, *rear;
}Queue;

Queue* createQueue();

void enQueue(Queue* q, participant p);

int isEmpty(Queue* q);

void freeQueue(Queue* q);

participant dequeue(Queue* q);

#endif