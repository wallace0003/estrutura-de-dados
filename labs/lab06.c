#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
	int valor;
	struct Celula *proximo;
	struct Celula *anterior;
} Celula;

typedef struct {
	Celula *head;
	Celula *tail;
	int qtde;
} Queue;

Celula *cria_celula(int valor){
	Celula *celula = malloc(sizeof(Celula));
	celula->proximo = NULL;
	celula->anterior = NULL;
	celula->valor = valor;

	return celula;
}

Queue *cria_queue(){
	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->qtde = 0;

	return queue;
}

void enqueue(Queue *queue, int valor){
	Celula *nova = cria_celula(valor);
    if(queue->qtde == 0){
        queue->head = nova;
    } else {
        queue->tail->proximo = nova;
        nova->anterior = queue->tail;
    }
    queue->tail = nova;
    queue->qtde++;
}

int dequeue(Queue *queue){
    if(queue->qtde == 0){
        return -1;
    }

    Celula *liberar = queue->head;
    int valor = queue->head->valor;
    if(queue->qtde == 1){
        queue->head = NULL;
        queue->tail = NULL;
    } else{
        queue->head->proximo->anterior = NULL;
        queue->head = queue->head->proximo;
    }
    queue->qtde--;
    free(liberar);
    return valor;
}

void show(Queue *queue){
    Celula *atual = queue->tail;
    while(atual != NULL){
        printf("%d", atual->valor);
        atual = atual->anterior;
    }
    printf("\n");
}

void show_invertido(Queue *queue){
    Celula *atual = queue->head;
    while(atual != NULL){
        printf("%d", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

int main(void) {
	Queue *qnum1 = cria_queue();
	Queue *qnum2 = cria_queue();
	Queue *res = cria_queue();
    int soma = 0;
    int vai1 = 0;
    
	
	char num1[100];
	char num2[100];
	fgets(num1, sizeof(num1), stdin);
	fgets(num2, sizeof(num2), stdin);

	int i = 0;
	while(num1[i] != '\n'){		
		enqueue(qnum1, (int)(num1[i]) - 48);
		enqueue(qnum2, (int)(num2[i]) - 48);
		i++;
	}
    Celula *valor1 = qnum1->tail;
    Celula *valor2 = qnum2->tail;

    while(valor1 != NULL){
        soma = valor1->valor + valor2->valor + vai1;
        if(soma > 9){
            soma = soma - 10;
            vai1 = 1;
        } else {
            vai1 = 0;
        }
        enqueue(res, soma);
        valor1 = valor1->anterior;
        valor2 = valor2->anterior;
    }
    if(vai1){
        enqueue(res, vai1);
    }
    show(res);
}