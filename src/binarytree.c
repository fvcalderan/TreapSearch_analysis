#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NIL NULL

typedef int TChave;
typedef struct {
    TChave Chave;
}
TItem;
typedef struct SNo * TArvBin;
typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
}
TNo;

typedef TArvBin TApontador;
typedef struct {
    TArvBin Raiz;
    int n;
}
TDicionario;

unsigned long int cmps = 0;

TDicionario * TDicionario_Inicia() {
    TDicionario * D;
    D = (TDicionario * ) malloc(sizeof(TDicionario));
    D -> n = 0;
    D -> Raiz = NULL;
    return D;
}

void Sucessor(TArvBin * q, TArvBin * r) {
    if (( * r) -> Esq != NULL)
        Sucessor(q, & ( * r) -> Esq);
    else {
        ( * q) -> Item = ( * r) -> Item;
        * q = * r;
        * r = ( * r) -> Dir;
    }
}

TArvBin Pesquisa(TArvBin Raiz, TChave c) {
    TArvBin No;
    No = Raiz;
    while ((No != NULL) && (cmps++, c != No -> Item.Chave)) {
        if (cmps++, c < No -> Item.Chave)
            No = No -> Esq;
        else if (cmps++, c > No -> Item.Chave)
            No = No -> Dir;
    }
    return No;
}

int Insere(TArvBin * pRaiz, TItem x) {
    TArvBin * pNo;
    pNo = pRaiz;
    while (( * pNo != NULL) && (cmps++, x.Chave != ( * pNo) -> Item.Chave)) {
        if (cmps++, x.Chave < ( * pNo) -> Item.Chave)
            pNo = & ( * pNo) -> Esq;
        else if (cmps++, x.Chave > ( * pNo) -> Item.Chave)
            pNo = & ( * pNo) -> Dir;
    }
    if ( * pNo == NULL) {
        * pNo = (TArvBin) malloc(sizeof(TNo));
        ( * pNo) -> Item = x;
        ( * pNo) -> Esq = NULL;
        ( * pNo) -> Dir = NULL;
        return 1;
    }
    return 0;
}

int Retira(TArvBin * pRaiz, TChave c) {
    TArvBin * p, q;
    p = pRaiz;
    while (( * p != NULL) && (cmps++, c != ( * p) -> Item.Chave)) {
        if (cmps++, c < ( * p) -> Item.Chave)
            p = & ( * p) -> Esq;
        else if (cmps++, c > ( * p) -> Item.Chave)
            p = & ( * p) -> Dir;
    }
    if ( * p != NULL) {
        q = * p;
        if (q -> Esq == NULL)
            *
            p = q -> Dir;
        else if (q -> Dir == NULL)
            *
            p = q -> Esq;
        else
            Sucessor( & q, & q -> Dir);
        free(q);
        return 1;
    }
    return 0;
}

void Predecessor(TArvBin * q, TArvBin * r) {
    if (( * r) -> Dir != NULL)
        Predecessor(q, & ( * r) -> Dir);
    else {
        ( * q) -> Item = ( * r) -> Item;
        * q = * r;
        * r = ( * r) -> Esq;
    }
}
TApontador TDicionario_Pesquisa(TDicionario * D, TChave c) {
    return Pesquisa(D -> Raiz, c);
}

int TDicionario_Insere(TDicionario * D, TItem x) {
    if (!Insere( & D -> Raiz, x))
        return 0;
    D -> n++;
    return 1;
}

int TDicionario_Retira(TDicionario * D, TChave c) {
    if (!Retira( & D -> Raiz, c))
        return 0;
    D -> n--;
    return 1;
}

void add_items(int *A, int size, TDicionario *D) {
    for (int i = 0; i < size; i++) {
        TDicionario_Insere(D, (TItem){.Chave = A[i]});
    }
}

void search_items(int *A, int size, TDicionario *D) {
    for (int i = 0; i < size; i++) {
        TDicionario_Pesquisa(D, (TChave)(A[i]));
    }
}

void remove_items(int *A, int size, TDicionario *D) {
    for (int i = 0; i < size; i++) {
        TDicionario_Retira(D, (TChave)(A[i]));
    }
}

int main(int argc, char **argv) {
    /* declare variables */
    int *A, A_size;
    char *file_name;
    FILE *f;
    clock_t begin_t, end_t;

    /* check amount of arguments */
    if (argc != 3) {
        printf("Usage: %s file_name size\n", argv[0]);
        return EXIT_SUCCESS;
    }

    /* name arguments */
    file_name = argv[1];
    A_size = atoi(argv[2]);

    /* load array */
    A = (int *) malloc(A_size * sizeof(int));
    f = fopen(file_name, "rb");
    size_t readbytes = fread(A, sizeof(int), A_size, f);

    /* create dictionary */
    TDicionario *D = TDicionario_Inicia();

    /* Print information about the run */
    printf("binary_tree,%s,%d", file_name, A_size);

    /* add, search and remove items (computing CPU time taken) */
    begin_t = clock();
    add_items(A, A_size, D);
    end_t = clock();
    printf(",%ld", cmps);
    printf(",%lf", (double)(end_t - begin_t) / CLOCKS_PER_SEC);
    cmps = 0;

    begin_t = clock();
    search_items(A, A_size, D);
    end_t = clock();
    printf(",%ld", cmps);
    printf(",%lf", (double)(end_t - begin_t) / CLOCKS_PER_SEC);
    cmps = 0;

    begin_t = clock();
    remove_items(A, A_size, D);
    end_t = clock();
    printf(",%ld", cmps);
    printf(",%lf\n", (double)(end_t - begin_t) / CLOCKS_PER_SEC);
    cmps = 0;

    /* free memory, close file descriptors and return success */
    free(A);
    fclose(f);
    return EXIT_SUCCESS;
}
