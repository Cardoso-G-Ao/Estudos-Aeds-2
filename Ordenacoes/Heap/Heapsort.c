#include <stdio.h>  // printf: entrada e saída

// Troca os valores de duas variáveis (recebe os endereços delas)
void swap(int *a, int *b) {
    int temp = *a;  // guarda o valor apontado por a
    *a = *b;        // coloca em a o valor de b
    *b = temp;      // coloca em b o valor guardado de a
}

// "Peneira" o nó i para baixo (sift down), considerando que o heap tem n elementos.
// Pré-condição: as duas subárvores de i já são max-heaps.
void heapify(int arr[], int n, int i) {
    int largest = i;        // assume que o maior entre pai e filhos é o próprio pai
    int left = 2 * i + 1;   // posição do filho esquerdo
    int right = 2 * i + 2;  // posição do filho direito

    if (left < n && arr[left] > arr[largest]) {  // o filho esquerdo existe e é maior?
        largest = left;                          // então ele é o maior até agora
    }
    if (right < n && arr[right] > arr[largest]) {  // o filho direito existe e é maior que o vencedor?
        largest = right;                           // então ele é o maior
    }

    if (largest != i) {                // algum filho é maior que o pai?
        swap(&arr[i], &arr[largest]);  // troca o pai com o maior filho
        heapify(arr, n, largest);      // continua descendo, pois o valor trocado pode violar a regra abaixo
    }
    // se largest == i, o pai já é maior que os filhos: o heap está correto aqui
}

// Ordena o array com Heap Sort
void heapSort(int arr[], int n) {
    // Fase 1: construir o max-heap
    // n / 2 - 1 é o último nó que tem filhos; os nós depois dele são folhas
    for (int i = n / 2 - 1; i >= 0; i--) {  // do último pai até a raiz
        heapify(arr, n, i);                 // garante que o nó i respeite a regra do max-heap
    }

    // Fase 2: extrair o maior elemento repetidamente
    for (int end = n - 1; end > 0; end--) {  // end = última posição do heap atual
        swap(&arr[0], &arr[end]);            // leva o maior (raiz) para a posição final
        heapify(arr, end, 0);                // reorganiza o heap, agora com end elementos (o maior ficou de fora)
    }
}

// Imprime um título e depois todos os elementos do array
void printArray(const char *titulo, int arr[], int n) {
    printf("%s\n", titulo);        // escreve o título em uma linha
    for (int i = 0; i < n; i++) {  // percorre o array
        printf("%d ", arr[i]);     // imprime cada número seguido de espaço
    }
    printf("\n");                  // quebra de linha no final
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};  // array de exemplo
    int n = sizeof(arr) / sizeof(arr[0]);    // número de elementos = tamanho total / tamanho de um elemento

    printArray("Array original:", arr, n);   // mostra o array antes de ordenar
    heapSort(arr, n);                        // ordena com Heap Sort
    printArray("Array ordenado:", arr, n);   // mostra o array depois de ordenar

    return 0;  // 0 indica que o programa terminou sem erros
}