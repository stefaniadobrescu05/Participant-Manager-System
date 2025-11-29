#include "bPas4.h"

TreeNode* maxValueNode(TreeNode* root){
    if (!root) 
        return NULL;
    while (root->right) 
        root=root->right;
    return root;
}

participant* extract_max(TreeNode** root){
    if (!*root) 
        return NULL;

    TreeNode* max_node=maxValueNode(*root);

    participant* p = malloc(sizeof(participant));
    p->nume = strdup(max_node->p.nume);  // copie deep
    p->exp = max_node->p.exp;
    p->var = max_node->p.var;
    p->s = max_node->p.s;

    *root=delete_node(*root, p->exp);  // elimină din BST
    return p;
}

traseu* trasee(FILE* f, int* n){
    // Alocăm vectorul de trasee 
    traseu* v=malloc(sizeof(traseu) * T_MAX); 
    char linie[50];  // buffer pentru citirea unei linii din fișier
    int i=0;        // contor pentru trasee

    while (fgets(linie, sizeof(linie), f)){
        char* token = strtok(linie, ":");
        v[i].nume_traseu = strdup(token); 

        token = strtok(NULL, "\n");  // partea cu numerele pădurilor

        int j = 0;  // contor pentru păduri
        char* nr = strtok(token, " ");  // extragem primul număr
        while (nr){
            v[i].paduri[j++] = atoi(nr);  // convertim string la int și stocăm
            nr = strtok(NULL, " ");      // trecem la următorul număr
        }

        v[i].nr_paduri = j;  // salvăm câte păduri are traseul curent
        i++;  // trecem la următorul traseu
    }

    *n = i;     // transmitem înapoi câte trasee am citit

    return v;   // returnăm vectorul cu traseele încărcate
}

void free_trasee(traseu* v, int n){
    for (int i = 0; i < n; i++){
        free(v[i].nume_traseu);
    }
    free(v);
}
