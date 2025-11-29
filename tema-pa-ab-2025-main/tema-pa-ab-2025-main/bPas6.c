#include "bPas6.h"

heap_elements* delete_max(MaxHeap* h){
    if (h->size == 0)
        return NULL;

    heap_elements* max_elem = h->vector[0];
    h->vector[0] = h->vector[h->size - 1];
    h->size--;

    heapify_down(h, 0);

    return max_elem;  // returnează elementul șters
}