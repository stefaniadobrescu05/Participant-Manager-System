#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "bPas1.h"

#ifndef BPAS2_3_H
#define BPAS2_3_H

typedef struct TreeNode {
    participant p;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* insert(TreeNode* root, participant p);

void complete_inorder(TreeNode* root, FILE* f);

void free_bst(TreeNode* root);

TreeNode* minValueNode(TreeNode* root);

void update_bst(TreeNode** root, FILE *f);

TreeNode* delete_node(TreeNode* root, float exp);

#endif