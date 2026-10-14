#include <stdio.h>  // printf: entrada e saída

// Pesquisa sequencial: percorre o array do início ao fim até achar o valor x.
// Devolve a posição de x, ou -1 se ele não existir. Funciona em arrays DESORDENADOS.
int pesquisaSequencial(int arr[], int n, int x, int *comparacoes) {
    *comparacoes = 0;                  // zera o contador de comparações
    for (int i = 0; i < n; i++) {      // visita cada posição, uma por vez
        (*comparacoes)++;              // mais uma comparação
        if (arr[i] == x) {             // achou?
            return i;                  // devolve a posição e encerra
        }
    }
    return -1;                         // chegou ao fim sem achar
}

// Versão com sentinela: coloca x logo depois do último elemento, para não precisar testar "i < n" a cada volta.
// O array precisa ter UMA posição sobrando no final (tamanho n + 1).
int pesquisaComSentinela(int arr[], int n, int x) {
    int ultimo = arr[n];               // guarda o que estava na posição extra
    arr[n] = x;                        // a sentinela garante que o laço sempre termina
    int i = 0;
    while (arr[i] != x) {              // não precisa checar o limite do array
        i++;
    }
    arr[n] = ultimo;                   // devolve o valor original à posição extra
    return (i < n) ? i : -1;           // se parou na sentinela (i == n), o valor não existia
}

// Mostra o resultado de uma busca
void mostrar(int x, int pos, int comparacoes) {
    if (pos >= 0) {
        printf("Valor %d encontrado na posição %d (%d comparações)\n", x, pos, comparacoes);
    } else {
        printf("Valor %d não encontrado (%d comparações)\n", x, comparacoes);
    }
}

int main() {
    int arr[8] = {38, 27, 43, 3, 9, 82, 10};  // 7 elementos + 1 posição extra para a sentinela
    int n = 7;
    int comparacoes;

    int pos = pesquisaSequencial(arr, n, 9, &comparacoes);   // caso encontrado
    mostrar(9, pos, comparacoes);

    pos = pesquisaSequencial(arr, n, 50, &comparacoes);      // caso não encontrado: percorre tudo
    mostrar(50, pos, comparacoes);

    pos = pesquisaComSentinela(arr, n, 82);                  // versão com sentinela
    printf("Com sentinela: 82 está na posição %d\n", pos);

    return 0;  // 0 indica que o programa terminou sem erros
}