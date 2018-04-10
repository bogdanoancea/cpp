#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tree.h"

struct btree{
    void	*key;
    struct btree *left;
    struct btree *right;
    struct btree *pred;
};


BTree BTree_New () {
    return NULL;
}

int BTree_Empty(BTree root) {
    return root==NULL;
}

int BTree_Size(BTree root) {
	if(!root)
        return 0;
	return BTree_Size(root->left) + BTree_Size(root->right)+1;
}

void *BTree_GetKey(BTree root){
	assert(root);
	return root->key;
}

void BTree_SetKey(BTree root, void *key){
	assert(root);
	root->key = key;
}

int BTree_Leaf(BTree root){
	assert(root);
	return (root->left==0 && root->right==0);
}

BTree BTree_Root(BTree node){
	assert(node);
	while(node->pred)
		node = node->pred;
	return node;
}

BTree BTree_GetPred(BTree node) {
	assert(node);
	return node->pred;
}

BTree BTree_GetLT(BTree node){
	assert(node);
	return node->left;
}

BTree BTree_GetRT(BTree node){
	assert(node);
	return node->right;
}

void BTree_SetLT(BTree root, BTree left){
	assert(!BTree_Empty(root));
	root->left = left;
	if(left)
		left->pred = root;
}

void BTree_SetRT(BTree root, BTree right) {
	assert(!BTree_Empty(root));
	root->right = right;
	if(right)
		right->pred = root;
}

void BTree_SetPred(BTree root, BTree p, int dir) {
	assert(!BTree_Empty(root));
	root->pred = p;
	if(dir==-1)
		p->left = root;
	else
		if(dir==1)
			p->right = root;
}

BTree BTree_CreateNode(void *key, BTree left, BTree right, BTree pred, int dir) {
    BTree node = (BTree)malloc(sizeof(struct btree));
    node->key = key;
    node->left = left;
    node->right = right;
    node->pred = pred;
    if(pred)
    switch(dir){
        case -1: pred->left = node;
                       break;
        case 1:  pred->right = node;
                      break;
        case  0: ;
    }
    return node;
}

BTree BTree_CreateTree(BTree root, BTree left, BTree right){
    assert(root);
    BTree_SetLT(root, left);
    BTree_SetRT(root, right);
    return root;
}


void PreOrder(BTree root, void (*Visit)(void*)){
    if(!BTree_Empty(root)){
        Visit(BTree_GetKey(root));
        PreOrder(BTree_GetLT(root), Visit);
        PreOrder(BTree_GetRT(root), Visit);
    }
}

void InOrder(BTree root, void (*Visit)(void*)){
    if(!BTree_Empty(root)){
        InOrder(BTree_GetLT(root), Visit);
        Visit(BTree_GetKey(root));
        InOrder(BTree_GetRT(root), Visit);
    }
}

void PostOrder(BTree root, void (*Visit)(void*)){
    if(!BTree_Empty(root)){
        PostOrder(BTree_GetLT(root), Visit);
        PostOrder(BTree_GetRT(root), Visit);
        Visit(BTree_GetKey(root));
    }
}

void Visit(void *key) {
    printf("cheia %d ", *(int*)key);
}



