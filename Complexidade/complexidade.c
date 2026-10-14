#include <stdio.h>  // printf: entrada e saída

// Em vez de medir segundos, contamos QUANTAS OPERAÇÕES cada trecho de código faz
// quando o tamanho da entrada (n) cresce. Assim vemos a "forma" do crescimento.

// O(1): o custo não depende de n
long constante(int n) {
    (void)n;                                    // n existe só para manter a mesma forma das outras funções
    return 1;                                   // uma única operação, qualquer que seja n
}

// O(log n): o problema cai pela metade a cada volta
long logaritmico(int n) {
    long ops = 0;
    for (int i = n; i > 1; i /= 2) ops++;       // divide por 2 até chegar a 1
    return ops;
}

// O(n): um laço simples
long linear(int n) {
    long ops = 0;
    for (int i = 0; i < n; i++) ops++;          // uma operação por elemento
    return ops;
}

// O(n log n): um laço de n voltas que, dentro, faz um trabalho logarítmico
long nLogN(int n) {
    long ops = 0;
    for (int i = 0; i < n; i++)
        for (int j = n; j > 1; j /= 2) ops++;
    return ops;
}

// O(n²): dois laços aninhados, ambos de n voltas
long quadratico(int n) {
    long ops = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) ops++;
    return ops;
}

// O(2^n): cada chamada gera duas novas chamadas (Fibonacci recursivo); conta as chamadas
long exponencial(int n) {
    if (n < 2) return 1;                        // caso base: uma chamada
    return 1 + exponencial(n - 1) + exponencial(n - 2);  // esta chamada + as duas filhas
}

int main() {
    int tamanhos[] = {10, 100, 1000};           // tamanhos de entrada que vamos testar
    int total = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("%8s %6s %8s %8s %10s %12s\n", "n", "O(1)", "O(logn)", "O(n)", "O(nlogn)", "O(n^2)");
    for (int i = 0; i < total; i++) {
        int n = tamanhos[i];
        printf("%8d %6ld %8ld %8ld %10ld %12ld\n",
               n, constante(n), logaritmico(n), linear(n), nLogN(n), quadratico(n));
    }

    printf("\nO(2^n): número de chamadas do Fibonacci recursivo\n");
    for (int n = 10; n <= 30; n += 5) {         // cresce muito rápido: n = 30 já passa de 2 milhões
        printf("n = %2d -> %ld chamadas\n", n, exponencial(n));
    }

    return 0;  // 0 indica que o programa terminou sem erros
}