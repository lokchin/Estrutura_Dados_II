#include <stdio.h>
#include <stdlib.h>
#include <limits.h>>

typedef struct NO {
  int dado;
  int alt;
  struct NO *esq;
  struct NO *dir;
} NO;

NO* criaArvBin(int dado);                            // Aloca a raiz e returna ela null.

NO* criaNo(int valor);                               // Aloca o nó, o dado com o valor e as direções.

NO* encontrarMax(NO *raiz);                          /* Verifica se a raiz existe, se não tiver raiz direita
                                                        retorna a raiz, se tiver, chama a função pra direita. */

NO* encontrarMin(NO *raiz);                           /* Verifica se a raiz existe, se não tiver raiz esquerda
                                                         retorna a raiz, se tiver, chama a função pra esquerda. */

int maior(int x, int y);                              // Retorna o maior valor entre dois.

int altura(NO *raiz);                                 // Se não tiver raiz, -1, se tiver, busca a altura

NO* simplesEsquerda(NO *raiz);                        /* O y vai ser o filho da direita da raiz, o f vai ser
                                                         o filho da esquerda do y, e após isso o filho da                                                                    esquerda, vai ser a própria raiz, se a raiz tiver direita
                                                         extra, vai ser o f. */

NO* simplesDireita(NO *raiz);                         /* O y vai ser o filho da esquerda da raiz, o f vai ser
                                                         o filho da direita do y, e após isso o filho da                                                                     direita, vai ser a própria raiz, se a raiz tiver esquerda
                                                         extra, vai ser o f. */

NO* duplaDireita(NO *raiz);                           // Faz uma simplesDireita com a direita, e retorna a                                                                   simplesEsquerda da raiz.

NO* duplaEsquerda(NO *raiz);                          // Faz uma simplesEsquerda com a esquerda, e retorna a                                                                 simplesDireita da raiz.

int fatorBalanceamento(NO *raiz);                     // A altura esquerda menos a altura direita.

NO* balancear(NO *raiz);                              /* Função para balancear, chama o fator de balanceamento
                                                         da raiz.
                                                         Se a raiz for negativa, e o filho negativo,                                                                         simplesEsquerda.
                                                         Se a raiz for positiva, e o filho positivo, simplesDireita.
                                                         Se a raiz for positiva, e o filho negativo, duplaEsquerda.
                                                         Se a raiz for negativa, e o filho positivo, duplaDireita.
                                                          */

NO* inserir(NO *raiz, int valor);

NO* remover(NO *raiz, int valor);

int ehAVL(NO *raiz);                                  /* Define a esq, dir, e o fb, verifica se a raiz existe,
                                                         se não existir, retorna 1, calcula o fb, se o módulo
                                                         de fb for > 1, retorna 0, se não, chama recursivamente
                                                         pra esquerda e direita. */ 


NO* criaArvBin(int dado) {
  NO* raiz = (NO*) malloc(sizeof(NO));
  if (raiz)
    raiz = NULL;
  return raiz;
}

NO *criaNo(int valor) {
  NO *novoNo = malloc(sizeof(NO));
  novoNo->dado = valor;
  novoNo->dir = NULL;
  novoNo->esq = NULL;
  novoNo->alt = 0;
  return novoNo;
};

NO* encontrarMax(NO *raiz) {
  if (!raiz)
    return NULL;
  else if (!raiz->dir)
    return raiz;
  else
    return encontrarMax(raiz->dir);
}

NO* encontrarMin(NO *raiz) {
  if (!raiz)
    return NULL;
  else if (raiz->esq == NULL)
    return raiz;
  else
    return encontrarMin(raiz->esq);
}

int maior(int x, int y) {
  return (x > y) ? x : y;
}

int altura(NO *raiz) {
  if (!raiz)
    return -1;
  else
    return raiz->alt;
}

