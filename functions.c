// STEFANICA Matei-Costin 311CB
#include "functions.h"

TCoada *initQ() {
    TCoada *coada = (TCoada *)malloc(sizeof(TCoada));
    if (!coada) {
        printf("Alocare nereusita!");
        return NULL;
    }
    coada->inc = NULL;
    coada->sf = NULL;
    return coada;
}

void intrQ(TCoada *coada, Node *nod) { // inserare element in coada
    TLista elem = (TLista)malloc(sizeof(TCelula));
    if (!elem) {
        printf("Alocare nereusita!");
        return;
    }
    elem->nod = nod;
    if (coada->inc == NULL) {
        // coada e vida
        elem->pre = NULL;
        elem->urm = NULL;
        coada->inc = elem;
        coada->sf = elem;
        return;
    }
    // coada nu e vida
    coada->sf->urm = elem;
    elem->pre = coada->sf;
    coada->sf = elem;
    elem->urm = NULL;
    return;
}

Node *extrQ(TCoada *coada) { // extragere element din coada
    Node *nodExtras;
    if (coada->inc == coada->sf) {
        // mai e un singur element in coada
        nodExtras = coada->inc->nod;
        free(coada->inc);
        coada->inc = NULL;
        coada->sf = NULL;
        return nodExtras;
    }
    // in coada sunt mai multe elemente
    TLista aux;
    nodExtras = coada->inc->nod;
    aux = coada->inc;
    coada->inc = coada->inc->urm;
    coada->inc->pre = NULL;
    free(aux);
    return nodExtras;
}

Node *constrFrunza(int nivel) {
    Node *nod = (Node *)malloc(sizeof(Node));
    if (!nod) {
        printf("Alocare nereusita!");
        return NULL;
    }
    nod->info = (char *)calloc(100, sizeof(char));
    if (!nod->info) {
        printf("Alocare nereusita!");
        return NULL;
    }
    int i;
    for (i = 0; i < 27; i++) {
        // initializare vector de copii cu NULL
        nod->children[i] = NULL;
    } 
    nod->nivel = nivel;
    return nod;
}

void afisareArb(Node *arb, FILE *out) {
    // vom folosi parcurgerea in latime
    TCoada *coada = initQ();
    Node *nodAux;
    intrQ(coada, arb); // inserarea radacinii in coada
    int i, nrNoduri, nrNoduriUrmNivel;
    nrNoduri = 1;
    nrNoduriUrmNivel = 0;
    int cnt = 0;
    int ok = 0;
    // pentru ca radacina este singura pe nivelul ei si inca nu stim cati fii
    // are
    while(coada->inc != NULL) { // cat timp exista noduri in coada
        if (nrNoduri == 0) {
            // am terminat de afisat nodurile de pe un anumit nivel,
            // deci afisez \n
            if (cnt != 0) {
                fprintf(out, "\n"); // pentru a nu incepe cu \n, dar a avea
                                    // \n la fiecare rand nou
            }
            else {
                cnt++;
            }
            nrNoduri = nrNoduriUrmNivel;
            nrNoduriUrmNivel = 0;
        }
        nodAux = extrQ(coada);
        nrNoduri--;
        
        for (i = 0; i < 27; i++) {
            if (nodAux->children[i] != NULL) {
                // bag in coada copiii
                intrQ(coada, nodAux->children[i]);
                nrNoduriUrmNivel++;
            }
        }
        if (ok == 0) { // pentru a nu incepe afisarea cu un spatiu gol,
        // pentru ca radacina e tratata ca un nod normal, dar nu are informatie
            fprintf(out, "%s", nodAux->info);
            ok++;
        }
        else {
            fprintf(out, "%s ", nodAux->info);
        }
    }
    fprintf(out, "\n");
    distrQ(&coada);
}

void inserareSufix(Node *arb, char *cuvant) {
    char *sufix = (char *)calloc(strlen(cuvant) + 1, sizeof(char));
    char *sirAux = (char *)calloc(strlen(cuvant) + 1, sizeof(char));
    int lungimeSufix = 1;
    int pozitie;
    char caracter;
    Node *aux;
    int len = strlen(cuvant);
    while (len - lungimeSufix + 1 > 0) { // pentru a parcurge toate sufixele
        strcpy(sufix, cuvant + strlen(cuvant) - lungimeSufix);
        lungimeSufix++;
        // in sufix am sufixul curent
        aux = arb;
        // parcurgere pana in punctul in care trebuie sa inserez
        while (strlen(sufix) > 0) {
            caracter = sufix[0];
            if (caracter == '$') {
                pozitie = 0;
            }
            else {
                pozitie = (int)caracter - 'a' + 1;
            }
            if (aux->children[pozitie] == NULL) {
                break;
            }
            else {
                aux = aux->children[pozitie];
                strcpy(sirAux, sufix + 1);
                strcpy(sufix, sirAux);
            }
        }
        // am ajuns in locul in care trebuie sa inserez
        while (strlen(sufix) > 0) {
            caracter = sufix[0];
            if (caracter == '$') {
                pozitie = 0;
            }
            else {
                pozitie = (int)caracter - 'a' + 1;
            }
            aux->children[pozitie] = constrFrunza(aux->nivel + 1);
            aux = aux->children[pozitie];
            aux->info[0] = caracter;
            aux->info[1] = '\0';
            strcpy(sirAux, sufix + 1);
            strcpy(sufix, sirAux);
        }
    }
    free(sufix);
    free(sirAux);
}

