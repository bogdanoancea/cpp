#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED


struct btree;
typedef struct btree *BTree;



/*
creeaza un arbore nou
*/
BTree BTree_New();

/* returneaza 1 daca arborele este gol, 0 altfel
*/
int	BTree_Empty(BTree t);

/*
determina numarul de noduri al arborelui t
*/
int	BTree_Size(BTree t);

/*
returneaza radacina nodului t
*/
BTree BTree_Root(BTree t);


/*
returneaza informatia (cheia) din nodul t
*/
void *BTree_GetKey(BTree t);


/*
seteaza adresa cheii nodului a egală cu key
*/
void BTree_SetKey(BTree node, void *key);

/*
retuneaza 1 dacă nodul node este frunza, 0 altfel
*/
int BTree_Leaf(BTree node);

/*
retuneaza nodul predecessor (tata) al nodului node sau valoarea  NULL
*/
BTree GetPred(BTree node);

/*
face nodul p tata al nodului node. Nodul predecesor p va avea nodul node subarbore stang sau drept,
dupa cum dir este -1 sau 1
*/
void SetPred(BTree node, BTree p, int dir);

/*
returneaza radacina subarborelui stang a lui node

*/
BTree BTree_GetLT(BTree node);

/*
face left subarbore stang a lui node
*/
void BTree_SetLT(BTree node, BTree left);

/*
returneaza radacina subarborelui drept a lui node
*/
BTree BTree_GetRT(BTree node);


/*
face right subarbore stang a lui node
*/
void BTree_SetRT(BTree node, BTree right);


/*
creaza un nod cu cheia key, subarbori si parinte specificaţi;
nodul creat este subarbore stang sau drept a lui node dupa cum dir este -1 sau 1
*/
BTree BTree_CreateNode(void *key, BTree left, BTree right, BTree node, int dir);

/*
creaza un arbore dintr-un nod radacina si doi subarbori specificati
*/
BTree BTree_CreateTree(BTree root, BTree left, BTree right);

/*
returneaza inaltimea arborelui cu radacina root
*/
int	BTree_Height(BTree root);

/*
returneaza adancimea nodului node
*/
int	BTree_Depth(BTree node);


/*
viziteaza arborele cu radacina root in preordine
*/
void PreOrder(BTree root, void (*Visit)(void*));

/*
viziteaza arborele cu radacina root in inordine
*/
void InOrder(BTree root, void (*Visit)(void*));

/*
viziteaza arborele cu radacina root in postordine
*/
void PostOrder(BTree root, void (*Visit)(void*));

void Visit(void *key);

#endif // TREE_H_INCLUDED
