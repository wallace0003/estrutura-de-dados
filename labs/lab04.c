#include <stdio.h>

int verificarSenha(int senha, int tentativa) {
    return (senha == tentativa);
}

void quebrarSenha(int senha) {
    int tentativa;
    int n = 0;
    for (tentativa = 0; tentativa <= 99999; tentativa++) {
        n++;
        if (verificarSenha(senha, tentativa)) {
            printf("Senha encontrada: %05d\n", tentativa);
            printf("Número de tentativas: %d \n", n);
            return;
        }
    }
    printf("Senha não encontrada.\n");
}

int main() {
    int senha;
    printf("Digite a senha de 5 dígitos para ser quebrada: ");
    scanf("%d", &senha);

    quebrarSenha(senha);

    return 0;
}