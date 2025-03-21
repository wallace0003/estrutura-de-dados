#include <stdio.h>
#include <stdlib.h>


typedef struct{
    struct Celula *anterior;
    int valor;
    struct Celula *proximo
} Celula;

typedef struct{
    int qtd;
    Celula *topo;
} Pilha;

Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula));
    nova->anterior = NULL;
    nova->proximo = NULL;
    nova->valor = valor;
    return nova;
}

Pilha *criar_pilha(){
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->qtd = 0;
    pilha->topo = NULL;
    return pilha;
}

void push(Pilha *pilha, int valor){
    Celula *nova = criar_celula(valor);
    if(pilha->qtd > 0){
        pilha->topo->proximo = nova;
        nova->anterior = pilha->topo;
    }
    pilha->topo = nova;
    pilha->qtd++;
}

int pop(Pilha *pilha){
    if(pilha->qtd == 0){
        return 0;
    }
    Celula *liberar = pilha->topo;
    if(pilha->topo->anterior == NULL){
        pilha->topo = NULL;
    } else  {
        Celula *anterior = pilha->topo->anterior;
        anterior->proximo = NULL;
        pilha->topo = anterior;
    }
    free(liberar);

}


void mostrar(Pilha *pilha){
    Celula *atual = pilha->topo;
    printf("Topo ->");
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
    printf("<- Brase");
}

int main(){
    Pilha *pilha = criar_pilha();
    for(int i = 0; i<10; i++){
        push(pilha, i);
        mostrar(pilha);
    }
    for(int i = 0; i<10; i++){
        pop(pilha);
        mostrar(pilha);
    }
    return 0;
}



