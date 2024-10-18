#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No {
    int chave;
    int prioridade; 
    struct No *esq;
    struct No *dir;
} No;

// Função para criar um novo nó
No* criarNo(int chave);
// Função para rotacionar à direita
No* rotacionarDir(No* y);
// Função para rotacionar à esquerda
No* rotacionarEsq(No* x);
// Função para inserir um nó na Treap
No* inserir(No* raiz, int chave);
// Função para deletar um nó da Treap
No* deletar(No* raiz, int chave);
// Função para buscar um nó na Treap
No* buscar(No* raiz, int chave);
// Função para exibir a Treap (em ordem)
void exibirEmOrdem(No* raiz);


No* criarNo(int chave) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->prioridade = rand() % 100; 
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

No* rotacionarDir(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    return x;
}

No* rotacionarEsq(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    return y;
}

No* inserir(No* raiz, int chave) {
    if (raiz == NULL)
        return criarNo(chave);
    if (chave < raiz->chave) {
        raiz->esq = inserir(raiz->esq, chave);
        if (raiz->esq->prioridade > raiz->prioridade)
            raiz = rotacionarDir(raiz);
    } else if (chave > raiz->chave) {
        raiz->dir = inserir(raiz->dir, chave);
        if (raiz->dir->prioridade > raiz->prioridade)
            raiz = rotacionarEsq(raiz);
    }
    return raiz;
}

No* deletar(No* raiz, int chave) {
    if (raiz == NULL)
        return raiz;
    if (chave < raiz->chave)
        raiz->esq = deletar(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = deletar(raiz->dir, chave);
    else {
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            raiz = temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            raiz = temp;
        } else {
            if (raiz->esq->prioridade > raiz->dir->prioridade) {
                raiz = rotacionarDir(raiz);
                raiz->dir = deletar(raiz->dir, chave);
            } else {
                raiz = rotacionarEsq(raiz);
                raiz->esq = deletar(raiz->esq, chave);
            }
        }
    }
    return raiz;
}

No* buscar(No* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return buscar(raiz->esq, chave);
    else
        return buscar(raiz->dir, chave);
}

void exibirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esq);
        printf("Chave: %d, Prioridade: %d\n", raiz->chave, raiz->prioridade);
        exibirEmOrdem(raiz->dir);
    }
}



int main() {
    srand(time(NULL)); 
    No* raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Treap em ordem:\n");
    exibirEmOrdem(raiz);

    int chave = 40;
    No* resultado = buscar(raiz, chave);
    if (resultado != NULL)
        printf("\nChave %d encontrada com prioridade %d\n", resultado->chave, resultado->prioridade);
    else
        printf("\nChave %d não encontrada\n", chave);

    printf("\nDeletando chave 40\n");
    raiz = deletar(raiz, 40);
    printf("Treap em ordem após excluir:\n");
    exibirEmOrdem(raiz);

    return 0;
}
