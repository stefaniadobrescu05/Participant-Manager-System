#include "heap.h"

MaxHeap* create_heap(int cap) {
    MaxHeap* h=malloc(sizeof(MaxHeap));
    h->vector=malloc(sizeof(heap_elements*)*cap);
    h->size=0;
    h->cap=cap;
    return h;
}

void swap(heap_elements** a, heap_elements** b) {
    heap_elements* temp=*a;
    *a=*b;
    *b=temp;
}

void heapify_up(MaxHeap* h, int i){
    while (i> 0) {
        int parent = (i- 1) / 2;
        if (h->vector[parent]->p->exp>=h->vector[i]->p->exp) 
            break;
        swap(&h->vector[parent], &h->vector[i]);
        i=parent;
    }
}

void heapify_down(MaxHeap* h, int i){
    while (2 * i + 1 < h->size){ // cât timp are cel puțin un copil (stânga)
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int max = i;

        // Verificăm dacă copilul stâng are experiență mai mare decât părintele
        if (left < h->size && h->vector[left]->p->exp > h->vector[max]->p->exp)
            max = left;

        // Verificăm dacă copilul drept are experiență mai mare decât cea mai mare găsită până acum
        if (right < h->size && h->vector[right]->p->exp > h->vector[max]->p->exp)
            max = right;

        // Dacă părintele e deja mai mare decât ambii copii, nu trebuie schimbat nimic
        if (max == i)
            break;

        // Altfel, facem swap cu copilul mai mare și continuăm mai jos
        swap(&h->vector[i], &h->vector[max]);
        i = max;
    }
}

void insert_heap(MaxHeap* h, participant* p, traseu* t) {
    if (h->size>=h->cap) 
    return;

    heap_elements* e=malloc(sizeof(heap_elements));
    e->p=p;
    e->t=t;

    h->vector[h->size]=e;
    heapify_up(h, h->size);
    h->size++;
}

void free_heap(MaxHeap* h) {
    if (!h) return;

    for (int i = 0; i < h->size; i++) {
        heap_elements* e = h->vector[i];
        if (e) {
            if (e->p) {
                free(e->p->nume);  // numele a fost duplicat cu strdup
                free(e->p);        // eliberăm structura participant
            }
            free(e);               // eliberăm heap_elements
        }
    }

    free(h->vector);  // eliberăm vectorul de pointeri
    free(h);          // eliberăm structura heap-ului
}

void free_heap_element(heap_elements* e) {
    if (!e) return;
    free(e->p->nume);
    free(e->p);
    free(e);
}