int nrFrunze(Node *arb) {
    // similar cu afisarea
    int nrFrunze = 0;
    TCoada *coada = initQ();
    Node *nodAux;
    intrQ(coada, arb);
    int i, nrNoduri, nrNoduriUrmNivel;
    nrNoduri = 1;
    nrNoduriUrmNivel = 0;
    // pentru ca radacina este singura pe nivelul ei si inca nu
    // stim cati fii are
    while(coada->inc != NULL) {
        if (nrNoduri == 0) {
            nrNoduri = nrNoduriUrmNivel;
            nrNoduriUrmNivel = 0;
        }
        nodAux = extrQ(coada);
        nrNoduri--;
        
        for (i = 0; i < 27; i++) {
            if (nodAux->children[i] != NULL) {
                intrQ(coada, nodAux->children[i]);
                nrNoduriUrmNivel++;
            }
        }
        if (nodAux->info[0] == '$') {
            nrFrunze++;
        }
    }
    distrQ(&coada);
    return nrFrunze;
}

int nrSufixe(Node *arb, int k) {
    // similar cu afisarea
    int nr = 0;
    TCoada *coada = initQ();
    Node *nodAux;
    intrQ(coada, arb);
    int i, nrNoduri, nrNoduriUrmNivel;
    nrNoduri = 1;
    nrNoduriUrmNivel = 0;
    // pentru ca radacina este singura pe nivelul ei si inca
    // nu stim cati fii are
    while(coada->inc != NULL) {
        if (nrNoduri == 0) {
            nrNoduri = nrNoduriUrmNivel;
            nrNoduriUrmNivel = 0;
        }
        nodAux = extrQ(coada);
        nrNoduri--;
        
        for (i = 0; i < 27; i++) {
            if (nodAux->children[i] != NULL) {
                intrQ(coada, nodAux->children[i]);
                nrNoduriUrmNivel++;
            }
        }
        if (nodAux->info[0] == '$' && nodAux->nivel == k) {
            nr++;
        }
    }
    distrQ(&coada);
    return nr;
}

int nrDescendentiDirecti(Node *arb) {
    // similar cu afisarea
    int nr = 0;
    TCoada *coada = initQ();
    Node *nodAux;
    intrQ(coada, arb);
    int i, nrNoduri, nrNoduriUrmNivel;
    int cnt;
    nrNoduri = 1;
    nrNoduriUrmNivel = 0;
    // pentru ca radacina este singura pe nivelul ei si inca
    // nu stim cati fii are
    while(coada->inc != NULL) {
        if (nrNoduri == 0) {
            nrNoduri = nrNoduriUrmNivel;
            nrNoduriUrmNivel = 0;
        }
        nodAux = extrQ(coada);
        nrNoduri--;
        cnt = 0;
        for (i = 0; i < 27; i++) {
            if (nodAux->children[i] != NULL) {
                cnt++;
                intrQ(coada, nodAux->children[i]);
                nrNoduriUrmNivel++;
            }
        }
        if (cnt > nr) {
            nr = cnt;
        }
    }
    distrQ(&coada);
    return nr;
}

int existaSufix(Node *arb, char *cuvant) {
    char *sufix = (char *)calloc(strlen(cuvant) + 1, sizeof(char));
    strcpy(sufix, cuvant);
    char caracter;
    int pozitie;
    Node *aux;
    aux = arb;
    char *sirAux = (char *)calloc(strlen(cuvant) + 2, sizeof(char));
    while (strlen(sufix) > 0) {
        caracter = sufix[0];
        if (caracter == '$') {
            pozitie = 0;
        }
        else {
            pozitie = (int)caracter - 'a' + 1;
        }
        if (aux->children[pozitie] == NULL) {
            // nu exista sufix
            break;
        }
        else {
            aux = aux->children[pozitie];
            strcpy(sirAux, sufix + 1);
            strcpy(sufix, sirAux);
        }
    }
    if (strlen(sufix)) {
        free(sufix);
        free(sirAux);
        return 0;
    }
    free(sufix);
    free(sirAux);
    return 1;
}

void compact(Node *arb) {
    TCoada *coada = initQ();
    Node *nodAux, *nodCopil;
    intrQ(coada, arb);
    int i, j;
    int nrFii, index;
    // pentru ca radacina este singura pe nivelul ei si inca
    // nu stim cati fii are
    while(coada->inc != NULL) {
        nodAux = extrQ(coada); // scot un nod
        nrFii = 0;
        for (i = 0; i < 27; i++) {
            if (nodAux->children[i] != NULL) { // pun pointerul nodCopil
                                                // spre unul dintre fii
                nrFii++; // numar fiii
                nodCopil = nodAux->children[i];
                index = i; // indexul respectivului fiu
            }
        }
        if (nrFii == 1) { // daca are un singur fiu
            if (nodAux->children[index]->info[0] != '$') {
                strcat(nodAux->info, nodCopil->info);
                for (j = 0; j < 27; j++) {
                    nodAux->children[j] = nodCopil->children[j];
                }
                free(nodCopil->info);
                free(nodCopil);
                intrQ(coada, nodAux);
            }
        }
        else {
            for (i = 1; i < 27; i++) {
                if (nodAux->children[i] != NULL) {
                    intrQ(coada, nodAux->children[i]);
                }
            }
        }
    }
    distrQ(&coada);
}

void eliberareArb(Node *arb) {
    TCoada *coada = initQ();
    Node *nodAux;
    intrQ(coada, arb);
    int i;
    // pentru ca radacina este singura pe nivelul ei si
    // inca nu stim cati fii are
    while(coada->inc != NULL) {
        nodAux = extrQ(coada);        
        for (i = 0; i < 27; i++) {
            if (nodAux->children[i] != NULL) {
                intrQ(coada, nodAux->children[i]);
            }
        }
        free(nodAux->info);
        free(nodAux);
    }
    distrQ(&coada);
}

void distrQ(TCoada **q) {
    if ((*q)->inc == (*q)->sf) {
        free((*q));
    }
}