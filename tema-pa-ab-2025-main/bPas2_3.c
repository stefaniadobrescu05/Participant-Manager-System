#include "bPas2_3.h"

//fct creare de arbore bst, respectand niste specificatii
TreeNode* insert(TreeNode* root, participant p) {
//functia porneste cu un arbore care se presupune ca este gol si insereza in root primul element din coada, inainte creand spatiu pentru el
    if (root==NULL) {
        TreeNode* node=(TreeNode*)malloc(sizeof(TreeNode));
        node->p=p;
        node->left=NULL;
        node->right=NULL;

        return node;
    }

    if (p.exp<root->p.exp)  //cand arborele deja nu mai este gol, asigura, in functie de experienta caliatatea de bst prin comparatii prin pasi recursivi
        root->left=insert(root->left, p);//daca exp elem prelucrate este mai mica decat ce este in root, se pune in stanga
    else if(p.exp>=root->p.exp)      
        root->right=insert(root->right, p);

    return root;
}

//fct de scriere in fisiere a detelor din arbore in maniera inorder
void complete_inorder(TreeNode* root, FILE* f) {
    if(root==NULL) 
    return;

    complete_inorder(root->right, f); //se prelucreaza de la dreapta, inorder pentru afisare descrescatoare
    fprintf(f, "%s %.2f %d %s\n", root->p.nume, root->p.exp, root->p.var, statut_to_string(root->p.s));
    complete_inorder(root->left, f);
}

void free_bst(TreeNode* root){ //fct de eliberare a memoriei
    if(root==NULL) 
        return;

    free_bst(root->left);
    free_bst(root->right);
    free(root->p.nume);
    free(root);
}

//Pas 3

//daca vreau sa sterg un nod cu doi copii am nevoie de copilul sau din stanga (acolo este valoarea mai mica)
TreeNode* minValueNode(TreeNode* root){
    // mergem cât mai mult spre stânga (acolo sunt valorile cele mai mici)
    while (root && root->left)
        root = root->left;
    return root; // returnăm nodul cel mai mic găsit
}

void update_bst(TreeNode** root, FILE *f){
    char linie[256];

    while (fgets(linie, sizeof(linie), f)){
        participant p=parse_line(linie);
        if (p.s==LORD){//aici se verfifca daca statutul este de lord 
            *root = delete_node(*root, p.exp);
            free(p.nume);
        }
    }
}

TreeNode* delete_node(TreeNode* root, float exp){
    if (root==NULL) 
        return NULL; // recursivitate: arbore gol

    //daca experienta primita ca parametru este mai mica decat exp nodului in care suntem
    if (exp<root->p.exp){
        root->left=delete_node(root->left, exp);
        //mergem in stanga
    }
    else if(exp>root->p.exp){
        // Căutăm în subarborele drept dacă cheia e mai mare
        root->right=delete_node(root->right, exp);
    }
    else{
        // Am găsit nodul cu experiența căutată
        // Caz 1: Nu are copil sau are doar copil dreapta
        if (root->left==NULL){
            TreeNode* temp=root->right; // putem muta dreptul în locul său
            free(root->p.nume);           // eliberăm numele alocat dinamic
            free(root);                   // eliberăm nodul în sine
            return temp;                  // întorc noua legătură
        }
        // Caz 2: Nu are copil sau are doar copil stânga
        else if (root->right==NULL){
            TreeNode* temp=root->left; // putem muta stânga în locul său
            free(root->p.nume);
            free(root);
            return temp;
        }

        // Caz 3: Are doi copii
        // Căutăm succesorul (cel mai mic nod din subarborele drept)
        TreeNode* minNode=minValueNode(root->right);
            // Salvează exp înainte de a modifica root
            float min_exp = minNode->p.exp;

            free(root->p.nume);
            root->p.nume = strdup(minNode->p.nume);
            root->p.exp = min_exp;
            root->p.var = minNode->p.var;
            root->p.s = minNode->p.s;

            // Șterge nodul duplicat folosind valoarea originală
            root->right = delete_node(root->right, min_exp);

    }

    if (root->right == root){ 
        printf(" root->right pointează către root! Ciclu creat!\n");
    }

    // Returnăm rădăcina curentă
    return root;
}


