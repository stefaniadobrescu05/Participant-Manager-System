#include "queue.h"

Queue* createQueue(){//am  creat o coada in care urmeaza sa adaug elemente din fisier
    Queue* q;
    q=(Queue*)malloc(sizeof(Queue));
    if (q==NULL){
        printf("Eroare la alocarea memoriei!\n");
        return NULL;
    }

    if(q==NULL)
        return NULL;

    q->front=q->rear=NULL;

    return q;
}

void freeQueue(Queue* q){
    Node* temp;
    while (q->front){
        temp = q->front;
        q->front = q->front->next;
        free(temp->p.nume);
        free(temp);
    }

    free(q);
}

void enQueue(Queue* q, participant p) {
    Node* newNode = createNode(p);
    if (!newNode) return;  

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } 
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

participant dequeue(Queue* q){//fct care soate cate un elem pe rand din coada pentrua putea fi pus in bst
    if (q->front==NULL){
        fprintf(stderr, "Coada este goală.\n");
        exit(1);
    }

    Node* temp=q->front;
    participant p=temp->p;

    q->front=q->front->next;
    if (q->front==NULL) 
    q->rear = NULL;

    free(temp);

    return p;
}

int isEmpty(Queue* q){
    return q->front == NULL;
}