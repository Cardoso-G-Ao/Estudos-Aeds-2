# Guia Completo: Fundamentos de Complexidade de Algoritmos

A **análise de complexidade** responde a uma pergunta central da computação: **o quanto um algoritmo "custa" quando o tamanho do problema cresce?** Com ela, é possível comparar algoritmos, prever o desempenho e escolher a melhor solução sem precisar rodar o programa em todas as situações.

Todos os guias deste repositório usam esse vocabulário ($\mathcal{O}(n)$, $\mathcal{O}(n \log n)$, melhor caso, pior caso, in-place...). Este guia explica de onde ele vem.

---

## 🧭 Por Que Analisar Algoritmos?

Medir o tempo em segundos parece natural, mas **não serve para comparar algoritmos**, porque o resultado depende de:
*   do **computador** (processador, memória);
*   da **linguagem** e do compilador;
*   dos **dados** usados no teste;
*   do que mais estiver rodando na máquina.

A análise de complexidade ignora tudo isso e olha para o que realmente importa: **como a quantidade de operações cresce em função do tamanho da entrada**, que chamamos de $n$.

**Analogia:** dois amigos vão de carro a cidades diferentes. Comparar "quem demorou mais" não diz qual rota é melhor. Já comparar **como o tempo cresce quando a distância dobra** diz muito mais.

---

## 📏 O Que Se Mede?

*   **Tamanho da entrada ($n$):** número de elementos do array, de células da lista, de dígitos do número...
*   **Complexidade de tempo:** quantas operações básicas (comparações, atribuições, somas) o algoritmo executa.
*   **Complexidade de espaço:** quanta memória **extra** o algoritmo usa, além da entrada.

### Os três cenários

| Cenário | Pergunta | Exemplo (pesquisa sequencial) |
|---|---|---|
| **Melhor caso** | Qual a entrada mais favorável? | O valor está na 1ª posição: 1 comparação |
| **Pior caso** | Qual a entrada mais desfavorável? | O valor está no fim ou não existe: $n$ comparações |
| **Caso médio** | Quanto custa, em média, sobre todas as entradas? | Cerca de $n/2$ comparações |

O **pior caso** é o mais usado, porque é uma **garantia**: o algoritmo nunca fará pior que isso.

---

## 🔢 Contando Operações

Vamos contar as operações de um trecho simples:

```c
int soma = 0;                    // 1 atribuição
for (int i = 0; i < n; i++) {    // o laço roda n vezes
    soma = soma + arr[i];        // 1 soma e 1 atribuição por volta
}
return soma;                     // 1 retorno
```

O custo total é algo como $T(n) = 2n + 3$. Para $n = 1000$, são 2003 operações. Mas os detalhes ("2" e "+ 3") importam pouco. **O que importa é que o custo cresce de forma linear com $n$.** É isso que a notação assintótica captura.

---

## 🔤 Notação Assintótica

Ela descreve o crescimento do custo quando $n$ fica **muito grande**.

| Notação | Lê-se | Significado | Analogia |
|---|---|---|---|
| $\mathcal{O}(f(n))$ | "O grande" | **Limite superior**: o custo não passa de $f(n)$ (a menos de uma constante) | "No máximo isso" |
| $\Omega(f(n))$ | "Ômega" | **Limite inferior**: o custo não é menor que $f(n)$ | "No mínimo isso" |
| $\Theta(f(n))$ | "Theta" | **Limite justo**: o custo cresce exatamente como $f(n)$ | "Isso, nem mais nem menos" |

**Definição formal de $\mathcal{O}$:** $T(n) = \mathcal{O}(f(n))$ se existem constantes positivas $c$ e $n_0$ tais que $T(n) \le c \cdot f(n)$ para todo $n \ge n_0$.

**Exemplo:** $T(n) = 2n + 3$ é $\mathcal{O}(n)$, pois $2n + 3 \le 3n$ para todo $n \ge 3$ (basta tomar $c = 3$ e $n_0 = 3$).

> **Cuidado:** $\mathcal{O}$ não é o mesmo que "pior caso". O pior caso é um **cenário**; $\mathcal{O}$ é uma **forma de descrever** o crescimento. Dá para dizer "o melhor caso é $\mathcal{O}(n)$" ou "o pior caso é $\Theta(n^2)$".

