#include <stdio.h>
#include <stdlib.h>
// Função responsável por intercalar (mesclar) dois sub-arrays ordenados
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Tamanho do sub-array esquerdo
    int n2 = right - mid;    // Tamanho do sub-array direito
    // Aloca memória para arrays temporários
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    // Copia os dados para os arrays temporários L e R
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    // Índices iniciais dos sub-arrays e do array principal
    int i = 0; // Índice de L
    int j = 0; // Índice de R
    int k = left; // Índice de arr
    // Mescla os arrays de volta no array original respeitando a ordem
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { // O sinal de <= garante a estabilidade do algoritmo
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    // Libera a memória alocada
    free(L);
    free(R);
}
// Função recursiva principal do Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Encontra o meio (escrito assim para evitar overflow em arrays gigantes)
        int mid = left + (right - left) / 2;

        // Ordena a primeira e a segunda metade recursivamente
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mescla as metades ordenadas
        merge(arr, left, mid, right);
    }
}
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // Chama o mergeSort passando o índice inicial (0) e o final (n-1)
    mergeSort(arr, 0, n - 1);

    printf("Array ordenado: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}