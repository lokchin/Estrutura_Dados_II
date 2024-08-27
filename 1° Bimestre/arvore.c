/* 
Aluno: Bruno Santos Lokchin
Turma: CC6N
Github: @lokchin
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {                         // Estrutura básica para um nó
    int dado;
    struct NO *esq;
    struct NO *dir;
} NO;

NO* criaArvBin();                           // Aloca a raiz e retorna NULL por não conter nada ainda.

NO* criaNO(int valor);                      // Aloca o nó, o dado com o valor e as direções.

NO* insereDado(NO *raiz, int valor);        /* Se não tiver raiz, cria um novo nó, se tiver, percorre
                                             a árvore fazendo comparações e retorna a raiz. */
                                             
NO* encontraDado(NO *raiz, int valor);      /* Faz a lógica para percorrer a árvore, até achar a
                                             posição certa, e retorna o valor dentro da posição. */
                                             
NO* acharMinimo(NO *raiz);                   // Encontra o menor valor da esquerda
                                            
NO* removeDado(NO *raiz, int valor);        /* Faz a lógica para percorrer a árvore, até achar a
                                             posição certa, após isso tudo, ele confere se não há
                                             os filhos da raiz, se não tiver, libera a raiz. */

NO* criaArvBin() {
    NO *raiz = (NO*) malloc(sizeof(NO));
  if (raiz)
    raiz = NULL;
  return raiz;
}

NO* criaNO(int valor) {
    NO *novoNo = malloc(sizeof(NO));
    if (novoNo) {
        novoNo->dado = valor;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
    }
    return novoNo;
}

NO* insereDado(NO *raiz, int valor) {
    if (raiz == NULL) {
        return criaNO(valor);
    }
    if (valor < raiz->dado) {
        raiz->esq = insereDado(raiz->esq, valor);
    } else if (valor > raiz->dado) {
        raiz->dir = insereDado(raiz->dir, valor);
    }
    return raiz;
}

NO* encontraDado(NO *raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) {
        return raiz;
    }
    if (valor < raiz->dado) {
        return encontraDado(raiz->esq, valor);
    } else {
        return encontraDado(raiz->dir, valor);
    }
}

NO* acharMinimo(NO *raiz) {
    while (raiz && raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

NO* removeDado(NO *raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }
    if (valor < raiz->dado) {
        raiz->esq = removeDado(raiz->esq, valor);
    } else if (valor > raiz->dado) {
        raiz->dir = removeDado(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL) {
            NO *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NO *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        NO *temp = acharMinimo(raiz->dir);
        raiz->dado = temp->dado;
        raiz->dir = removeDado(raiz->dir, temp->dado);
    }
    return raiz;
}

int main(void) {
    NO *raiz = criaArvBin();
    int N = 8, dados[8] = {50, 100, 30, 20, 40, 45, 35, 37};  //Números para serem inseridos
    
    for (int i = 0; i < N; i++) {
        raiz = insereDado(raiz, dados[i]);
    }
    
    int valorBusca;
    
    while(1) {
        printf("-----------------------------\n");
        printf("-------Buscar na árvore------\n");
        printf("-----------------------------\n\n");
        
        printf("Digite o que esta buscando: ");
        scanf("%i", &valorBusca);
        printf("\n");
        
        NO *resultado = encontraDado(raiz, valorBusca);
        
        if (resultado) {
            printf("Valor %d encontrado na árvore.\n\n\n", valorBusca);
        } else {
            printf("Valor %d não encontrado na árvore.\n\n\n", valorBusca);
        }
    }
    
    return 0;
}