---

## 📐 Regras para Simplificar

1.  **Descarte as constantes:** $5n$ vira $n$; $n/2$ vira $n$.
2.  **Fique só com o termo dominante:** $n^2 + 100n + 7$ vira $n^2$, pois para $n$ grande o $n^2$ domina tudo.
3.  **Regra da soma:** dois trechos em sequência custam o **maior** dos dois. $\mathcal{O}(n) + \mathcal{O}(n^2) = \mathcal{O}(n^2)$.
4.  **Regra do produto:** laços **aninhados** multiplicam. Um laço de $n$ voltas contendo outro de $n$ voltas custa $\mathcal{O}(n \cdot n) = \mathcal{O}(n^2)$.
5.  **Laços que dividem por 2** custam $\mathcal{O}(\log n)$: o problema pela metade a cada volta.

---

## 📈 As Classes de Complexidade Mais Comuns

Da mais rápida para a mais lenta:

| Classe | Nome | Exemplo típico |
|---|---|---|
| $\mathcal{O}(1)$ | Constante | Acessar `arr[i]`; empilhar em uma pilha |
| $\mathcal{O}(\log n)$ | Logarítmica | Pesquisa binária |
| $\mathcal{O}(n)$ | Linear | Pesquisa sequencial; percorrer uma lista |
| $\mathcal{O}(n \log n)$ | Linearítmica | Merge Sort, Heap Sort, Quick Sort (caso médio) |
| $\mathcal{O}(n^2)$ | Quadrática | Bubble, Insertion e Selection Sort |
| $\mathcal{O}(n^3)$ | Cúbica | Multiplicação de matrizes (método simples) |
| $\mathcal{O}(2^n)$ | Exponencial | Fibonacci recursivo simples; testar todos os subconjuntos |
| $\mathcal{O}(n!)$ | Fatorial | Testar todas as permutações |

### O quanto isso importa na prática?

Considere um computador que faz **1 bilhão (10⁹) de operações por segundo**:

| $n$ | $\log n$ | $n$ | $n \log n$ | $n^2$ | $2^n$ |
|---|---|---|---|---|---|
| 10 | 3 ns | 10 ns | 33 ns | 100 ns | 1 µs |
| 50 | 6 ns | 50 ns | 282 ns | 2,5 µs | **13 dias** |
| 1.000 | 10 ns | 1 µs | 10 µs | 1 ms | cerca de $10^{284}$ anos |
| 1.000.000 | 20 ns | 1 ms | 20 ms | **17 minutos** | impossível |

Um algoritmo quadrático com 1 milhão de elementos leva quase 17 minutos; um $\mathcal{O}(n \log n)$ leva 20 milissegundos. **A escolha do algoritmo vale mais que um computador mais rápido.**

---

## 🔍 Como Analisar um Código: 5 Exemplos

**1. Sequência simples → $\mathcal{O}(1)$**
```c
int x = arr[0] + arr[1];
```

**2. Um laço → $\mathcal{O}(n)$**
```c
for (int i = 0; i < n; i++) { /* trabalho constante */ }
```

**3. Dois laços aninhados → $\mathcal{O}(n^2)$**
```c
for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) { /* trabalho constante */ }
```

**4. Laço que divide por 2 → $\mathcal{O}(\log n)$**
```c
for (int i = n; i > 1; i /= 2) { /* trabalho constante */ }
```

**5. Laço com laço logarítmico dentro → $\mathcal{O}(n \log n)$**
```c
for (int i = 0; i < n; i++)
    for (int j = n; j > 1; j /= 2) { /* trabalho constante */ }
```

> **Armadilha comum:** dois laços aninhados nem sempre dão $n^2$. Se o laço interno vai de `i` até `n` (como no Insertion Sort), o total é $\frac{n(n-1)}{2}$, que **continua sendo $\mathcal{O}(n^2)$**. Já se o interno roda um número fixo de vezes (por exemplo, 3), o total é $\mathcal{O}(n)$.

---

## 🔁 Complexidade de Algoritmos Recursivos

Em recursão, o custo é descrito por uma **recorrência**.

