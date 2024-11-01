#include <stdio.h>
#include <stdlib.h>

#define ORDEM 3  

typedef struct NoB {
    int chaves[ORDEM - 1];        
    struct NoB *filhos[ORDEM];   
    int numChaves;                
    int folha;                     
} NoB;

// Insere uma chave na árvore B
void inserir(NoB **raiz, int chave);
// Insere uma chave em um nó que não está cheio
void inserirNaoCheio(NoB *no, int chave);
// Divide o filho y de um nó quando ele está cheio
void dividirFilho(NoB *no, int i, NoB *y);
// Remove uma chave da árvore B
void remover(NoB **raiz, int chave);
// Função auxiliar para remoção de uma chave em um nó
void removerDeNo(NoB *no, int chave);
// Função auxiliar para obter a chave predecessora
int obterPredecessor(NoB *no);
// Função auxiliar para obter a chave sucessora
int obterSucessor(NoB *no);
// Função auxiliar para unir dois filhos de um nó
void unir(NoB *no, int idx);
// Função auxiliar para preencher um nó filho que possui menos chaves que o necessário
void preencher(NoB *no, int idx);
// Função auxiliar para emprestar uma chave do nó anterior
void emprestarDoAnterior(NoB *no, int idx);
// Função auxiliar para emprestar uma chave do nó seguinte
void emprestarDoSeguinte(NoB *no, int idx);


NoB *criarNo(int folha) {
    NoB *novoNo = (NoB *)malloc(sizeof(NoB));
    novoNo->numChaves = 0;
    novoNo->folha = folha;
    for (int i = 0; i < ORDEM; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

void inserir(NoB **raiz, int chave) {
    if (*raiz == NULL) {
        *raiz = criarNo(1);
        (*raiz)->chaves[0] = chave;
        (*raiz)->numChaves = 1;
    } else {
        if ((*raiz)->numChaves == ORDEM - 1) {
            NoB *novoNo = criarNo(0);
            novoNo->filhos[0] = *raiz;
            dividirFilho(novoNo, 0, *raiz);
            int i = 0;
            if (novoNo->chaves[0] < chave) i++;
            inserirNaoCheio(novoNo->filhos[i], chave);
            *raiz = novoNo;
        } else {
            inserirNaoCheio(*raiz, chave);
        }
    }
}

void inserirNaoCheio(NoB *no, int chave) {
    int i = no->numChaves - 1;
    if (no->folha) {
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        while (i >= 0 && no->chaves[i] > chave) {
            i--;
        }
        i++;
        if (no->filhos[i]->numChaves == ORDEM - 1) {
            dividirFilho(no, i, no->filhos[i]);
            if (no->chaves[i] < chave) i++;
        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}

void dividirFilho(NoB *no, int i, NoB *y) {
    NoB *z = criarNo(y->folha);
    z->numChaves = ORDEM / 2;

    for (int j = 0; j < ORDEM / 2; j++) {
        z->chaves[j] = y->chaves[j + ORDEM / 2 + 1];
    }

    if (!y->folha) {
        for (int j = 0; j < ORDEM / 2 + 1; j++) {
            z->filhos[j] = y->filhos[j + ORDEM / 2 + 1];
        }
    }

    y->numChaves = ORDEM / 2;
    for (int j = no->numChaves; j >= i + 1; j--) {
        no->filhos[j + 1] = no->filhos[j];
    }

    no->filhos[i + 1] = z;
    for (int j = no->numChaves - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
    }

    no->chaves[i] = y->chaves[ORDEM / 2];
    no->numChaves++;
}

void remover(NoB **raiz, int chave) {
    if (*raiz == NULL) return;
    removerDeNo(*raiz, chave);

    if ((*raiz)->numChaves == 0) {
        NoB *tmp = *raiz;
        if ((*raiz)->folha) {
            *raiz = NULL;
        } else {
            *raiz = (*raiz)->filhos[0];
        }
        free(tmp);
    }
}

void removerDeNo(NoB *no, int chave) {
    int idx = 0;
    while (idx < no->numChaves && no->chaves[idx] < chave) idx++;

    if (idx < no->numChaves && no->chaves[idx] == chave) {
        if (no->folha) {
            for (int i = idx + 1; i < no->numChaves; ++i) {
                no->chaves[i - 1] = no->chaves[i];
            }
            no->numChaves--;
        } else {
            if (no->filhos[idx]->numChaves >= ORDEM / 2) {
                int pred = obterPredecessor(no->filhos[idx]);
                no->chaves[idx] = pred;
                removerDeNo(no->filhos[idx], pred);
            } else if (no->filhos[idx + 1]->numChaves >= ORDEM / 2) {
                int suc = obterSucessor(no->filhos[idx + 1]);
                no->chaves[idx] = suc;
                removerDeNo(no->filhos[idx + 1], suc);
            } else {
                unir(no, idx);
                removerDeNo(no->filhos[idx], chave);
            }
        }
    } else {
        if (no->folha) return;
        int flag = (idx == no->numChaves);
        if (no->filhos[idx]->numChaves < ORDEM / 2) {
            preencher(no, idx);
        }
        if (flag && idx > no->numChaves) {
            removerDeNo(no->filhos[idx - 1], chave);
        } else {
            removerDeNo(no->filhos[idx], chave);
        }
    }
}

int main() {
    NoB *raiz = NULL;
    int opcao, chave;

    while (1) {
        printf("\nÁrvore B - Menu de Operações:\n");
        printf("1. Inserir chave\n");
        printf("2. Remover chave\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%d", &chave);
                inserir(&raiz, chave);
                printf("Chave %d inserida com sucesso.\n", chave);
                break;
            case 2:
                printf("Digite a chave a ser removida: ");
                scanf("%d", &chave);
                remover(&raiz, chave);
                printf("Chave %d removida (se existia).\n", chave);
                break;
            case 3:
                printf("Encerrando o programa.\n");
                exit(0);
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    return 0;
}
