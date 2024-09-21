#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int valor;
    int *esq;
    int *dir;
} NO

int filho_esquerda(int pai, int tam) {
    int filho = (2*pai)+1;
    if (filho<tam) { 
        return filho;
    }
    return -1;
}

int filho_direita(int pai){
    return 2 * pai + 2;
}

int pai_heap(int filho) {
    return (int) (filho - 1) / 2;
}

int main() {
    int vetor[] = {33, 32, 31, 30, 29, 28};
    int tam = sizeof(vetor) / sizeof(vetor(int))
    for (int i=0; i<tam/2; i++) {
        printf("Pai: %i - Filhos: %i e %i\n", vetor[i], vetor[filho_esquerda(i)], vetor[filho_direita(i)]);
    }
}