| Algoritmo | Recorrência | Solução |
|---|---|---|
| Pesquisa binária | $T(n) = T(n/2) + \mathcal{O}(1)$ | $\mathcal{O}(\log n)$ |
| Merge Sort | $T(n) = 2T(n/2) + \mathcal{O}(n)$ | $\mathcal{O}(n \log n)$ |
| Fatorial recursivo | $T(n) = T(n-1) + \mathcal{O}(1)$ | $\mathcal{O}(n)$ |
| Fibonacci recursivo | $T(n) = T(n-1) + T(n-2) + \mathcal{O}(1)$ | $\mathcal{O}(2^n)$ |

**Intuição para o Merge Sort:** o array é dividido ao meio $\log_2 n$ vezes (a altura da recursão), e em cada nível todos os $n$ elementos são intercalados uma vez. Logo, $n \cdot \log n$.

---

## 🧠 Complexidade de Espaço

Conta a memória **extra**, sem contar a própria entrada.

| Algoritmo | Espaço extra | Por quê |
|---|---|---|
| Bubble, Insertion, Selection, Heap Sort | $\mathcal{O}(1)$ | Trabalham *in-place* |
| Quick Sort | $\mathcal{O}(\log n)$ | Pilha de recursão |
| Merge Sort | $\mathcal{O}(n)$ | Array auxiliar |
| Counting Sort | $\mathcal{O}(n + k)$ | Array de contagem e de saída |

Muitas vezes há um **compromisso entre tempo e espaço**: o Counting Sort é rápido justamente porque gasta memória extra.

---

## 🗂️ Complexidade dos Algoritmos Deste Repositório

| Algoritmo | Melhor caso | Caso médio | Pior caso | Espaço |
|---|---|---|---|---|
| Bubble Sort | $\mathcal{O}(n)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ |
| Insertion Sort | $\mathcal{O}(n)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ |
| Selection Sort | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(1)$ |
| Merge Sort | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ |
| Quick Sort | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(\log n)$ |
| Heap Sort | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ |
| Counting Sort | $\mathcal{O}(n + k)$ | $\mathcal{O}(n + k)$ | $\mathcal{O}(n + k)$ | $\mathcal{O}(n + k)$ |
| Pesquisa sequencial | $\mathcal{O}(1)$ | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ |
| Pesquisa binária | $\mathcal{O}(1)$ | $\mathcal{O}(\log n)$ | $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ |

---

## 💻 Exemplo em C

O arquivo `complexidade.c` **conta as operações** de funções com complexidade $\mathcal{O}(1)$, $\mathcal{O}(\log n)$, $\mathcal{O}(n)$, $\mathcal{O}(n \log n)$, $\mathcal{O}(n^2)$ e $\mathcal{O}(2^n)$, para vários valores de $n$. A saída mostra o crescimento acontecendo:

```
       n   O(1)  O(logn)     O(n)   O(nlogn)       O(n^2)
      10      1        3       10         30          100
     100      1        6      100        600        10000
    1000      1        9     1000       9000      1000000
```

Repare como, ao multiplicar $n$ por 10, o custo $\mathcal{O}(n)$ também é multiplicado por 10, o $\mathcal{O}(n^2)$ por 100 e o $\mathcal{O}(\log n)$ só ganha 3 operações.

---

## 🎯 Para Que Serve Isso na Prática?

*   **Escolher o algoritmo certo** para o tamanho dos seus dados (por exemplo, evitar $\mathcal{O}(n^2)$ em milhões de itens).
*   **Prever o desempenho** antes de escrever o código.
*   **Comparar soluções** de forma justa, sem depender da máquina.
*   **Entender os guias** deste repositório, que usam a mesma linguagem.

---

## 📝 Resumo Rápido

*   **Complexidade** mede como o custo (tempo ou memória) cresce com o tamanho da entrada $n$.
*   **Cenários:** melhor, pior (a garantia) e médio.
*   **Notações:** $\mathcal{O}$ (limite superior), $\Omega$ (limite inferior), $\Theta$ (limite justo).
*   **Simplificar:** descartar constantes, ficar com o termo dominante, somar em sequência, multiplicar em laços aninhados.
*   **Classes:** $1 < \log n < n < n \log n < n^2 < n^3 < 2^n < n!$.
*   **Destaque:** a escolha do algoritmo importa mais que a velocidade do computador.