NO* simplesEsquerda(NO *raiz) {
  NO *y, *f;
  y = raiz->dir;
  f = y->esq;
  y->esq = raiz;
  raiz->dir = f;
  raiz->alt = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
  y->alt = maior(altura(y->esq), altura(y->dir)) + 1;
  return y;
}

NO* simplesDireita(NO *raiz) {
  NO *y, *f;
  y = raiz->esq;
  f = y->dir;
  y->dir = raiz;
  raiz->esq = f;
  raiz->alt = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
  y->alt = maior(altura(y->esq), altura(y->dir)) + 1;
  return y;
}

NO* duplaDireita(NO *raiz) {
  raiz->dir = simplesDireita(raiz->dir);
  return simplesEsquerda(raiz);
}

NO* duplaEsquerda(NO *raiz) {
  raiz->esq = simplesEsquerda(raiz->esq);
  return simplesDireita(raiz);
}

int fatorBalanceamento(NO *raiz) {
  if (!raiz)
    return 0;
  else
    return altura(raiz->esq) - altura(raiz->dir);
}

NO* balancear(NO *raiz) {
  int fb = fatorBalanceamento(raiz);
  if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
    raiz = simplesEsquerda(raiz);
  else if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
    raiz = simplesDireita(raiz);
  else if (fb > 1 && fatorBalanceamento(raiz->esq) < 0)
    raiz = duplaEsquerda(raiz);
  else if (fb < -1 && fatorBalanceamento(raiz->dir) > 0)
    raiz = duplaDireita(raiz);
  return raiz;
}

NO* inserir(NO *raiz, int valor) {
  if (!raiz)
    return NULL;
  if (valor < raiz->dado)
    raiz->esq = inserir(raiz->esq, valor);
  else if (valor > raiz->dado)
    raiz->dir = inserir(raiz->dir, valor);
  raiz->alt = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
  raiz = balancear(raiz);
  return raiz;
}

NO* remover(NO *raiz, int valor) {
  struct NO *temp;
  if (!raiz)
    return NULL;
  if (valor < raiz->dado)
    raiz->esq = remover(raiz->esq, valor);
  else if (valor > raiz->dado)
    raiz->dir = remover(raiz->dir, valor);
  else {
    if (raiz->esq && raiz->dir) {
      temp = encontrarMax(raiz->esq);
      raiz->dado = temp->dado;
      raiz->esq = remover(raiz->esq, temp->dado);
    } else {
      temp = raiz;
      if (!raiz->esq)
        raiz = raiz->dir;
      if (!raiz->dir)
        raiz = raiz->esq;
      free(temp);
    }
  }
  raiz->alt = maior(altura(raiz->dir), altura(raiz->esq)) + 1;
  raiz = balancear(raiz);
  return raiz;
}

int ehAVL(NO *raiz) {
  int esq, dir, fb;
  if(!raiz)
    return 1;
  fb = fatorBalanceamento(raiz);
  if(abs(fb > 1))
    return 0;
  return ehAVL(raiz->esq) && ehAVL(raiz->dir);
}

void imprimir(NO *raiz, int nivel) {
  int i;
  if (raiz) {
    imprimir(raiz->dir, nivel + 1);
    printf("\n\n");
    for (i = 0; i < nivel; i++)
      printf("\t");
    printf("%i", raiz->dado);
    imprimir(raiz->esq, nivel + 1);
  }
}

int main() {
  int op, valor;
  NO *raiz = NULL;

  do {
    printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - "
           "Imprimir\n\n\n\n\t");
    scanf("%i", &op);

    switch (op) {
    case 0:
      printf("SAINDO");
      break;
    case 1:
      printf("\tDigite o valor a ser inserido: ");
      scanf("%i", &valor);
      raiz = inserir(raiz, valor);
      break;
    case 2:
      printf("\tDigite o valor a ser removido: ");
      scanf("%i", &valor);
      raiz = remover(raiz, valor);
      break;
    case 3:
      imprimir(raiz, 1);
      break;
    default:
      printf("\nOpção inválida\n");
    }
  } while (op != 0);
  return 0;
}
