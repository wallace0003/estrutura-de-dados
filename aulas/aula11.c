#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice {
    int chave;
    struct Vertice *esq;
    struct Vertice *dir;
    struct Vertice *pai; // novo campo
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

// Rotações com atualização do pai
Vertice* rotacaoEsquerda(Vertice *x) {
    Vertice *y = x->dir;
    x->dir = y->esq;
    if (y->esq) y->esq->pai = x;

    y->esq = x;

    y->pai = x->pai;
    x->pai = y;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

Vertice* rotacaoDireita(Vertice *y) {
    Vertice *x = y->esq;
    y->esq = x->dir;
    if (x->dir) x->dir->pai = y;

    x->dir = y;

    x->pai = y->pai;
    y->pai = x;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

// Inserção com referência ao pai
Vertice* inserir(Vertice *raiz, int chave) {
    if (raiz == NULL) {
        Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
        novo->chave = chave;
        novo->esq = novo->dir = novo->pai = NULL;
        novo->altura = 0;
        return novo;
    }

    if (chave < raiz->chave) {
        Vertice *filho = inserir(raiz->esq, chave);
        raiz->esq = filho;
        filho->pai = raiz;
    } else if (chave > raiz->chave) {
        Vertice *filho = inserir(raiz->dir, chave);
        raiz->dir = filho;
        filho->pai = raiz;
    } else {
        return raiz; // chave duplicada
    }

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));
    int fb = fatorBalanceamento(raiz);

    // Casos de rotação
    if (fb < -1 && chave < raiz->esq->chave)
        return rotacaoDireita(raiz); // Caso 3

    if (fb > 1 && chave > raiz->dir->chave)
        return rotacaoEsquerda(raiz); // Caso 1

    if (fb < -1 && chave > raiz->esq->chave) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        raiz->esq->pai = raiz;
        return rotacaoDireita(raiz); // Caso 4
    }

    if (fb > 1 && chave < raiz->dir->chave) {
        raiz->dir = rotacaoDireita(raiz->dir);
        raiz->dir->pai = raiz;
        return rotacaoEsquerda(raiz); // Caso 2
    }

    return raiz;
}

// Impressão em ordem crescente com pai
void imprimir(Vertice *raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esq);
        printf("%d ", raiz->chave);
        imprimir(raiz->dir);
    }
}


int main() {
    int valores[] = {21, 26, 30, 9, 4, 14, 28, 18, 15, 10, 2, 3, 7};
    int n = sizeof(valores) / sizeof(valores[0]);

    Vertice *raiz = NULL;
    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
        raiz->pai = NULL; // garantir que raiz continue sendo raiz após rotações
    }

    imprimir(raiz);

    return 0;
}
