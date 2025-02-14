#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
    int valor;
    struct Celula *proximo; 
} Celula;

typedef struct{
    Celula *primeiro;
    int qtd;
}LDE;

Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula));
    nova->proximo = NULL;
    nova->valor = valor;
    return nova;
}

LDE *criar_lista(){
    LDE *lista = malloc(sizeof(LDE));
    lista->primeiro = NULL;
    lista->qtd = 0;
    return lista;
}

void inserir(LDE *lista, int valor){
    Celula *nova = criar_celula(valor);

    if(lista->primeiro == NULL){
        lista->primeiro = nova;
        lista->qtd++;
        return;
    }

    Celula *anterior =NULL;
    Celula *atual = lista->primeiro;

    while(atual != NULL && atual->valor < nova->valor){
        anterior = atual;
        atual = atual->proximo;
    }

    if(anterior == NULL && atual != NULL){
        nova->proximo = atual;
        lista->primeiro = nova;
        lista->qtd++;
        return;
    }

    if(anterior != NULL && atual == NULL){
        anterior->proximo = nova;
        lista->qtd++;
        return;
    }

    if(anterior != NULL && atual != NULL){
        anterior->proximo = nova;
        nova->proximo = atual;
        lista->qtd++;
        return;
    }
}

void mostrar(LDE *lista){
    Celula *atual = lista->primeiro;
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

int main(){
    LDE *lista = criar_lista();
    for(int i = 10; i > 0; i--){
        inserir(lista,i);
        mostrar(lista);
    }

    return 0;
}