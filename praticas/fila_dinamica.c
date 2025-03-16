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

Fila *criar_fila(){
    Fila *fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtde = 0;
    return fila;
}

void enfileirar(Fila *fila, int valor){
    Celula *nova = criar_celula(valor);
    if(fila->qtde == 0){
        fila->head = nova;
    } else {
        fila->tail->proximo = nova;
        nova->anterior = fila->tail;
    }
    fila->tail = nova;
    fila->qtde++;
}

void mostra_fila(Fila *fila, int inversa){
    if(inversa){
        Celula *atual = fila->head;
        printf("HEAD -> ");
        while(atual != NULL){
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }
        printf("<- TAIL");
    } else{
        Celula *atual = fila->tail;
        printf("TAIL -> ");
        while(atual != NULL){
            printf("%d ", atual->valor);
            atual = atual->anterior;
        }
        printf("<- HEAD");
    }
    printf("\n");
}

int desenfileirar(Fila *fila){
    if(fila->qtde == 0){
        return -1;
    }

    Celula *liberar = fila->head;
    int valor = fila->head->valor;
    if(fila->qtde == 1){
        fila->head = NULL;
        fila->tail = NULL;
    } else{
        fila->head->proximo->anterior = NULL;
        fila->head = fila->head->proximo;
    }
    fila->qtde--;
    free(liberar);
    return valor;
}

int main(){
    Fila *fila = criar_fila();
    int n_clientes = 0;
    
    printf("Digite quantos clientes você deseja atender: ");
    scanf("%d", &n_clientes);
    printf("\n");
    printf("Número de clientes: %d ", n_clientes);
    printf("\n");

    for(int i = 1; i <= n_clientes; i++){
        enfileirar(fila, i);
        mostra_fila(fila, 1);
        mostra_fila(fila, 0);
    }

    for(int i = 1; i <= n_clientes; i++){
        printf("Cliente atendido: %d \n", desenfileirar(fila));
        mostra_fila(fila, 1);
    }

    
    return 0;
}
