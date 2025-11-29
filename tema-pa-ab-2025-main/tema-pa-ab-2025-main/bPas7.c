#include "bPas7.h"

Graph * create_graph(){
    Graph* g = (Graph*) malloc(sizeof(Graph));
    g->v = V_MAX;
    g->a = (g_node**) malloc(V_MAX* sizeof(g_node*));

    for (int i = 0; i < V_MAX; i++) {
        g->a[i] = NULL;
        g->grad_in[i] = 0;
        g->grad_out[i] = 0;
        g->e=0;
    }

    return g;         
    }

void add_edge(Graph* g, int from, int to) {
    g_node* new_g_node = (g_node*) malloc(sizeof(g_node));
    new_g_node->nr = to;
    new_g_node->next = g->a[from];
    g->a[from] = new_g_node;

    g->grad_out[from]++;
    g->grad_in[to]++;
    g->e++;
}
void getInDegrees(g_node* a[],int *grad_in) {
    for(int i=0; i<V_MAX; i++){
        grad_in[i]=0;
    }

    for (int i = 0; i < V_MAX; i++) {
        g_node* curent = a[i];
        while (curent != NULL) {
            grad_in[curent->nr]++;
            curent = curent->next;
        }
    }
}

void getOutDegrees(g_node *a[], int *grad_out){
    for(int i=0; i<V_MAX; i++){
    g_node* curent = a[i];

    while(curent != NULL){
        grad_out[i]++;
        curent = curent->next;
    }
}
}

void dfs(g_node* a[], int grad_out[], int vizitat[], int traseu[], int l, int current, Path drumuri[], int* nr_drumuri){
    vizitat[current] = 1;
    traseu[l++] = current;

    if (grad_out[current] == 0) {
        Path d;
        d.l = l;
        for (int i = 0; i < l; i++) {
            d.nodes[i] = traseu[i];
        }
        drumuri[*nr_drumuri] = d;
        (*nr_drumuri)++;
    }
    else {
        g_node* vecin = a[current];
        while (vecin != NULL) {
            if (!vizitat[vecin->nr]) {
                dfs(a, grad_out, vizitat, traseu, l, vecin->nr, drumuri, nr_drumuri);
            }
            vecin = vecin->next;
        }
    }

    vizitat[current] = 0;
}

int compare_paths(Path * p1, Path* p2) {
    int min_len;
    if (p1->l < p2->l) {
        min_len = p1->l;
    }
    else {
        min_len = p2->l;
    }

    for (int i = 0; i < min_len; i++) {
        if (p1->nodes[i] != p2->nodes[i]) {
            return p1->nodes[i] - p2->nodes[i];
        }
    }

    return p1->l - p2->l;
}

void sort_paths(Path drumuri[], int nr_drumuri) {
    for (int i = 0; i < nr_drumuri - 1; i++) {
        for (int j = i + 1; j < nr_drumuri; j++) {
            if (compare_paths(&drumuri[i], &drumuri[j]) > 0) {
                Path aux = drumuri[i];
                drumuri[i] = drumuri[j];
                drumuri[j] = aux;
            }
        }
    }
}

void write_path(FILE* fout, Path drumuri[], int nr_drumuri) {
    sort_paths(drumuri, nr_drumuri);

    for (int i = 0; i < nr_drumuri; i++) {
        fprintf(fout, "T%d: ", i+1);
        for (int j = 0; j < drumuri[i].l; j++) {
            fprintf(fout, "%d ", drumuri[i].nodes[j]);
        }
        fprintf(fout, "\n");
    }
}

// Funcție principală care face DFS de la toate nodurile cu grad de intrare 0
void generate_all_paths(g_node* a[], int* grad_in, int* grad_out, FILE* fout) {
    int vizitat[V_MAX] = {0};
    int traseu[V_MAX];
    Path drumuri[D_MAX];
    int nr_drumuri = 0;

    for (int i = 0; i < V_MAX; i++) {
        if (grad_in[i] == 0) {
            dfs(a, grad_out, vizitat, traseu, 0, i, drumuri, &nr_drumuri);
        }
    }

    write_path(fout, drumuri, nr_drumuri);
}

void free_graph(Graph* g) {
    for (int i = 0; i < V_MAX; i++) {
        g_node* curent = g->a[i];
        while (curent) {
            g_node* tmp = curent;
            curent = curent->next;
            free(tmp);
        }
    }
    free(g->a);
    free(g);
}