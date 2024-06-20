// STEFANICA Matei-Costin 311CB
#include "functions.h"

int main(int argc, char *argv[]) {

    Node *arbore = constrFrunza(-1);
    int n; // nr de sufixe
    int m; // nr de sufixe cautate la taskul 3
    int i;
    int k; // pentru taskul 2
    char k_char;
    int frunze, sufixe, descendenti;
    char *sufix = (char *)calloc(100, sizeof(char)); 

    if (strcmp(argv[1], "-c1") == 0) { // task 1
        FILE *in = fopen(argv[2], "r");
        FILE *out = fopen(argv[3], "w"); // deschidere fisiere
        fscanf(in, "%d", &n);
        for (i = 0; i < n; i++) {
            // citirea si inserarea sufixelor in arbore
            fscanf(in, "%s", sufix);
            strcat(sufix, "$");
            inserareSufix(arbore, sufix);
        }
        afisareArb(arbore, out);
        fclose(in);
        fclose(out); // inchidere fisiere
    }
    else if (strcmp(argv[1], "-c2") == 0) { // task 2
        FILE *in = fopen(argv[3], "r");
        FILE *out = fopen(argv[4], "w"); // deschidere fisiere
        fscanf(in, "%d", &n);
        k_char = argv[2][0]; 
        k = k_char - '0'; // pentru a face conversia de la char la int
        for (i = 0; i < n; i++) {
            // citirea si inserarea sufixelor in arbore
            fscanf(in, "%s", sufix);
            strcat(sufix, "$");
            inserareSufix(arbore, sufix);
        }
        // apelare functii statistici
        frunze = nrFrunze(arbore);
        sufixe = nrSufixe(arbore, k);
        descendenti = nrDescendentiDirecti(arbore);
        fprintf(out, "%d\n%d\n%d\n", frunze, sufixe, descendenti);
        fclose(in);
        fclose(out); // inchidere fisiere
    }
    else if (strcmp(argv[1], "-c3") == 0) { // task 3
        FILE *in = fopen(argv[2], "r");
        FILE *out = fopen(argv[3], "w"); // deschidere fisiere
        fscanf(in, "%d", &n);
        fscanf(in, "%d", &m);
        for (i = 0; i < n; i++) {
            // citirea si inserarea sufixelor in arbore
            fscanf(in, "%s", sufix);
            strcat(sufix, "$");
            inserareSufix(arbore, sufix);
        }
        for (i = 0; i < m; i++) {
            // citire si cautare sufixe in arbore
            fscanf(in, "%s", sufix);
            strcat(sufix, "$");
            fprintf(out, "%d\n", existaSufix(arbore, sufix));
        }
        fclose(in);
        fclose(out); // inchidere fisiere
    }
    else if (strcmp(argv[1], "-c4") == 0) { // task 4
        FILE *in = fopen(argv[2], "r");
        FILE *out = fopen(argv[3], "w"); // deschidere fisiere
        fscanf(in, "%d", &n);
        for (i = 0; i < n; i++) {
            // citirea si inserarea sufixelor in arbore
            fscanf(in, "%s", sufix);
            strcat(sufix, "$");
            inserareSufix(arbore, sufix);
        }
        compact(arbore); // creare arbore compact
        afisareArb(arbore, out);
        fclose(in);
        fclose(out); // inchidere fisiere
    }
    free(sufix);
    eliberareArb(arbore);
    return 0;
}