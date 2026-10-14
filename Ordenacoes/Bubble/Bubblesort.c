#include <stdio.h>  // printf: entrada e saída

// Bubble Sort com a otimização "parar se nenhuma troca aconteceu".
// Conta comparações e trocas para você comparar com os outros algoritmos.
void bubbleSort(int arr[], int n) {
    int comparacoes = 0, trocas = 0;  // contadores (só para estudo)

    for (int i = 0; i < n - 1; i++) {      // cada passada faz o maior elemento restante "subir" até o fim
        int trocou = 0;                    // marca se esta passada fez alguma troca

        for (int j = 0; j < n - 1 - i; j++) {  // compara pares vizinhos; os últimos i já estão no lugar
            comparacoes++;                     // mais uma comparação
            if (arr[j] > arr[j + 1]) {         // o par está fora de ordem?
                int temp = arr[j];             // guarda o elemento da esquerda
                arr[j] = arr[j + 1];           // o menor vai para a esquerda
                arr[j + 1] = temp;             // o maior vai para a direita
                trocas++;                      // mais uma troca
                trocou = 1;                    // anota que houve troca nesta passada
            }
        }

        if (!trocou) break;  // passada sem trocas: o array já está ordenado, podemos parar
    }

    printf("Comparações: %d | Trocas: %d\n", comparacoes, trocas);
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
    int arr[] = {5, 1, 4, 2, 8};            // array de exemplo
    int n = sizeof(arr) / sizeof(arr[0]);   // número de elementos = tamanho total / tamanho de um elemento

    printArray("Array original:", arr, n);  // mostra o array antes de ordenar
    bubbleSort(arr, n);                     // ordena com Bubble Sort
    printArray("Array ordenado:", arr, n);  // mostra o array depois de ordenar

    int ordenado[] = {1, 2, 3, 4, 5};       // caso favorável: já está ordenado
    printf("\nArray já ordenado:\n");
    bubbleSort(ordenado, 5);                // só uma passada, sem trocas

    return 0;  // 0 indica que o programa terminou sem erros
}