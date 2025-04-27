#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11
#define TAM 15 

typedef struct Celula{
    int valor;
    struct Celula* proximo;
  }Celula;
  
  typedef struct {
    Celula* inicio;
  }Lista;
  
  typedef struct {
    Lista* table[tam_hash];
  }Hash;

typedef struct LDDE {
    int valor;
    struct LDDE* ant;
    struct LDDE* prox;
} LDDE;

LDDE* inicializaLista() {
    return NULL;
}

int hash(int valor) {
    return valor % TAM;
}

LDDE* inserir(LDDE* lista, int valor) {
    LDDE* novo = (LDDE*)malloc(sizeof(LDDE));
    novo->valor = valor;
    novo->prox = lista;
    novo->ant = NULL;
    if (lista != NULL)
        lista->ant = novo;
    return novo;
}

LDDE* remover(LDDE* lista, int valor) {
    LDDE* atual = lista;
    while (atual != NULL && atual->valor != valor)
        atual = atual->prox;
    if (atual == NULL) {
        printf("Valor %d não encontrado.\n", valor);
        return lista;
    }

    if (atual->ant != NULL)
        atual->ant->prox = atual->prox;
    else
        lista = atual->prox;

    if (atual->prox != NULL)
        atual->prox->ant = atual->ant;

    free(atual);
    return lista;
}

void exibirTabela(LDDE* tabela[]) {
    for (int i = 0; i < TAM; i++) {
        printf("Hash[%d]: ", i);
        LDDE* atual = tabela[i];
        while (atual != NULL) {
            printf("%d <-> ", atual->valor);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

int main(void) {
    Hash* hash = start_hash();
    int valor;
    while(1){
      scanf("%d", &valor);
      if(valor == 0)
        break;
      inserir_hash(hash, valor);
    }
    imprimir(hash);
    while(1){
      scanf("%d", &valor);
      if(valor == 0)
        break;
      remover_hash(hash, valor);
    }
    imprimir(hash);
    return 0;
  }
