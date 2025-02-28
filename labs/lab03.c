#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *anterior;
    struct no *proximo;
} No;

typedef struct lista_duplamente_encadeada {
    int quantidade;
    No *inicio;
} ListaDuplamenteEncadeada;

ListaDuplamenteEncadeada *criar_lista() {
    ListaDuplamenteEncadeada *lista = malloc(sizeof(ListaDuplamenteEncadeada));
    lista->inicio = NULL;
    lista->quantidade = 0;
    return lista;
}

No *criar_no(int valor) {
    No *novo_no = malloc(sizeof(No));
    novo_no->valor = valor;
    novo_no->anterior = NULL;
    novo_no->proximo = NULL;
    return novo_no;
}

void inserir_valor(ListaDuplamenteEncadeada *lista, int valor) {
    No *novo_no = criar_no(valor);
    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
    } else {
        No *atual = lista->inicio, *anterior = NULL;
        while (atual != NULL && atual->valor < valor) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (anterior == NULL) {
            novo_no->proximo = lista->inicio;
            lista->inicio->anterior = novo_no;
            lista->inicio = novo_no;
        } else {
            novo_no->proximo = atual;
            novo_no->anterior = anterior;
            anterior->proximo = novo_no;
            if (atual != NULL) {
                atual->anterior = novo_no;
            }
        }
    }
    lista->quantidade++;
}

void exibir_lista(ListaDuplamenteEncadeada *lista) {
    No *atual = lista->inicio;
    printf("Início -> ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("<- Final\n");
}

void exibir_lista_invertida(ListaDuplamenteEncadeada *lista) {
    if (lista->inicio == NULL) {
        printf("Final -> <- Início\n");
        return;
    }
    No *atual = lista->inicio;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    printf("Final -> ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
    printf("<- Início\n");
}

void remover_valor(ListaDuplamenteEncadeada *lista, int valor) {
    No *atual = lista->inicio;
    while (atual != NULL && atual->valor != valor) {
        atual = atual->proximo;
    }
    if (atual == NULL) return;
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        lista->inicio = atual->proximo;
    }
    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }
    free(atual);
    lista->quantidade--;
}

int main(void) {
    ListaDuplamenteEncadeada *lista = criar_lista();

    inserir_valor(lista, 10);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 5);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 20);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 15);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 5);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 15);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 20);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 10);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    for (int i = 1; i <= 10; i++) {
        inserir_valor(lista, i);
    }
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    for (int i = 1; i <= 10; i++) {
        remover_valor(lista, i);
    }
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    remover_valor(lista, 100);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    inserir_valor(lista, 10);
    inserir_valor(lista, 10);
    inserir_valor(lista, 10);
    exibir_lista(lista);
    exibir_lista_invertida(lista);

    return 0;
}
