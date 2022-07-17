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
    int cor;
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

int EhNegro(TArvBin No) {
    return (No == NULL) || (No -> cor == 0);
}
int EhRubro(TArvBin No) {
    return (No != NULL) && (No -> cor == 1);
}

int AlturaNegra(TArvBin No) {
    int hEsq, hDir;
    if (No == NULL)
        return 0; // altura negra de arvore vazia e 0
    hEsq = AlturaNegra(No -> Esq);
    hDir = AlturaNegra(No -> Dir);
    if (hEsq > hDir)
        return hEsq + EhNegro(No);
    else
        return hDir + EhNegro(No);
}

int ArvoreARN(TArvBin No) {
    if (No == NULL)
        return 1;
    if (!ArvoreARN(No -> Esq))
        return 0;
    if (!ArvoreARN(No -> Dir))
        return 0;
    if (EhRubro(No) && (!EhNegro(No -> Esq) || !EhNegro(No -> Dir)))
        return 0;
    if (AlturaNegra(No -> Esq) != AlturaNegra(No -> Dir))
        return 0;
    return 1;
}

void InverteCor(TArvBin No) {
    if (No != NULL) No -> cor = !No -> cor;
}
void TrocaCores(TArvBin No) {
    InverteCor(No);
    InverteCor(No -> Esq);
    InverteCor(No -> Dir);
}

void RotacaoDireita(TArvBin * pA) {
    TArvBin pB;
    pB = ( * pA) -> Esq;
    ( * pA) -> Esq = pB -> Dir;
    pB -> Dir = * pA;
    * pA = pB;
}

void RotacaoEsquerda(TArvBin * pA) {
    TArvBin pB;
    pB = ( * pA) -> Dir;
    ( * pA) -> Dir = pB -> Esq;
    pB -> Esq = * pA;
    * pA = pB;
}

int BalancaDireita1(TArvBin * pC) {
    TArvBin pD = ( * pC) -> Dir;
    if (EhRubro(pD)) { // caso 4a
        RotacaoEsquerda(pC);
        pC = & ( * pC) -> Esq;
        pD = ( * pC) -> Dir;
    }
    if (pD != NULL) {
        if (EhNegro(pD -> Esq) && EhNegro(pD -> Dir)) { // caso 1
            InverteCor(pD);
            if (EhRubro( * pC)) {
                InverteCor( * pC);
                return 0;
            }
        } else {
            int cor = ( * pC) -> cor;
            ( * pC) -> cor = 0;
            if (EhNegro(pD -> Dir)) // caso 2a
                RotacaoDireita( & ( * pC) -> Dir);
            else
                InverteCor(pD -> Dir);
            RotacaoEsquerda(pC); // caso 3a
            ( * pC) -> cor = cor;
            return 0;
        }
    }
    return 1;
}

int BalancaEsquerda1(TArvBin * pC) {
    TArvBin pD = ( * pC) -> Esq;
    if (EhRubro(pD)) { // caso 4b
        RotacaoDireita(pC);
        pC = & ( * pC) -> Dir;
        pD = ( * pC) -> Esq;
    }
    if (pD != NULL) {
        if (EhNegro(pD -> Esq) && EhNegro(pD -> Dir)) { // caso 1
            InverteCor(pD);
            if (EhRubro( * pC)) {
                InverteCor( * pC);
                return 0;
            }
        } else {
            int cor = ( * pC) -> cor;
            ( * pC) -> cor = 0;
            if (EhNegro(pD -> Esq)) // caso 2b
                RotacaoEsquerda( & ( * pC) -> Esq);
            else
                InverteCor(pD -> Esq);
            RotacaoDireita(pC); // caso 3b
            ( * pC) -> cor = cor;
            return 0;
        }
    }
    return 1;
}

void BalancaEsquerda3(TArvBin * pA, TArvBin * pB, TArvBin * pC) {
    if (EhRubro(( * pC) -> Dir)) // caso 1
        TrocaCores( * pC);
    else {
        if ( * pB == ( * pA) -> Dir) // caso 2a
            RotacaoEsquerda(pA);
        InverteCor( * pA);
        InverteCor( * pC); // caso 3a
        RotacaoDireita(pC);
    }
}

