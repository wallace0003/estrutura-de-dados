#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct No {
    int valor;
    struct No* esq;
    struct No* dir;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = malloc(sizeof(No));
    if (novo) {
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// Inserção na árvore binária de busca
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

// Travessia em ordem (esquerda -> raiz -> direita)
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdem(raiz->dir);
    }
}

// Travessia em pré-ordem (raiz -> esquerda -> direita)
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

// Travessia em pós-ordem (esquerda -> direita -> raiz)
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

// Função auxiliar para encontrar o maior valor da subárvore esquerda
No* maiorEsquerda(No* raiz) {
    No* atual = raiz;
    while (atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

// Remoção de um nó da árvore
No* remover(No* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Encontrou o nó a ser removido
        if (raiz->esq == NULL && raiz->dir == NULL) {
            // Caso 1: nó sem filhos
            free(raiz);
            return NULL;
        } else if (raiz->esq == NULL) {
            // Caso 2: só tem filho à direita
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            // Caso 2: só tem filho à esquerda
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        } else {
            // Caso 3: dois filhos
            No* temp = maiorEsquerda(raiz->esq);
            raiz->valor = temp->valor;
            raiz->esq = remover(raiz->esq, temp->valor);
        }
    }
    return raiz;
}

// Função para liberar toda a árvore
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

// Programa principal
int main() {
    No* raiz = NULL;
    int opcao, valor;

    do {
        printf("\n1 - Inserir\n2 - Remover\n3 - Exibir em ordem\n4 - Exibir em pré-ordem\n5 - Exibir em pós-ordem\n0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Valor a inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("Valor a remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
            case 3:
                printf("Árvore em ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;
            case 4:
                printf("Árvore em pré-ordem: ");
                preOrdem(raiz);
                printf("\n");
                break;
            case 5:
                printf("Árvore em pós-ordem: ");
                posOrdem(raiz);
                printf("\n");
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberar(raiz);
    return 0;
}
