#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

void preencherDecrescente(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

void bubbleSort(int v[], int n, long *comparacoes, long *movimentacoes) {
    int aux;
    *comparacoes = 0;
    *movimentacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comparacoes)++;
            if (v[j] > v[j + 1]) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                (*movimentacoes) += 3;
            }
        }
    }
}

void selectionSort(int v[], int n, long *comparacoes, long *movimentacoes) {
    int min, aux;
    *comparacoes = 0;
    *movimentacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (min != i) {
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
            (*movimentacoes) += 3;
        }
    }
}

void testarAlgoritmos(int n) {
    int original[MAX], v[MAX];
    long comparacoes, movimentacoes;
    clock_t inicio, fim;
    double tempo;

    preencherDecrescente(original, n);

    for (int i = 0; i < n; i++) v[i] = original[i];

    inicio = clock();
    bubbleSort(v, n, &comparacoes, &movimentacoes);
    fim = clock();

    tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    printf("Bubble Sort | %5d | %8.2f ms | %10ld | %10ld\n",
           n, tempo, comparacoes, movimentacoes);

    for (int i = 0; i < n; i++) v[i] = original[i];

    inicio = clock();
    selectionSort(v, n, &comparacoes, &movimentacoes);
    fim = clock();

    tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
    printf("Selection   | %5d | %8.2f ms | %10ld | %10ld\n",
           n, tempo, comparacoes, movimentacoes);
}

int main() {
    printf("Algoritmo   | Tamanho | Tempo (ms) | Comparacoes | Movimentacoes\n");
    printf("---------------------------------------------------------------\n");

    testarAlgoritmos(100);
    testarAlgoritmos(1000);
    testarAlgoritmos(10000);

    return 0;
}
