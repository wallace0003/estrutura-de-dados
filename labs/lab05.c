#include <stdio.h>

#define LEN 100

typedef struct {
char data[LEN];
int head;
int tail;
int qtde;
} Queue;

void enqueue(Queue *queue, char caracter) {
if(queue->qtde == LEN){
    return;
}
queue->data[queue->tail++]= caracter;
queue->qtde++;
}

int dequeue(Queue *queue) {
if(queue->qtde == 0){
    return 0;
}

char valor = queue->data[queue->head++];
queue->qtde--;
return valor;
}

void show(Queue *queue) {
for(int i = queue->head; i < queue->tail; i++){
    printf("%c", queue->data[i]);
}
}

void start_queue(Queue *queue) {
queue->head = 0;
queue->tail = 0;
queue->qtde = 0;
}

int main(void) {
char s[LEN];
fgets(s, sizeof(s), stdin);
Queue queue;
Queue queue2;
int verifica = 0;

start_queue(&queue);
start_queue(&queue2);

for (int i = 0; s[i] != '\0'; i++) {
    enqueue(&queue, s[i]);
}

for (int i = queue.head; i < queue.tail; i++){

    if(s[i] == '('){
        enqueue(&queue2, s[i]);
    }

    else if(s[i] == ')'){
        if(dequeue(&queue2) == 0){
            verifica = 1;
            break;
        };
    }
    dequeue(&queue);
    show(&queue);
    
}

if(verifica == 1 || queue2.qtde != 0){
    printf("incorreto\n");
}else{
    printf("correto\n");
}


return 0;
}
