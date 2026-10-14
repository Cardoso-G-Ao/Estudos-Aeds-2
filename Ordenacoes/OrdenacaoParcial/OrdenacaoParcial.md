# Guia Completo: Ordenação Parcial

A **Ordenação Parcial** resolve um problema diferente da ordenação completa: em vez de ordenar todos os $n$ elementos, queremos apenas os **$k$ menores** (ou maiores), **já em ordem**, onde $k$ costuma ser muito menor que $n$.

Se você só precisa do "top 10" de um milhão de itens, ordenar tudo em $\mathcal{O}(n \log n)$ é um desperdício. Com a ordenação parcial é possível fazer bem menos trabalho.

---

## 🏅 Como Funciona? (A Analogia do Pódio)

Imagine uma maratona com milhares de corredores e você só quer saber **quem ficou no pódio** (os 3 primeiros). Você não precisa descobrir quem foi o 2.847º colocado:
1. Você acha o primeiro colocado e o separa.
2. Acha o segundo colocado entre os que sobraram e o separa.
3. Acha o terceiro. **Pronto.** O resto da multidão pode ficar bagunçado.

**Definição do problema:** dado um array de $n$ elementos e um inteiro $k$ ($1 \le k \le n$), reorganizar o array de modo que as $k$ primeiras posições contenham os $k$ menores elementos **em ordem crescente**. As outras $n - k$ posições ficam em qualquer ordem.

Existem quatro métodos clássicos, cada um adaptado de um algoritmo de ordenação completa.

### 1. Seleção parcial

Repete só **$k$ vezes** o passo do Selection Sort: procura o menor entre os que sobraram e o coloca na próxima posição.

### 2. Inserção parcial

Mantém os $k$ primeiros elementos **ordenados**. Cada elemento seguinte é comparado com o **maior** dos $k$: se for maior, é descartado; se for menor, **entra** na posição certa e o maior dos $k$ sai.

### 3. Heapsort parcial

Constrói um **min-heap** com todos os elementos (custo $\mathcal{O}(n)$) e **retira o mínimo $k$ vezes** (custo $\mathcal{O}(\log n)$ cada).

### 4. Quicksort parcial

Particiona como o Quick Sort, mas **só continua nos lados que contêm posições entre as $k$ primeiras**. O lado direito do pivô é ignorado quando o pivô já está na posição $k - 1$ ou além.

### Exemplo passo a passo

Array inicial: `[38, 27, 43, 3, 9, 82, 10]`, com $k = 3$.

**Seleção parcial**

| Passo | Procura o menor em | Menor | Array |
|---|---|---|---|
| 1 | posições 0 a 6 | 3 | `[3, 27, 43, 38, 9, 82, 10]` |
| 2 | posições 1 a 6 | 9 | `[3, 9, 43, 38, 27, 82, 10]` |
| 3 | posições 2 a 6 | 10 | `[3, 9, 10, 38, 27, 82, 43]` |

Resultado: os 3 menores, `[3, 9, 10]`, estão nas 3 primeiras posições. O restante não foi ordenado.

**Inserção parcial** (k = 3): os três primeiros, `[38, 27, 43]`, são ordenados para `[27, 38, 43]`. Depois: `3 < 43` entra e sai o 43 (`[3, 27, 38]`); `9 < 38` entra e sai o 38 (`[3, 9, 27]`); `82` é descartado; `10 < 27` entra e sai o 27 (`[3, 9, 10]`).

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)

| Método | Tempo | Observação |
|---|---|---|
| Seleção parcial | $\mathcal{O}(n \cdot k)$ | Sempre, independentemente da entrada |
| Inserção parcial | $\mathcal{O}(n \cdot k)$ no pior caso; $\mathcal{O}(n)$ no melhor | Quase nada precisa entrar quando os $k$ primeiros já são os menores |
| Heapsort parcial | $\mathcal{O}(n + k \log n)$ | Construir o heap custa $\mathcal{O}(n)$ |
| Quicksort parcial | $\mathcal{O}(n + k \log k)$ no caso médio | $\mathcal{O}(n^2)$ no pior caso, como o Quick Sort |

