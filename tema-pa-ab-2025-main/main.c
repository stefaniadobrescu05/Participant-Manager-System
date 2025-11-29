#include "bPas1.h"
#include "queue.h"
#include "bPas6.h"
#include "bPas7.h"


int main(){
    //PAS1
    //se deschid fiserele de intrare si iesire
    FILE* fin1 = fopen("./Pas_1/candidati.csv", "r");
    FILE* fout1 = fopen("./Pas_1/test_1.csv", "w");

    //daca au fost deschise cu succes atuncti pointerii au adrese valabile, daca nu sunt egali cu NULL
    if (fin1 == NULL){
        printf("Eroare la deschiderea fisierului cu candidati");
    }

    if (fout1 == NULL){
        printf("Eroare la deschiderea fisierului de test");
        return 1;
    }

    fprintf(fout1, "Nume Experienta Varsta Statut_social\n");//se fixeaza headerul(titlul)

    char linie[256]; //bufeer unde se va afla linia citita
    Queue* q = createQueue();

    fgets(linie, sizeof(linie), fin1); // sari peste prima linie pentru a nu fi prelucrat si vechiu header

    while (fgets(linie, sizeof(linie), fin1)){ //se opreste din citit la final de linie
        participant p = parse_line(linie);
        enQueue(q, p);
    }

    Node* current = q->front;//dupa ce coada a fost creata incepem sa scriem in fisierul de iesire de la inceputul cozii
    while (current != NULL){
        fprintf(fout1, "%s %.2f %d %s\n", current->p.nume, current->p.exp, current->p.var, statut_to_string(current->p.s));
                                                                                               //aici se aplica fct de convertire din valori int 
                                                                                               //in cuv coresp, pt ca trb facuta pe ficare cuvant curent in parte
        current = current->next;
    }

    fclose(fin1);
    fclose(fout1);

    //PAS2
    //se initializeaza cei doi arbori 
    TreeNode* bst1=NULL; //lord
    TreeNode* bst2=NULL;//aventurier+cavaler

    while (!isEmpty(q)){// cat timp coada nu este goala (pentru ca in cerinta se precizeaza ca la final coada va fi goala)
        participant p=dequeue(q); //se extrage cate un element pe rand din coadaa cu aceasta functie

        if (p.s==CAVALER || p.s==AVENTURIER) //si se stabileste fiecare element unde va fi introdus cu ajutorul fct insert care are un  mod specific de functionare
            bst2=insert(bst2, p);
        else if (p.s==LORD) 
            bst1=insert(bst1, p);
    }

    FILE* fout2_1=fopen("./Pas_2/test_2_lorzi.csv", "w");//urmeaza sa fie deschise fisierele in care vor fi scrise datele din 
                                                         //arbori si facute verificarile daca s-au putut deschide
    if (!fout2_1){
        printf("Nu pot deschide fiserul");
        return 1;
    }
    FILE* fout2_2=fopen("./Pas_2/test_2_cavaleri_aventurieri.csv", "w");
    if (!fout2_2){
        printf("Nu pot deschide fiserul");
        return 1;
    }

    fprintf(fout2_1, "Nume Experienta Varsta Statut_social\n");
    fprintf(fout2_2, "Nume Experienta Varsta Statut_social\n");

    complete_inorder(bst1, fout2_1); // scrie în fișier
    complete_inorder(bst2, fout2_2);

    fclose(fout2_1);//se inchid fisierele
    fclose(fout2_2);

    freeQueue(q);

    //PAS3
    FILE* fin3=fopen("./Pas_3/contestatii.csv", "r");//urmeaza sa fie deschis fisierul pentru a citi contestiile
    if(!fin3){
        printf("Eroare la deschiderea fisierului de contestatii!");
        return 1;
    }

    FILE* fout3=fopen("./Pas_3/test_3_lorzi.csv", "w");
    if(!fout3){
        printf("Eroare la deschiderea fisierului test_3_lorzi!");
        return 1;
    }

    fgets(linie, sizeof(linie), fin3); // ignoră headerul

    update_bst(&bst1, fin3);

    fprintf(fout3, "Nume Experienta Varsta Statut_social\n");//se fixeaza headerul(titlul)
    complete_inorder(bst1, fout3); // scrie în fișier

    fclose(fin3);
    fclose(fout3);

    //PAS4
    //se deschide fisierul de trasee + verificare pentru a se putea crea vectroul cu informatiii din el
    FILE* fin4=fopen("./Pas_4/trasee.csv", "r");
    if(!fin4) {
        printf("Eroare la deschiderea fisierului cu trasee!");
        return 1;
    }

    traseu *v;
    int nr=0;
    v=trasee(fin4, &nr); //aici se face un vector cu 8 elemente, fiecare de tip traseu, adica fiecare element din vectror va stoca ca 
                         //date numele traseului, un vectror cu padurile specifice si numarul de paduri

    fclose(fin4);//avem vectorul, nu mai este nevoie de fisier

    MaxHeap* heap = NULL;
    heap = create_heap(8); //se creeza heapul cu 8 elemente
    //alternativ 4 lorzi și 4 cavaleri/aventurieri
    for (int i = 0; i < 4; i++) {
        participant* lord = extract_max(&bst1);
        participant* c_a = extract_max(&bst2);

        if (lord && i*2 < nr)
            insert_heap(heap, lord, &v[i*2]);
        if (c_a && i*2+1 < nr)
            insert_heap(heap, c_a, &v[i*2+1]);
    }

    FILE* fout4 = fopen("./Pas_4/test_4.csv", "w");
    if (!fout4) {
        printf("Eroare la deschiderea fișierului test_4.csv");
        return 1;
    }

    //prima linie cu antetul
    fprintf(fout4, "Nume_Traseu - Nume_Participant (Experienta_participant)\n");

    for (int i = 0; i < heap->size; i++) {
        heap_elements* e = heap->vector[i];
        fprintf(fout4, "%s - %s (%.2f)\n", e->t->nume_traseu, e->p->nume, e->p->exp);
    }

    fclose(fout4);

    free_bst(bst1);//se elibereaza spatiul ocupat de arbori
    free_bst(bst2);

    //PAS5
    FILE* fout5= fopen("./Pas_5/test_5.csv", "w");
    if (!fout5) {
        printf("Eroare deschidere fisier");
        return 1;
    }
 
    update_exp(heap);

    fprintf(fout5, "Nume_Traseu - Nume_Participant (Experienta_participant)\n");

    for (int i = 0; i < heap->size; i++) {
        fprintf(fout5, "%s - %s (%.2f)\n", heap->vector[i]->t->nume_traseu,  heap->vector[i]->p->nume,  heap->vector[i]->p->exp);
    }

    fclose(fout5);

    //PAS6
    FILE* fout6= fopen("./Pas_6/test_6.csv", "w");
    if (!fout6) {
        printf("Eroare deschidere fisier");
        return 1;
    }

    fprintf(fout6, "Nume Experienta_totala\n");

    for(int i=0; i<3; i++){
        heap_elements* elem=delete_max(heap);
        fprintf(fout6, "%s %.2f\n", elem->p->nume, elem->p->exp);
        free_heap_element(elem);
    }

    fclose(fout6);

    free_heap(heap);
    free_trasee(v, nr);
    
    //PAS7
    FILE* fin7=fopen("./Pas_7/drumuri.csv", "r");
    if (!fin7) {
        printf("Eroare deschidere fisier cu drumuri");
        return 1;
    }

    FILE* fout7=fopen("./Pas_7/test_7.csv", "w");
    if (!fout7) {
        printf("Eroare deschidere fisier trasee");
        return 1;
    }

    int from, to;
    Graph* g=NULL;
    g=create_graph();

    while(fscanf(fin7, "%d %d", &from, &to)==2)
    add_edge(g, from, to);

    fclose(fin7);

    getInDegrees (g->a, g->grad_in);
    getOutDegrees (g->a, g->grad_out);

    generate_all_paths(g->a, g->grad_in, g->grad_out, fout7);
    fclose(fout7);

    free_graph(g);
    return 0;
}
