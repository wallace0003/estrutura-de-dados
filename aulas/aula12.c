#include <stdio.h>
#include <stdlib.h>

#define V 6 // número de vértices

// Função que transforma 'a', 'b', ... em 0, 1, ...
int get_index(char x) {
    return x - 'a';
}

// Inicia a matriz com 0
void inicia_arestas(int arestas[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            arestas[i][j] = 0;
        }
    }
}

// Cria aresta direcionada de v -> u
void cria_aresta(int arestas[V][V], int v, int u) {
    arestas[v][u] = 1;
}

// Mostra a matriz de adjacência
void mostra_arestas(int arestas[V][V]) {
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", arestas[i][j]);
        }
        printf("\n");
    }
}

// Mostra os adjacentes de um vértice
void mostra_adjacentes(int arestas[V][V], char vertice) {
    int idx = get_index(vertice);
    printf("Adjacentes de %c: ", vertice);
    for (int j = 0; j < V; j++) {
        if (arestas[idx][j] == 1) {
            printf("%c ", j + 'a');
        }
    }
    printf("\n");
}

// BFS para calcular distâncias a partir de um vértice
void mostra_distancias(int arestas[V][V], char origem) {
    int cor[V], dist[V];
    int fila[V], ini = 0, fim = 0;

    int s = get_index(origem);

    for (int i = 0; i < V; i++) {
        dist[i] = -1; // -1 representa infinito
        cor[i] = 0;   // 0 = branco (não visitado)
    }

    dist[s] = 0;
    cor[s] = 1; // cinza
    fila[fim++] = s;

    while (ini < fim) {
        int u = fila[ini++];

        for (int v = 0; v < V; v++) {
            if (arestas[u][v] && cor[v] == 0) {
                dist[v] = dist[u] + 1;
                cor[v] = 1;
                fila[fim++] = v;
            }
        }
        cor[u] = 2; // preto
    }

    printf("Distâncias a partir de %c:\n", origem);
    for (int i = 0; i < V; i++) {
        printf("%c: %d\n", i + 'a', dist[i]);
    }
}

int main() {
    int arestas[V][V];
    inicia_arestas(arestas);

    // Criação das arestas conforme exemplo do slide
    cria_aresta(arestas, get_index('a'), get_index('b'));
    cria_aresta(arestas, get_index('a'), get_index('d'));
    cria_aresta(arestas, get_index('a'), get_index('e'));
    cria_aresta(arestas, get_index('b'), get_index('a'));
    cria_aresta(arestas, get_index('b'), get_index('c'));
    cria_aresta(arestas, get_index('b'), get_index('f'));
    cria_aresta(arestas, get_index('c'), get_index('b'));
    cria_aresta(arestas, get_index('d'), get_index('a'));
    cria_aresta(arestas, get_index('e'), get_index('a'));
    cria_aresta(arestas, get_index('e'), get_index('f'));
    cria_aresta(arestas, get_index('f'), get_index('b'));
    cria_aresta(arestas, get_index('f'), get_index('e'));

    // Mostrar matriz de adjacência
    mostra_arestas(arestas);

    // Mostrar vizinhos
    mostra_adjacentes(arestas, 'a');
    mostra_adjacentes(arestas, 'b');
    mostra_adjacentes(arestas, 'f');

    // Mostrar distâncias a partir de um vértice
    mostra_distancias(arestas, 'a');

    return 0;
}