void BalancaDireita3(TArvBin * pA, TArvBin * pB, TArvBin * pC) {
    if (EhRubro(( * pC) -> Esq)) // caso 1
        TrocaCores( * pC);
    else {
        if ( * pB == ( * pA) -> Esq) // caso 2b
            RotacaoDireita(pA);
        InverteCor( * pA);
        InverteCor( * pC); // caso 3b
        RotacaoEsquerda(pC);
    }
}


void BalancaNo(TArvBin * pA, TArvBin * pB, TArvBin * pC) {
    if ((pC != NULL) && EhRubro( * pA) && EhRubro( * pB)) {
        if ( * pA == ( * pC) -> Esq)
            BalancaEsquerda3(pA, pB, pC);
        else
            BalancaDireita3(pA, pB, pC);
    }
}

void InsereRecursivo(TArvBin * pA, TArvBin * pC, TItem x) {
    if ( * pA == NULL) {
        * pA = (TArvBin) malloc(sizeof(TNo));
        ( * pA) -> Item = x;
        ( * pA) -> Esq = NULL;
        ( * pA) -> Dir = NULL;
        ( * pA) -> cor = 1; // o novo no e rubro
    } else if (cmps++, x.Chave < ( * pA) -> Item.Chave) {
        InsereRecursivo( & ( * pA) -> Esq, pA, x);
        BalancaNo(pA, & ( * pA) -> Esq, pC);
    } else if (cmps++, x.Chave > ( * pA) -> Item.Chave) {
        InsereRecursivo( & ( * pA) -> Dir, pA, x);
        BalancaNo(pA, & ( * pA) -> Dir, pC);
    }
}
void Insere(TArvBin * pRaiz, TItem x) {
    InsereRecursivo(pRaiz, NULL, x);
    ( * pRaiz) -> cor = 0; // a raiz e negra
}

int Sucessor(TArvBin * q, TArvBin * r) {
    int bh;
    if (( * r) -> Esq != NULL) {
        if (Sucessor(q, & ( * r) -> Esq))
            return BalancaDireita1(r); // subarvore esquerda encolheu
        return 0;
    } else {
        ( * q) -> Item = ( * r) -> Item;
        * q = * r;
        * r = ( * r) -> Dir;
        bh = EhNegro( * q) && EhNegro( * r);
        if (!bh && EhNegro( * q))
            ( * r) -> cor = 0;
        return bh;
    }
}


int RetiraRecursivo(TArvBin * p, TChave x) {
    TArvBin q;
    int bh;
    if ( * p == NULL)
        return 0; // retorna 0 caso o item nao esteja na arvore
    else if (cmps++, x < ( * p) -> Item.Chave) {
        if (RetiraRecursivo( & ( * p) -> Esq, x))
            return BalancaDireita1(p); // subarvore esquerda encolheu
        return 0;
    } else if (cmps++, x > ( * p) -> Item.Chave) {
        if (RetiraRecursivo( & ( * p) -> Dir, x))
            return BalancaEsquerda1(p); // subarvore direita encolheu
        return 0;
    } else {
        q = * p;
        if (q -> Esq == NULL) {
            * p = q -> Dir;
            bh = EhNegro( * p) && EhNegro(q);
            if (!bh && EhNegro(q))
                ( * p) -> cor = 0;
        } else if (q -> Dir == NULL) {
            * p = q -> Esq;
            bh = EhNegro( * p) && EhNegro(q);
            if (!bh && EhNegro(q))
                ( * p) -> cor = 0;
        } else { // possui dois filhos
            if (Sucessor( & q, & q -> Dir))
                bh = BalancaEsquerda1(p); // subarvore direita encolheu
            else bh = 0;
        }
        free(q);
        return bh;
    }
}

void Retira(TArvBin * pRaiz, TChave x) {
    RetiraRecursivo(pRaiz, x);
    if ( * pRaiz != NULL)
        ( * pRaiz) -> cor = 0; // a raiz e negra
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

TApontador TDicionario_Pesquisa(TDicionario * D, TChave c) {
    return Pesquisa(D -> Raiz, c);
}

int TDicionario_Insere(TDicionario * D, TItem x) {
    Insere( & D -> Raiz, x);
    D -> n++;
    return 1;
}

int TDicionario_Retira(TDicionario * D, TChave c) {
    Retira( & D -> Raiz, c);
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
    printf("rnbtree,%s,%d", file_name, A_size);

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
