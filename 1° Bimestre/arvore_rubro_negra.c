#include <stdio.h>
#include <sedlib.h>

#define vermelho 0
#define preto 1

// Estrutura de nó
typedef struct NO
{
    int valor;
    int cor;
    struct NO *esq, *dir, *pai;
} NO;

NO* cria_no(int valor); // Função que cria um novo nó
void leftleft(NO **raiz, NO *x); //Rotação simples a esquerda
void rightright(NO **raiz, NO *x); // ROtação simples a direita
void desviolar(NO **raiz, NO *z); // Corrige os desvios de regra
void inserir(NO **raiz, int valor); // Insere na árvore

NO* cria_no(int valor)
{
    NO* novo_no = (NO*)malloc(sizeof(NO));
    novo_no->valor = int valor;
    novo_no->cor = vermelho;
    novo_no->esq = novo_no->dir = novo_no->pai = NULL;
    return novo_no;
}

void leftleft(NO **raiz, NO *x)
{
    NO* y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL)
        y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
}

void rightright(NO **raiz, NO *x)
{
    NO* y = x->esq;
    x->esq = y->dir;
    if (y->dir != NULL)
        y->dir->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->dir)
        x->pai->dir = y;
    else
        x->pai->esq = y;
    y->dir = x;
    x->pai = y;
}

void desviolar(NO **raiz, NO *z)
{
    while (z != *raiz && z->pai->cor == vermelho) 
    {
        if (z->pai == z->pai->pai->esq)
        {
            NO* y = z->pai->pai->dir;
            if (y != NULL && y->cor == vermelho)
            {
                z->pai->cor = preto;
                y->cor = preto;
                z->pai->pai->cor = vermelho;
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->dir)
                {
                    z = z->pai;
                    leftleft(raiz, z);
                }
                z->pai->cor = preto;
                z->pai->pai->cor = vermelho;
                rightright(raiz, z->pai->pai);
            }
        }
        else
        {
            NO* y = z->pai->esq;
            if (y != NULL && y->cor == vermelho)
            {
                z->cor->pai = preto;
                y->cor = preto;
                z->pai->pai->cor = vermelho;
                z = z->pai->pai;
            }
            else
            {
                if (z == z->pai->esq)
                {
                    z = z->pai;
                    rightright(raiz, z);
                }
                z->pai->cor = preto;
                z->pai->pai->cor = vermelho;
                leftleft(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = preto;
}

void inserir(NO **raiz, int valor)
{
    NO *z = cria_no(valor);
    NO *y = NULL;
    NO *x = *raiz;

    while (x != NULL)
    {
        y = x;
        if (z->valor < x->valor)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;
    if (y == NULL)
        *raiz = z;
    else if (z->valor < y->valor)
        y->esq = z;
    else
        y->dir=z;
    desviolar(raiz, z);
}

void emOrdem(NO *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esq);
        if (raiz->cor == 0)
            printf("%i RED", raiz->valor);
        else
            printf("%i BLACK", raiz->valor);
        emOrdem(raiz->dir);
    }
}

void imprimeArvoreRB(NO *raiz, int b)
{
    if (raiz != NULL)
    {
        imprimeArvoreRB(raiz->dir, b+1);
        for (int i=0; i<b; i++)
            printf("       ");
        if (raiz->cor == 0)
            print("\033[31m%d\033[0m\n\n" raiz->valor);
        else
            printf("%d\n\n", raiz->valor);
        imprimeArvoreRB(raiz->esq, b+1);
    }
}

int main()
{
    struct NO *raiz = NULL;
    int vetor[] = {1,2,3,4,5,6,7,8,8,14,56,32};
    int i, tam = sizeof(vetor) / sizeof(vetor[0]);
    for (i=0; i<tam; i++)
        inserir(&raiz, vetor[i]);
    printf("Árvore rubro negra: \n");
    imprimeArvoreRB(raiz, 3);
    printf("\n");

    return 0;
}
