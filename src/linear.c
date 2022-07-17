#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NIL - 1

typedef int TChave;
typedef struct {
    TChave Chave;
}
TItem;
typedef int TApontador;
typedef struct {
    TItem * Item;
    int n, max;
}
TDicionario;

unsigned long int cmps = 0;

TDicionario * TDicionario_Inicia();
TApontador TDicionario_Pesquisa(TDicionario * D, TChave c);
int TDicionario_Insere(TDicionario * D, TItem x);
int TDicionario_Retira(TDicionario * D, TChave c);

TDicionario * TDicionario_Inicia() {
    TDicionario * D;
    D = (TDicionario * ) malloc(sizeof(TDicionario));
    D -> n = 0;
    D -> max = 10;
    D -> Item = (TItem * ) malloc(D -> max * sizeof(TItem));
    return D;
}

TApontador TDicionario_Pesquisa(TDicionario * D, TChave c) {
    TApontador i;
    for (i = 0; i < D -> n; i++)
        if (cmps++, D -> Item[i].Chave == c)
            return i;
    return NIL;
}

int TDicionario_Insere(TDicionario * D, TItem x) {
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0;
    if (D -> n == D -> max) {
        D -> max *= 2;
        D -> Item = (TItem * ) realloc(D -> Item, D -> max * sizeof(TItem));
    }
    D -> Item[D -> n++] = x;
    return 1;
}

int TDicionario_Retira(TDicionario * D, TChave c) {
    TApontador i;
    i = TDicionario_Pesquisa(D, c);
    if (i == NIL)
        return 0;
    D -> Item[i] = D -> Item[--D -> n];
    if (4 * D -> n == D -> max) {
        D -> max /= 2;
        D -> Item = (TItem * ) realloc(D -> Item, D -> max * sizeof(TItem));
    }
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
    printf("linear,%s,%d", file_name, A_size);

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
