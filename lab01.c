#include <stdio.h>

#define LEN 10

typedef struct{
  int dados[LEN];
  int qtde;
} LES;

int is_empty(LES *les){
    return les -> qtde == 0;
}

int is_full(LES *les){
   return les -> qtde == LEN;
}

int get_index(LES *les, int value){
  int idx = 0;
  while(idx < les -> qtde && les -> dados[idx] < value){
    idx++;
  }
  return idx;
}

void move_left(LES *les, int idx){
  for (int n = idx; n < les -> qtde; n++){
    les -> dados[n] = les -> dados[n + 1];
  }
}

void insert(LES *les, int value){
  if (is_full(les)){
    return 0;
  }
  int idx = get_index(les, value);
  move_right(les, idx);
  les -> dados[idx] = value;
  les -> qtde++;
}

void delete(LES *les, int value){
    if (is_empty(les)){
        return;
    };

    int idx = get_index(les,value);
    move_left(les,idx);
    les -> dados[idx] = value;
    les -> qtde --;
    printf("Número apagado foi: %d", les -> dados[idx]);

}

void show(LES *les){
  for (int i = 0; i < les -> qtde; i++){
    printf("%d ", les -> dados[i]);
    printf("\n");
  }
}

int main() {
  LES les;
  les.qtde = 10;
  LES *p_les = &les;
  for(int num = 10; num <=0; num--){
    insert(p_les, num);
    show(p_les);
  }
  return 0;
}