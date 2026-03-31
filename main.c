/* =========================================================
   Aluno: Lucas Figueredo de Oliveira
   Turma: 5º Periodo "A"
   RA: 2410469
   ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* =========================================================
   FUNÇÕES AUXILIARES
   ========================================================= */

// Imprime o array (usado para mostrar antes/depois)
void printArray(const int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Copia um array para outro (garante comparação justa)
void copyArray(const int *src, int *dst, int n) {
    memcpy(dst, src, n * sizeof(int));
}

// Preenche com números aleatórios
void fillRandom(int *arr, int n, int maxVal) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % maxVal;
}

// Array já ordenado crescente
void fillSortedAsc(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

// Array ordenado decrescente
void fillSortedDesc(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = n - 1 - i;
}

// Array quase ordenado (simula caso real)
void fillAlmostSorted(int *arr, int n) {
    fillSortedAsc(arr, n);
    if (n >= 10) {
        for (int k = 0; k < 5; k++) {
            int i = rand() % n;
            int j = rand() % n;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
}

// Escolhe o tipo de preenchimento
void fillByType(int *arr, int n, int type) {
    switch (type) {
        case 1: fillRandom(arr, n, 100000); break;
        case 2: fillSortedAsc(arr, n); break;
        case 3: fillSortedDesc(arr, n); break;
        case 4: fillAlmostSorted(arr, n); break;
        default: fillRandom(arr, n, 100000);
    }
}

/* =========================================================
   ALGORITMOS DE ORDENAÇÃO
   ========================================================= */

// Bubble Sort (O(n²))
void bubbleSort(int *arr, int n) {
    int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

// Selection Sort (O(n²))
void selectionSort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;

        if (minIdx != i) {
            int tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }
}

// Insertion Sort (O(n²))
void insertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
static int partitionQS(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partitionQS(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
static void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    if (!L || !R) {
        printf("Erro de memória no Merge Sort.\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Shell Sort
void shellSort(int *arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

/* =========================================================
   MEDIÇÃO DE TEMPO
   ========================================================= */

double runAndTime(void (*sortFn)(int*, int), int *arr, int n) {
    clock_t start = clock();
    sortFn(arr, n);
    clock_t end = clock();
    return ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
}

double runAndTimeQuick(int *arr, int n) {
    clock_t start = clock();
    quickSort(arr, 0, n - 1);
    clock_t end = clock();
    return ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
}

double runAndTimeMerge(int *arr, int n) {
    clock_t start = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();
    return ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
}

/* =========================================================
   EXECUÇÃO DOS TESTES
   ========================================================= */

void runSingleAlgorithm(int alg, int type, int n) {
    int *base = malloc(n * sizeof(int));
    int *work = malloc(n * sizeof(int));

    fillByType(base, n, type);
    copyArray(base, work, n);

    double ms = 0.0;

    switch (alg) {
        case 1: ms = runAndTime(bubbleSort, work, n); printf("Bubble Sort"); break;
        case 2: ms = runAndTime(selectionSort, work, n); printf("Selection Sort"); break;
        case 3: ms = runAndTime(insertionSort, work, n); printf("Insertion Sort"); break;
        case 4: ms = runAndTimeQuick(work, n); printf("Quick Sort"); break;
        case 5: ms = runAndTimeMerge(work, n); printf("Merge Sort"); break;
        case 6: ms = runAndTime(shellSort, work, n); printf("Shell Sort"); break;
    }

    printf(" | n=%d | tempo=%.3f ms\n", n, ms);

    free(base);
    free(work);
}

void runAllAlgorithms(int type, int n) {
    int *base = malloc(n * sizeof(int));
    int *work = malloc(n * sizeof(int));

    fillByType(base, n, type);

    printf("\n--- Comparação (mesmo array base) | n=%d ---\n", n);

    copyArray(base, work, n);
    printf("Bubble Sort   : %.3f ms\n", runAndTime(bubbleSort, work, n));

    copyArray(base, work, n);
    printf("Selection Sort: %.3f ms\n", runAndTime(selectionSort, work, n));

    copyArray(base, work, n);
    printf("Insertion Sort: %.3f ms\n", runAndTime(insertionSort, work, n));

    copyArray(base, work, n);
    printf("Quick Sort    : %.3f ms\n", runAndTimeQuick(work, n));

    copyArray(base, work, n);
    printf("Merge Sort    : %.3f ms\n", runAndTimeMerge(work, n));

    copyArray(base, work, n);
    printf("Shell Sort    : %.3f ms\n", runAndTime(shellSort, work, n));

    free(base);
    free(work);
}

/* =========================================================
   MENU PRINCIPAL
   ========================================================= */

int main() {
    srand((unsigned)time(NULL));

    int alg, type, n;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1) Bubble Sort\n");
        printf("2) Selection Sort\n");
        printf("3) Insertion Sort\n");
        printf("4) Quick Sort\n");
        printf("5) Merge Sort\n");
        printf("6) Shell Sort\n");
        printf("7) Rodar TODOS (comparacao)\n");
        printf("0) Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &alg) != 1) break;
        if (alg == 0) break;

        printf("\nTipo de array:\n");
        printf("1) Aleatorio\n");
        printf("2) Ordenado crescente\n");
        printf("3) Ordenado decrescente\n");
        printf("4) Quase ordenado\n");
        printf("Escolha: ");

        if (scanf("%d", &type) != 1) break;

        printf("Digite o tamanho do array: ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            printf("Tamanho invalido.\n");
            continue;
        }

        if (alg >= 1 && alg <= 6)
            runSingleAlgorithm(alg, type, n);
        else if (alg == 7)
            runAllAlgorithms(type, n);
        else
            printf("Opcao invalida.\n");
    }

    return 0;
}