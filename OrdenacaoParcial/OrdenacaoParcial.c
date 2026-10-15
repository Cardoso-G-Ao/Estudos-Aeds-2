#include <stdio.h>   // printf: entrada e saída
#include <string.h>  // memcpy: copiar arrays

// Ordenação parcial: colocar os k MENORES elementos, em ordem, nas k primeiras posições.
// Os outros n - k elementos ficam em qualquer ordem. Cada função faz isso de um jeito.

void trocar(int *a, int *b) {
    int t = *a;  // guarda o valor de a
    *a = *b;     // a recebe o valor de b
    *b = t;      // b recebe o valor guardado de a
}

// 1) Seleção parcial: repete só k vezes o passo do Selection Sort. Custo: O(n·k)
void selecaoParcial(int arr[], int n, int k) {
    for (int i = 0; i < k; i++) {          // só as k primeiras posições
        int menor = i;                     // assume que o menor está na posição i
        for (int j = i + 1; j < n; j++) {  // procura o menor entre os que sobraram
            if (arr[j] < arr[menor]) {
                menor = j;                 // achou um menor
            }
        }
        trocar(&arr[i], &arr[menor]);      // coloca o menor na posição i
    }
}

// 2) Inserção parcial: mantém os k primeiros ordenados e só aceita quem for menor que o maior deles.
//    Custo: O(n·k) no pior caso e O(n) quando quase nada entra.
void insercaoParcial(int arr[], int n, int k) {
    for (int i = 1; i < k; i++) {                // ordena os k primeiros com Insertion Sort
        int chave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];                 // empurra o maior para a direita
            j--;
        }
        arr[j + 1] = chave;
    }
    for (int i = k; i < n; i++) {                // examina cada elemento restante
        if (arr[i] < arr[k - 1]) {               // é menor que o maior dos k? então ele entra
            int chave = arr[i];
            arr[i] = arr[k - 1];                 // o maior dos k sai e vai para a posição i (não se perde)
            int j = k - 2;
            while (j >= 0 && arr[j] > chave) {   // insere a chave na posição certa entre os k
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = chave;
        }
    }
}

// Peneira o nó i num MIN-heap de tamanho n (o pai é sempre menor que os filhos)
void peneirarMin(int arr[], int n, int i) {
    int menor = i, esq = 2 * i + 1, dir = 2 * i + 2;
    if (esq < n && arr[esq] < arr[menor]) menor = esq;  // filho esquerdo menor?
    if (dir < n && arr[dir] < arr[menor]) menor = dir;  // filho direito menor?
    if (menor != i) {
        trocar(&arr[i], &arr[menor]);                   // desce o nó
        peneirarMin(arr, n, menor);                     // continua descendo
    }
}

// 3) Heapsort parcial: monta um min-heap (O(n)) e retira o mínimo k vezes (O(log n) cada).
//    Custo: O(n + k·log n)
void heapParcial(int arr[], int n, int k) {
    for (int i = n / 2 - 1; i >= 0; i--) {  // constrói o min-heap
        peneirarMin(arr, n, i);
    }
    for (int i = 0; i < k; i++) {           // retira o menor k vezes
        trocar(&arr[0], &arr[n - 1 - i]);   // manda o menor (raiz) para o fim do heap
        peneirarMin(arr, n - 1 - i, 0);     // reorganiza o heap, agora menor
    }
    for (int i = 0, j = n - 1; i < j; i++, j--) {  // inverte o array: os k menores vão para o início, em ordem crescente
        trocar(&arr[i], &arr[j]);
    }
}

// Particiona arr[low..high] com o último elemento como pivô (Lomuto); devolve a posição final do pivô
int particionar(int arr[], int low, int high) {
    int pivo = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 4) Quicksort parcial: como o Quick Sort, mas só desce nos lados que ainda contêm posições menores que k.
//    Ao final, as k primeiras posições já estão corretas e em ordem.
//    Custo médio: O(n + k·log k)
void quickParcial(int arr[], int low, int high, int k) {
    if (low < high) {
        int p = particionar(arr, low, high);    // o pivô fica na posição final p
        quickParcial(arr, low, p - 1, k);       // o lado esquerdo sempre interessa
        if (p < k - 1) {                        // o lado direito só interessa se ainda faltam posições entre as k primeiras
            quickParcial(arr, p + 1, high, k);
        }
    }
}

// Imprime os k primeiros elementos do array
void imprimirK(const char *titulo, int arr[], int k) {
    printf("%s ", titulo);
    for (int i = 0; i < k; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int original[] = {38, 27, 43, 3, 9, 82, 10};   // array de exemplo
    int n = sizeof(original) / sizeof(original[0]);
    int k = 3;                                     // queremos os 3 menores, em ordem
    int copia[sizeof(original) / sizeof(original[0])];

    printf("Os %d menores de %d elementos:\n", k, n);

    memcpy(copia, original, sizeof(original));     // cada método recebe uma cópia do array original
    selecaoParcial(copia, n, k);
    imprimirK("Seleção parcial:", copia, k);

    memcpy(copia, original, sizeof(original));
    insercaoParcial(copia, n, k);
    imprimirK("Inserção parcial:", copia, k);

    memcpy(copia, original, sizeof(original));
    heapParcial(copia, n, k);
    imprimirK("Heapsort parcial:", copia, k);

    memcpy(copia, original, sizeof(original));
    quickParcial(copia, 0, n - 1, k);
    imprimirK("Quicksort parcial:", copia, k);

    return 0;
}