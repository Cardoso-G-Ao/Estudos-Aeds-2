#include <stdio.h>  // printf: entrada e saída

// Troca os valores de duas variáveis (recebe os endereços delas)
void swap(int *a, int *b) {
    int temp = *a;  // guarda o valor apontado por a
    *a = *b;        // coloca em a o valor de b
    *b = temp;      // coloca em b o valor guardado de a
}
// Particiona arr[low..high] usando o último elemento como pivô (método de Lomuto)
// Ao final: tudo à esquerda do pivô é <= pivô, tudo à direita é > pivô.
// Devolve a posição final do pivô.
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // escolhe o último elemento do trecho como pivô
    int i = low - 1;        // i marca o fim da "zona dos menores"; começa vazia (low - 1)

    for (int j = low; j < high; j++) {  // j percorre o trecho, sem incluir o pivô
        if (arr[j] <= pivot) {          // este elemento pertence à zona dos menores?
            i++;                        // aumenta a zona dos menores em uma posição
            swap(&arr[i], &arr[j]);     // traz o elemento para dentro dessa zona
        }
        // se arr[j] > pivot, não faz nada: ele fica na zona dos maiores
    }

    swap(&arr[i + 1], &arr[high]);  // coloca o pivô logo depois da zona dos menores
    return i + 1;                   // essa é a posição definitiva do pivô
}

// Ordena arr[low..high] (ambos os limites incluídos)
void quickSort(int arr[], int low, int high) {
    if (low < high) {                       // caso base: com 0 ou 1 elemento, já está ordenado
        int p = partition(arr, low, high);  // particiona e descobre onde o pivô ficou
        quickSort(arr, low, p - 1);         // ordena os menores (à esquerda do pivô)
        quickSort(arr, p + 1, high);        // ordena os maiores (à direita do pivô)
        // o pivô (posição p) já está no lugar certo, por isso não entra em nenhuma chamada
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
    quickSort(arr, 0, n - 1);                // ordena do primeiro ao último índice
    printArray("Array ordenado:", arr, n);   // mostra o array depois de ordenar

    return 0;  // 0 indica que o programa terminou sem erros
}