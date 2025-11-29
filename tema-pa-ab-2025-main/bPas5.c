#include "bPas5.h"

void update_exp(MaxHeap* h){
    for(int i=0; i<h->size; i++){
        heap_elements* elem=h->vector[i];

        int suma=0;
        for(int j=0; j<elem->t->nr_paduri; j++){
            suma=suma+elem->t->paduri[j];
        }

        elem->p->exp=(float)elem->p->exp+suma;

        heapify_up(h, i);
    }
}

