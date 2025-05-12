#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice {
    int chave;
    struct Vertice *esq;
    struct Vertice *dir;
    int altura;
} Vertice;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(Vertice *n) {
    if (n == NULL)
        return -1;
    return n->altura;
}

int fatorBalanceamento(Vertice *n) {
    if (n == NULL)
        return 0;
    return altura(n->dir) - altura(n->esq);
}

// Rotações
Vertice* rotacaoEsquerda(Vertice *x) {
    Vertice *y = x->dir;
    x->dir = y->esq;
    y->esq = x;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

Vertice* rotacaoDireita(Vertice *y) {
    Vertice *x = y->esq;
    y->esq = x->dir;
    x->dir = y;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

// Inserção com balanceamento
Vertice* inserir(Vertice *raiz, int chave) {
    if (raiz == NULL) {
        Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
        novo->chave = chave;
        novo->esq = novo->dir = NULL;
        novo->altura = 0;
        return novo;
    }

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);
    else
        return raiz; // chave duplicada não é permitida

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
    int fb = fatorBalanceamento(raiz);

    // Casos de desbalanceamento:
    if (fb < -1 && chave < raiz->esq->chave)
        return rotacaoDireita(raiz); // Caso 3

    if (fb > 1 && chave > raiz->dir->chave)
        return rotacaoEsquerda(raiz); // Caso 1

    if (fb < -1 && chave > raiz->esq->chave) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz); // Caso 4
    }

    if (fb > 1 && chave < raiz->dir->chave) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz); // Caso 2
    }

    return raiz;
}

// Impressão em ordem
void imprimir(Vertice *raiz, int nivel) {
    if (raiz != NULL) {
        imprimir(raiz->dir, nivel + 1);
        for (int i = 0; i < nivel; i++) printf("   ");
        printf("%d\n", raiz->chave);
        imprimir(raiz->esq, nivel + 1);
    }
}

int main() {
    int valores[] = {21, 26, 30, 9, 4, 14, 28, 18, 15, 10, 2, 3, 7};
    int n = sizeof(valores) / sizeof(valores[0]);

    Vertice *raiz = NULL;
    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("Árvore AVL final:\n");
    imprimir(raiz, 0);

    return 0;
}
