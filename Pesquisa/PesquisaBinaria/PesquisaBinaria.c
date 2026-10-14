#include <stdio.h>  // printf: entrada e saída

// Pesquisa binária (iterativa). O array PRECISA estar ordenado em ordem crescente.
// A cada passo, olha o elemento do meio e descarta metade do intervalo.
int pesquisaBinaria(int arr[], int n, int x, int *passos) {
    int esq = 0, dir = n - 1;          // intervalo de busca: do primeiro ao último
    *passos = 0;                       // zera o contador de passos
    while (esq <= dir) {               // enquanto ainda existir intervalo
        (*passos)++;                   // mais um passo
        int meio = esq + (dir - esq) / 2;  // posição do meio (evita estouro de int que (esq + dir) / 2 poderia causar)
        if (arr[meio] == x) {          // achou no meio?
            return meio;
        } else if (arr[meio] < x) {    // x é maior: descarta a metade esquerda
            esq = meio + 1;
        } else {                       // x é menor: descarta a metade direita
            dir = meio - 1;
        }
    }
    return -1;                         // o intervalo acabou: x não existe
}

// Versão recursiva: faz a mesma coisa, chamando a si mesma na metade que sobrou
int pesquisaBinariaRec(int arr[], int esq, int dir, int x) {
    if (esq > dir) return -1;          // caso base: intervalo vazio
    int meio = esq + (dir - esq) / 2;
    if (arr[meio] == x) return meio;
    if (arr[meio] < x) return pesquisaBinariaRec(arr, meio + 1, dir, x);  // procura na metade direita
    return pesquisaBinariaRec(arr, esq, meio - 1, x);                     // procura na metade esquerda
}

int main() {
    int arr[] = {3, 9, 10, 27, 38, 43, 82};   // array ORDENADO de exemplo
    int n = sizeof(arr) / sizeof(arr[0]);
    int passos;

    int pos = pesquisaBinaria(arr, n, 43, &passos);   // caso encontrado
    printf("Valor 43: posição %d em %d passos\n", pos, passos);

    pos = pesquisaBinaria(arr, n, 12, &passos);       // caso não encontrado
    printf("Valor 12: posição %d em %d passos\n", pos, passos);

    pos = pesquisaBinariaRec(arr, 0, n - 1, 82);      // versão recursiva
    printf("Valor 82 (recursiva): posição %d\n", pos);

    return 0;  // 0 indica que o programa terminou sem erros
}