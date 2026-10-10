#include <stdlib.h>

void countingSort(int arr[], int n) {
    int i, max = arr[0];

    // Descobre o maior valor para definir o tamanho do array de contagem
    for (i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    int *count  = calloc(max + 1, sizeof(int)); // zerado
    int *output = malloc(n * sizeof(int));

    // Fase 1: conta quantas vezes cada valor aparece
    for (i = 0; i < n; i++)
        count[arr[i]]++;

    // Fase 2: soma acumulada (count[v] = quantos elementos são <= v)
    for (i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Fase 3: posiciona de trás para frente (garante a estabilidade)
    for (i = n - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    // Copia o resultado de volta
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(count);
    free(output);
}