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
    int fb;
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

int Altura(TArvBin No) {
    int hEsq, hDir;
    if (No == NULL)
        return -1; // altura de arvore vazia e -1
    hEsq = Altura(No -> Esq);
    hDir = Altura(No -> Dir);
    if (hEsq > hDir)
        return hEsq + 1;
    else
        return hDir + 1;
}

int FB(TArvBin No) {
    if (No == NULL)
        return 0;
    return No -> fb;
}

int ArvoreAVL(TArvBin No) {
    int fb;
    if (No == NULL)
        return 1;
    if (!ArvoreAVL(No -> Esq))
        return 0;
    if (!ArvoreAVL(No -> Dir))
        return 0;
    fb = FB(No);
    if ((fb > 1) || (fb < -1))
        return 0;
    else
        return 1;
}

void LL(TArvBin * pA) {
    TArvBin pB;
    pB = ( * pA) -> Esq;
    ( * pA) -> Esq = pB -> Dir;
    pB -> Dir = * pA;
    if (pB -> fb == 0) {
        ( * pA) -> fb = +1;
        pB -> fb = -1;
    } else {
        ( * pA) -> fb = 0;
        pB -> fb = 0;
    }
    * pA = pB;
}

void RR(TArvBin * pA) {
    TArvBin pB;
    pB = ( * pA) -> Dir;
    ( * pA) -> Dir = pB -> Esq;
    pB -> Esq = * pA;
    if (pB -> fb == 0) {
        ( * pA) -> fb = -1;
        pB -> fb = +1;
    } else {
        ( * pA) -> fb = 0;
        pB -> fb = 0;
    }
    * pA = pB;
}


void LR(TArvBin * pA) {
    TArvBin pB, pC;
    pB = ( * pA) -> Esq;
    pC = pB -> Dir;
    pB -> Dir = pC -> Esq;
    pC -> Esq = pB;
    ( * pA) -> Esq = pC -> Dir;
    pC -> Dir = * pA;
    if (pC -> fb == +1)( * pA) -> fb = -1;
    else( * pA) -> fb = 0;
    if (pC -> fb == -1) pB -> fb = +1;
    else pB -> fb = 0;
    pC -> fb = 0;
    * pA = pC;
}

void RL(TArvBin * pA) {
    TArvBin pB, pC;
    pB = ( * pA) -> Dir;
    pC = pB -> Esq;
    pB -> Esq = pC -> Dir;
    pC -> Dir = pB;
    ( * pA) -> Dir = pC -> Esq;
    pC -> Esq = * pA;
    if (pC -> fb == -1)( * pA) -> fb = +1;
    else( * pA) -> fb = 0;
    if (pC -> fb == +1) pB -> fb = -1;
    else pB -> fb = 0;
    pC -> fb = 0;
    * pA = pC;
}


int BalancaEsquerda(TArvBin * pNo) {
    int fbe = FB(( * pNo) -> Esq);
    if (fbe > 0) {
        LL(pNo);
        return 1;
    } else if (fbe < 0) {
        LR(pNo);
        return 1;
    } else {
        LL(pNo);
        return 0;
    }
}

int BalancaDireita(TArvBin * pNo) {
    int fbd = FB(( * pNo) -> Dir);
    if (fbd < 0) {
        RR(pNo);
        return 1;
    } else if (fbd > 0) {
        RL(pNo);
        return 1;
    } else {
        RR(pNo);
        return 0;
    }
}

int BalancaNo(TArvBin * pNo) {
    int fb = FB( * pNo);
    if (fb > 1)
        return BalancaEsquerda(pNo);
    else if (fb < -1)
        return BalancaDireita(pNo);
    return 0;
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

int Insere(TArvBin * pNo, TItem x) {
    if ( * pNo == NULL) {
        * pNo = (TArvBin) malloc(sizeof(TNo));
        ( * pNo) -> Item = x;
        ( * pNo) -> Esq = NULL;
        ( * pNo) -> Dir = NULL;
        ( * pNo) -> fb = 0;
        return 1;
    } else if (cmps++, x.Chave < ( * pNo) -> Item.Chave) {
        if (Insere( & ( * pNo) -> Esq, x))
            switch (( * pNo) -> fb) { // subarvore esquerda cresceu
            case -1:
                ( * pNo) -> fb = 0;
                return 0;
            case 0:
                ( * pNo) -> fb = +1;
                return 1;
            case +1:
                return !BalancaEsquerda(pNo);
            }
        return 0;
    } else if (cmps++, x.Chave > ( * pNo) -> Item.Chave) {
        if (Insere( & ( * pNo) -> Dir, x))
            switch (( * pNo) -> fb) { // subarvore direita cresceu
            case +1:
                ( * pNo) -> fb = 0;
                return 0;
            case 0:
                ( * pNo) -> fb = -1;
                return 1;
            case -1:
                return !BalancaDireita(pNo);
            }
        return 0;
    } else
        return 0; // retorna 0 caso o item ja estiver na arvore
}

int Sucessor(TArvBin * q, TArvBin * r) {
    if (( * r) -> Esq != NULL) {
        if (Sucessor(q, & ( * r) -> Esq))
            switch (( * r) -> fb) { // subarvore esquerda encolheu
            case +1:
                ( * r) -> fb = 0;
                return 1;
            case 0:
                ( * r) -> fb = -1;
                return 0;
            case -1:
                return BalancaDireita(r);
            }
        return 0;
    } else {
        ( * q) -> Item = ( * r) -> Item;
        * q = * r;
        * r = ( * r) -> Dir;
        return 1;
    }
}

int Retira(TArvBin * p, TChave c) {
    TArvBin q;
    int ret;
    if ( * p == NULL)
        return 0; // retorna 0 caso o item nao esteja na arvore
    else if (cmps++, c < ( * p) -> Item.Chave) {
        if (Retira( & ( * p) -> Esq, c))
            switch (( * p) -> fb) { // subarvore esquerda encolheu
            case +1:
                ( * p) -> fb = 0;
                return 1;
            case 0:
                ( * p) -> fb = -1;
                return 0;
            case -1:
                return BalancaDireita(p);
            }
        return 0;
    } else if (cmps++, c > ( * p) -> Item.Chave) {
        if (Retira( & ( * p) -> Dir, c))
            switch (( * p) -> fb) { // subarvore direita encolheu
            case -1:
                ( * p) -> fb = 0;
                return 1;
            case 0:
                ( * p) -> fb = +1;
                return 0;
            case +1:
                return BalancaEsquerda(p);
            }
        return 0;
    } else {
        q = * p;
        if (q -> Esq == NULL) {
            * p = q -> Dir;
            ret = 1;
        } else if (q -> Dir == NULL) {
            * p = q -> Esq;
            ret = 1;
        } else { // possui dois filhos
            if (Sucessor( & q, & q -> Dir))
                switch (( * p) -> fb) { // subarvore direita encolheu
                case -1:
                    ( * p) -> fb = 0;
                    ret = 1;
                    break;
                case 0:
                    ( * p) -> fb = +1;
                    ret = 0;
                    break;
                case +1:
                    ret = BalancaEsquerda(p);
                    break;
                }
            else ret = 0;
        }
        free(q);
        return ret;
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

    /* create tree */
    TDicionario *D = TDicionario_Inicia();

    /* Print information about the run */
    printf("avltree,%s,%d", file_name, A_size);

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
