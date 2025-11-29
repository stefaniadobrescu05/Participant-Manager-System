#include <stdio.h>
#include <stdlib.h>
//#include "bst.h"
#include "bPas4.h"

#ifndef HEAP_H 
#define HEAP_H

typedef struct 
{
    participant* p;
    traseu* t;
} heap_elements;

typedef struct 
{
    heap_elements** vector;
    int size;
    int cap;
} MaxHeap;

MaxHeap* create_heap(int cap);

void swap(heap_elements** a, heap_elements** b);

void heapify_up(MaxHeap* h, int i);

void heapify_down(MaxHeap* h, int i);

void insert_heap(MaxHeap* h, participant* p, traseu* t);

void free_heap(MaxHeap* h);

void free_heap_element(heap_elements* e);

#endif