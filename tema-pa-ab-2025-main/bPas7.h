#include <stdio.h>
#include <stdlib.h>

#ifndef BPAS7_H
#define BPAS7_H

#define V_MAX 11
#define D_MAX 1100
#define L_MAX 11 //graf orienat aciclic

typedef struct list{ 
    int nr; //informatia utila = numarul varfului de stocat 
    struct list* next; 
}g_node; 

typedef struct{ 
    int v, e; 
    g_node** a; //vector cu V elemente - capetele de liste  
    int grad_in[V_MAX];
    int grad_out[V_MAX];
} Graph;

typedef struct{
    int nodes[L_MAX];
    int l;
}Path;

Graph * create_graph();

void add_edge(Graph* g, int from, int to);

void getInDegrees(g_node *a[],int *grad_in);

void getOutDegrees(g_node *a[], int *grad_out);

void dfs(g_node* lista[], int gradIesire[], int vizitat[], int traseu[], int l, int current, Path drumuri[], int* nr_drumuri);

int compare_paths(Path* p1, Path* p2);

void sort_paths(Path drumuri[], int nr_drumuri);

void write_path(FILE* fout, Path drumuri[], int nr_drumuri);

void generate_all_paths(g_node* lista[], int* gradIntrare, int* gradIesire, FILE* fout);

void free_graph(Graph* g);

#endif