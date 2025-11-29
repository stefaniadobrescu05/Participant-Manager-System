#include "list.h"

Node* createNode(participant p){
    Node* newNode=(Node*)malloc(sizeof(Node));
    if (newNode==NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return NULL;
    }

    if(newNode==NULL)
    return NULL;

    newNode->p=p;
    newNode->next=NULL;

    return newNode;
}
