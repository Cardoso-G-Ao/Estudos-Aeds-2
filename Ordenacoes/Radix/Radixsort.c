#include <stdio.h>
#include <stdlib.h>
// Função auxiliar para encontrar o maior número do array
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
// Counting Sort modificado para ordenar de acordo com a casa decimal (exp)
void countingSortForRadix(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = {0}; // O array de contagem sempre terá tamanho 10 (dígitos 0 a 9)
    // Conta a ocorrência dos dígitos na casa decimal atual
    // (arr[i] / exp) % 10 isola o dígito. Ex: (123 / 10) % 10 = 2
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }
    // Acumula a contagem para definir as posições
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    // Constrói o array de saída (de trás para frente garante a estabilidade)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    // Copia os números (agora ordenados pela casa decimal atual) de volta
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    free(output);
}
// Função principal do Radix Sort
void radixSort(int arr[], int n) {
    if (n <= 1) return;
    int max = getMax(arr, n);
    // Chama o Counting Sort para cada dígito
    // O 'exp' representa a potência de 10: 1 (unidade), 10 (dezena), 100 (centena)...
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp);
    }
}
int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Array original: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    radixSort(arr, n);
    printf("Array ordenado: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}