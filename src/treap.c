#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int TChave;

typedef struct {
    TChave Chave;
} TItem;

typedef struct SNo * TArvBin;
typedef struct SNo{
    TItem Item;
    TArvBin Esq, Dir;
    int prioridade;
} TNo;

typedef struct {
    TArvBin Raiz;
} TDicionario;

unsigned long int cmps = 0;

TArvBin TNo_Inicia(TItem Item)
{
    TArvBin pNo = malloc(sizeof(TNo));
    pNo->Item = Item;
    pNo->prioridade = rand();
    pNo->Esq = NULL;
    pNo->Dir = NULL;
    return pNo;
}

TArvBin RotacionaEsquerda(TArvBin pNo)
{
    TArvBin aux = pNo->Dir;
    pNo->Dir = aux->Esq;
    aux->Esq = pNo;
    pNo = aux;
    aux = pNo->Esq;
    return pNo;
}

TArvBin RotacionaDireita(TArvBin pNo)
{
    TArvBin aux = pNo->Esq;
    pNo->Esq = aux->Dir;
    aux->Dir = pNo;
    pNo = aux;
    aux = pNo->Dir;
    return pNo;
}

TDicionario *TDicionario_Inicia()
{
    TDicionario *D = malloc(sizeof(TDicionario));
    D->Raiz = NULL;
    return D;
}

TArvBin InsereRecursivo(TArvBin pNo, TItem Item)
{
    if (pNo == NULL) {
        pNo = TNo_Inicia(Item);
        return pNo;
    }
    if (cmps++, Item.Chave < pNo->Item.Chave) {
        pNo->Esq = InsereRecursivo(pNo->Esq, Item);
        if (pNo->Esq->prioridade < pNo->prioridade)
            pNo = RotacionaDireita(pNo);
    } else if (cmps++, Item.Chave >= pNo->Item.Chave) {
        pNo->Dir = InsereRecursivo(pNo->Dir, Item);
        if (pNo->Dir->prioridade < pNo->prioridade)
            pNo = RotacionaEsquerda(pNo);
    }
    return pNo;
}

TArvBin PesquisaRecursiva(TArvBin pNo, TItem Item)
{
    if (pNo == NULL)
        return NULL;
    if (cmps++, pNo->Item.Chave == Item.Chave)
        return pNo;
    if (cmps++, Item.Chave < pNo->Item.Chave)
        return PesquisaRecursiva(pNo->Esq, Item);
    else
        return PesquisaRecursiva(pNo->Dir, Item);
}

TArvBin RetiraRecursivo(TArvBin pNo, TItem Item)
{
    if (pNo == NULL) {
        return NULL;
    }
    if (cmps++, pNo->Item.Chave == Item.Chave) {
        if (pNo->Esq == NULL && pNo->Dir == NULL) {
            return NULL;
        } else if (pNo->Esq == NULL) {
            return pNo->Dir;
        } else if (pNo->Dir == NULL) {
            return pNo->Esq;
        } else {
            if (pNo->Esq->prioridade < pNo->Dir->prioridade) {
                pNo = RotacionaDireita(pNo);
                pNo->Dir = RetiraRecursivo(pNo->Dir, Item);
            } else {
                pNo = RotacionaEsquerda(pNo);
                pNo->Esq = RetiraRecursivo(pNo->Esq, Item);
            }
        }
    } else if (cmps++, Item.Chave < pNo->Item.Chave) {
        pNo->Esq = RetiraRecursivo(pNo->Esq, Item);
    } else {
        pNo->Dir = RetiraRecursivo(pNo->Dir, Item);
    }
    return pNo;
}

void PercorreRecursivo(TArvBin pNo) {
    if (pNo == NULL)
        return;
    printf("> Esq de %d\n", pNo->Item.Chave);
    PercorreRecursivo(pNo->Esq);
    printf("< Esq de %d\n", pNo->Item.Chave);
    printf("K: %d | RAN: %d\n", pNo->Item.Chave, pNo->prioridade);
    printf("> Dir de %d\n", pNo->Item.Chave);
    PercorreRecursivo(pNo->Dir);
    printf("< Dir de %d\n", pNo->Item.Chave);
}

void TDicionario_Insere(TDicionario *D, TItem Item)
{
    D->Raiz = InsereRecursivo(D->Raiz, Item);
}

TArvBin TDicionario_Pesquisa(TDicionario *D, TItem Item)
{
    return PesquisaRecursiva(D->Raiz, Item);
}

int TDicionario_Retira(TDicionario *D, TItem Item) {
    if (TDicionario_Pesquisa(D, Item) == NULL)
        return 0;
    D->Raiz = RetiraRecursivo(D->Raiz, Item);
    return 1;
}

void TDicionario_Percorre(TDicionario *D) {
    PercorreRecursivo(D->Raiz);
}

void add_items(int *A, int size, TDicionario *D) {
    for (int i = 0; i < size; i++) {
        TDicionario_Insere(D, (TItem){ .Chave=A[i] });
    }
}

void search_items(int *A, int size, TDicionario *D) {
    for (int i = 0; i < size; i++) {
        TDicionario_Pesquisa(D, (TItem){ .Chave=A[i] });
    }
}

void remove_items(int *A, int size, TDicionario *D) {
    for (int i = 0; i < size; i++) {
        TDicionario_Retira(D, (TItem){ .Chave=A[i] });
    }
}

int main(int argc, char **argv) {
    /* declare variables */
    int *A, A_size;
    char *file_name;
    FILE *f;
    clock_t begin_t, end_t;

    /* set a fixed seed for reproducibility */
    srand(1000);

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

    /* create tree */
    TDicionario *D = TDicionario_Inicia();

    /* Print information about the run */
    printf("treap,%s,%d", file_name, A_size);

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