> **Detalhe importante:** quando $k = n$, a ordenação parcial vira ordenação completa, e métodos como o Seleção parcial voltam a custar $\mathcal{O}(n^2)$. A vantagem aparece quando $k \ll n$.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(1)$ para seleção, inserção e heap parciais (in-place). O Quicksort parcial usa a pilha de recursão, $\mathcal{O}(\log n)$ em média.

### 3. Estabilidade
*   **É Estável?** Não, em geral. As trocas à distância (seleção, heap, partição) podem inverter a ordem de elementos iguais. A inserção parcial pode ser feita de forma estável.

### 4. Qual método escolher?

| Situação | Método indicado |
|---|---|
| $k$ muito pequeno (poucas unidades) | Seleção parcial ou Inserção parcial: simples e rápidos |
| $k$ médio ou grande | Heapsort parcial ou Quicksort parcial |
| Dados chegando em fluxo, guardando só os $k$ melhores | Variação com heap de tamanho $k$ (o "top-k") |
| Melhor desempenho médio na prática | Quicksort parcial |

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Evita trabalho desnecessário:** só ordena o que foi pedido.
*   **Muito mais rápido que ordenar tudo** quando $k \ll n$.
*   **Reaproveita ideias conhecidas:** cada método é uma adaptação de um algoritmo clássico.

**Desvantagens:**
*   **O resto do array fica sem ordem:** só as $k$ primeiras posições são garantidas.
*   **Perde a vantagem quando $k$ se aproxima de $n$.**
*   **Cada método tem um ponto fraco:** o Quicksort parcial pode degradar; o Seleção parcial cresce com $n \cdot k$.

---

## 💻 Exemplo Clássico em C

O arquivo `ordenacaoparcial.c` traz os quatro métodos, com um comentário em cada linha e um `main` que compara os resultados. Abaixo, o mais simples, a seleção parcial:

```c
void selecaoParcial(int arr[], int n, int k) {
    for (int i = 0; i < k; i++) {          // só as k primeiras posições
        int menor = i;
        for (int j = i + 1; j < n; j++) {  // procura o menor entre os que sobraram
            if (arr[j] < arr[menor]) menor = j;
        }
        int t = arr[i]; arr[i] = arr[menor]; arr[menor] = t;
    }
}
```

**Pontos de atenção no código:**
*   O laço externo vai até `k`, e não até `n`: essa é a única diferença para o Selection Sort completo.
*   No **Heapsort parcial**, cada retirada do mínimo manda o menor para o fim do heap; no final, o array é invertido para deixar os $k$ menores no início.
*   No **Quicksort parcial**, o lado direito do pivô só é visitado se `p < k - 1`.

---

## 🎯 Quando devo usar a Ordenação Parcial?

*   **Rankings e "top-k":** os 10 mais vendidos, as 5 menores distâncias, as 100 maiores pontuações.
*   **Buscar os $k$ vizinhos mais próximos** em algoritmos de classificação.
*   **Mostrar só a primeira página de resultados** ordenados de uma grande lista.
*   **Quando $k$ é muito menor que $n$.**

Quando você precisa de todos os elementos ordenados, use um algoritmo de ordenação completa.

---

## 📝 Resumo Rápido

*   **Ideia central:** ordenar só os $k$ menores elementos, deixando o resto sem ordem.
*   **Métodos:** seleção parcial, inserção parcial, heapsort parcial e quicksort parcial.
*   **Tempo:** $\mathcal{O}(n \cdot k)$ (seleção e inserção), $\mathcal{O}(n + k \log n)$ (heap), $\mathcal{O}(n + k \log k)$ médio (quick).
*   **Espaço:** $\mathcal{O}(1)$, in-place (o quick usa a pilha de recursão).
*   **Estável:** em geral, não.
*   **Destaque:** muito mais barato que ordenar tudo quando $k \ll n$.