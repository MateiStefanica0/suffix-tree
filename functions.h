// STEFANICA Matei-Costin 311CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *info; // sir de caractere
    struct node *children[27];
    int nivel; // folosit doar pentru taskul 3
} Node, *Tree;

typedef struct celula {
    // lista dublu inlantuita colosita pentru coada
    Tree nod;
    struct celula *urm;
    struct celula *pre;
} TCelula, *TLista;

typedef struct coada {
    TLista inc;
    TLista sf;
} TCoada;

TCoada *initQ();
void intrQ(TCoada *coada, Node *nod);
Node *extrQ(TCoada *coada);
Node *constrFrunza(int nivel);
void afisareArb(Node *arb, FILE *out);
void inserareSufix(Node *arb, char *cuvant);
int nrFrunze(Node *arb);
int nrSufixe(Node *arb, int k);
int nrDescendentiDirecti(Node *arb);
int existaSufix(Node *arb, char *sufix);
void compact(Node *arb);   
void eliberareArb(Node *arb);
void distrQ(TCoada **q);
