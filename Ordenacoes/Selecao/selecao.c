#include <stdio.h>
void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    // Move a fronteira do subarray não ordenado um por um
    for (i = 0; i < n - 1; i++) {
        // Encontra o menor elemento no array não ordenado
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Troca o menor elemento encontrado com o primeiro elemento
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}
