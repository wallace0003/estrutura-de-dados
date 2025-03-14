#include <stdio.h>
#include <stdlib.h>


typedef struct Celula{
    struct Celula *anterior;
    struct Celula *proximo;
    int valor;
} Celula;

typedef struct{
    int qtde;
    Celula *head;
    Celula *tail;
} Fila;

Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula));
    nova->anterior = NULL;
    nova->proximo = NULL;
    nova->valor = valor;
    return nova;
}

void enfileirar(Fila *fila, int valor){
    Celula *nova = criar_celula(valor);
    if(fila->qtde == 0){
        fila->head = nova;
    } else{
        fila->tail->proximo = nova;
        nova->anterior = fila->tail;
    }
    fila->tail = nova;
    fila->qtde++;
}

void mostra_fila(Fila *fila, int inversa){
    if(inversa){
        Celula *atual = fila->head;
        printf("HEAD ->");
        while(atual != NULL){
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }
        printf("<- TAIL");
    } else{
        Celula *atual = fila->tail;
        printf("TAIL ->");
        while(atual != NULL){
            printf("%d ", atual->valor);
            atual = atual->anterior;
        }
        printf("<- HEAD");
    }
    printf("\n");
}

int main(){
    Fila *fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtde = 0;
    
    enfileirar(fila, 10);
    mostra_fila(fila, 0);
    enfileirar(fila, 20);
    mostra_fila(fila, 1);
    enfileirar(fila, 20);
    mostra_fila(fila, 0);
    enfileirar(fila, 1);
    mostra_fila(fila, 10);
    
    
    return 0;
}
