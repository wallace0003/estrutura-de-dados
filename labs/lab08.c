#include <stdio.h>
#include <stdlib.h>

#define LEN 10

typedef struct {
    int A[LEN];
    int n; 
} Heap;


int pai(int i) {
    return (i - 1) / 2;
}

int filho_esq(int i) {
    return 2 * i + 1;
}

int filho_dir(int i) {
    return 2 * i + 2;
}


void peneirar(Heap *H, int i) {
    int esq = filho_esq(i);
    int dir = filho_dir(i);
    int maior = i;

    if (esq < H->n && H->A[esq] > H->A[maior])
        maior = esq;

    if (dir < H->n && H->A[dir] > H->A[maior])
        maior = dir;

    if (maior != i) {
        int temp = H->A[i];
        H->A[i] = H->A[maior];
        H->A[maior] = temp;

        peneirar(H, maior);
    }
}


void construir_heap(Heap *H) {
    for (int i = H->n / 2 - 1; i >= 0; i--) {
        peneirar(H, i);
    }
}


void inserir(Heap *H, int chave) {
    if (H->n >= LEN) {
        printf("Heap cheio!\n");
        return;
    }

    int i = H->n;
    H->A[i] = chave;
    H->n++;

    while (i > 0 && H->A[pai(i)] < H->A[i]) {
        int temp = H->A[i];
        H->A[i] = H->A[pai(i)];
        H->A[pai(i)] = temp;
        i = pai(i);
    }
}


int remover(Heap *H) {
    if (H->n <= 0) {
        printf("Heap vazio!\n");
        return -1;
    }

    int max = H->A[0];
    H->A[0] = H->A[H->n - 1];
    H->n--;
    peneirar(H, 0);

    return max;
}


void mostrar(Heap *H) {
    for (int i = 0; i < H->n; i++) {
        printf("%d ", H->A[i]);
    }
    printf("\n");
}


int main() {
    Heap *h = malloc(sizeof(Heap));
    int valor;
    h->n = 0;
    for (int i = 0; i < LEN; i++) {
        scanf("%d", &valor);
        inserir(h, valor);
        mostrar(h);
    }
    for (int i = 0; i < LEN; i++) {
        remover(h);
        mostrar(h);
    }

    return 0;
}
