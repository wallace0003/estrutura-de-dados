#include <stdio.h>>
#include <stdlib.h>

typedef struct Celula{
    struct Celula *anterior;
    struct celula *proximo;
    int valor;
} Celula;

typedef struct{
    Celula *primeiro;
    int qtd;
} LDDE;

Celula *criar_celula(int valor){
    Celula *novo = malloc(sizeof(Celula));
    novo->anterior = NULL;
    novo->proximo = NULL;
    novo->valor = valor;
    return novo;
}

LDDE *criar_lista(){
    LDDE *lista = malloc(sizeof(LDDE));
    lista->primeiro = NULL;
    lista->qtd = 0;
    return lista;
}

void inserir(LDDE *lista,   int valor){
    Celula *novo = criar_celula(valor);
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;

    while(atual != NULL && atual->valor < novo->valor){
        anterior = atual;
        atual = atual->proximo;
    }
    if(anterior == NULL){//Inserir no início
        lista->primeiro = novo;
        if(atual != NULL){
            novo->proximo = atual;
            atual->anterior = novo;
        }
    }else if(atual == NULL){//Inserir no final
        anterior->proximo = novo;
        novo->anterior = anterior;
    }else{//Inserir no meio
        anterior->proximo = novo;
        novo->anterior = anterior;
        novo->proximo = atual;
        atual->anterior = novo;
    }
    lista->qtd++;
}


void mostrar(LDDE *lista){
    Celula *atual = lista->primeiro;
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void main(){
    LDDE *lista = criar_lista();
    inserir(lista, 12);
    mostrar(lista);
    inserir(lista, 8);
    mostrar(lista);
    inserir(lista, 18);
    mostrar(lista);
    inserir(lista, 15);
    mostrar(lista);
}

