#include <stdio.h>
#include <stdlib.h>
#include "bPas2_3.h"

#ifndef BPAS4_H
#define BPAS4_H

#define T_MAX 8

typedef struct 
{
    char* nume_traseu;
    int paduri[10];
    int nr_paduri;
} traseu;

TreeNode* maxValueNode(TreeNode* root);

participant* extract_max(TreeNode** root);

traseu* trasee(FILE* f, int* n); 

void free_trasee(traseu* v, int n);

#endif