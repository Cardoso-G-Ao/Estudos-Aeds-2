#include <stdio.h>   // printf, fprintf, perror: entrada e saída
#include <stdlib.h>  // realloc, free, exit: memória dinâmica e encerramento

#define NUM_BUCKETS 5  // quantidade de baldes (faixas) em que os valores serão divididos

// Balde dinâmico: um "array que cresce sozinho"
typedef struct {
    int *data;     // ponteiro para os elementos guardados neste balde
    int size;      // quantos elementos o balde tem agora
    int capacity;  // quantos elementos cabem antes de precisar crescer
} Bucket;

// Adiciona um valor ao final do balde
void bucketPush(Bucket *b, int value) {
    if (b->size == b->capacity) {  // o balde está cheio?
        // se a capacidade é 0 (balde novo), começa com 4; senão, dobra a capacidade
        b->capacity = (b->capacity == 0) ? 4 : b->capacity * 2;
        // realloc aumenta o bloco de memória (e funciona com data == NULL no primeiro uso)
        b->data = (int *)realloc(b->data, b->capacity * sizeof(int));
        if (b->data == NULL) {  // realloc devolve NULL se faltar memória
            fprintf(stderr, "Erro de alocação de memória\n");  // avisa o erro
            exit(1);                                           // encerra o programa
        }
    }
    b->data[b->size] = value;  // grava o valor na primeira posição livre
    b->size++;                 // agora o balde tem um elemento a mais
}

// Insertion Sort: ordena um array pequeno (usado dentro de cada balde)
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {   // começa no 2º elemento; o 1º já é uma parte ordenada
        int key = arr[i];           // guarda o elemento atual (a "carta" a inserir)
        int j = i - 1;              // começa a olhar o elemento imediatamente à esquerda
        while (j >= 0 && arr[j] > key) {  // enquanto houver elemento maior que a chave...
            arr[j + 1] = arr[j];          // ...empurra esse elemento uma posição para a direita
            j--;                          // e olha o próximo à esquerda
        }
        arr[j + 1] = key;           // coloca a chave no espaço aberto (posição correta)
    }
}

// Bucket Sort para inteiros (aceita qualquer intervalo, inclusive negativos)
void bucketSort(int arr[], int n) {
    if (n <= 1) return;  // 0 ou 1 elemento já está ordenado: nada a fazer

    // --- Passo 1: descobrir o menor e o maior valor ---
    int min = arr[0], max = arr[0];       // começa assumindo que o 1º elemento é ambos
    for (int i = 1; i < n; i++) {         // percorre o restante do array
        if (arr[i] < min) min = arr[i];   // achou um valor menor: atualiza o mínimo
        if (arr[i] > max) max = arr[i];   // achou um valor maior: atualiza o máximo
    }
    if (min == max) return;  // todos os valores são iguais: já está ordenado

    // --- Passo 2: preparar os baldes ---
    Bucket buckets[NUM_BUCKETS] = {0};  // cria os baldes, todos zerados (data = NULL, size = 0, capacity = 0)
    long long range = (long long)max - min + 1;  // tamanho do intervalo de valores (long long evita overflow)

    // --- Passo 3: distribuir cada elemento no balde da sua faixa ---
    for (int i = 0; i < n; i++) {  // para cada elemento do array
        // (valor - min) varia de 0 até range - 1; multiplicar por NUM_BUCKETS e dividir
        // por range converte isso em um índice de balde entre 0 e NUM_BUCKETS - 1
        int idx = (int)(((long long)arr[i] - min) * NUM_BUCKETS / range);
        bucketPush(&buckets[idx], arr[i]);  // coloca o valor no balde calculado
    }

    // --- Passo 4: ordenar cada balde e juntar tudo de volta no array ---
    int pos = 0;                           // próxima posição livre do array original
    for (int b = 0; b < NUM_BUCKETS; b++) {  // percorre os baldes do primeiro ao último
        // ordena só os elementos deste balde (poucos, então o Insertion Sort resolve bem)
        insertionSort(buckets[b].data, buckets[b].size);
        for (int i = 0; i < buckets[b].size; i++) {  // para cada elemento já ordenado do balde
            arr[pos] = buckets[b].data[i];           // copia para o array original
            pos++;                                   // avança a posição de escrita
        }
        free(buckets[b].data);  // libera a memória do balde (free(NULL) é seguro para baldes vazios)
    }
    // Como os baldes representam faixas em ordem crescente, ao despejá-los em sequência
    // o array inteiro fica ordenado.
}

// Imprime um título e depois todos os elementos do array
void printArray(const char *titulo, int arr[], int n) {
    printf("%s\n", titulo);          // escreve o título em uma linha
    for (int i = 0; i < n; i++) {    // percorre o array
        printf("%d ", arr[i]);       // imprime cada número seguido de espaço
    }
    printf("\n");                    // quebra de linha no final
}

int main() {
    int arr[] = {78, 17, 39, 26, 72, 94, 21, 12, 23, 68};  // array de exemplo
    int n = sizeof(arr) / sizeof(arr[0]);  // número de elementos = tamanho total / tamanho de um elemento

    printArray("Array original:", arr, n);  // mostra o array antes de ordenar
    bucketSort(arr, n);                     // ordena com Bucket Sort
    printArray("Array ordenado:", arr, n);  // mostra o array depois de ordenar

    return 0;  // 0 indica que o programa terminou sem erros
}
