#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11

typedef struct Celula{
  int valor;
  struct Celula* proximo;
}Celula;

typedef struct {
  Celula* inicio;
}Lista;

typedef struct {
  Lista* table[tam_hash];
} Hash;

Hash* start_hash(){
  Hash* hash = malloc(sizeof(Hash));
  for(int i = 0; i < tam_hash; i++){
    Lista* lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    hash->table[i] = lista;
  }
  return hash;
}

void inserir_hash(Hash* hash, int valor){
    Celula *novo = malloc(sizeof(Celula));
    novo->valor = valor;
    int chave = valor % tam_hash;

    if(hash->table[chave]->inicio == NULL){
        hash->table[chave]->inicio = novo;
        novo->proximo = NULL;
    } else {
        novo->proximo = hash->table[chave]->inicio;
        hash->table[chave]->inicio = novo;
    }
}

void remover_hash(Hash* hash, int valor){
  Celula *anterior = NULL;
  int chave = valor % tam_hash;
  Celula *atual = hash->table[chave]->inicio;

  while(atual != NULL){
    if(atual->valor == valor){
        if(atual == NULL){
            free(atual);
            break;
        } if(atual != NULL && anterior != NULL){
            anterior->proximo = atual->proximo;
            free(atual);
            break;
        } if(anterior == NULL){
            hash->table[chave]->inicio = atual->proximo;
            free(atual);
            break;
        }
    }
    anterior = atual;
    atual = atual->proximo;
  }

  
}

void imprimir(Hash* hash){
  printf("---------------------\n");
  for(int i = 0; i < tam_hash; i++){
    Celula* atual = hash->table[i]->inicio;
    printf("%d -> ", i);
    while(atual != NULL){
      printf("%d ", atual->valor);
      atual = atual->proximo;
    }
    printf("\n");
  }
  printf("---------------------\n");
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