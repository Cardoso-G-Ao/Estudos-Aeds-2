# Guia Completo: Algoritmo Merge Sort (Ordenação por Intercalação)

O **Merge Sort** (ou Ordenação por Intercalação) é um algoritmo de ordenação baseado na estratégia **dividir para conquistar**. Ele divide o array ao meio repetidamente até sobrarem pedaços de um único elemento (que já estão ordenados por definição) e depois **intercala** (faz o *merge* de) esses pedaços, sempre produzindo listas ordenadas maiores.

Diferente dos algoritmos simples de $\mathcal{O}(n^2)$ (como Insertion Sort e Selection Sort), o Merge Sort garante $\mathcal{O}(n \log n)$ em **todos os casos**, o que o torna uma das escolhas mais confiáveis para grandes volumes de dados.

---

## 🧩 Como Funciona? (A Analogia das Duas Pilhas de Cartas)

Imagine que você tem duas pilhas de cartas, e cada uma **já está ordenada** com a menor carta por cima. Para juntá-las em uma única pilha ordenada, basta repetir:
1. Olhar a carta do topo de cada pilha.
2. Pegar a **menor** das duas e colocá-la na pilha final.
3. Repetir até uma das pilhas acabar, e então despejar o que sobrou da outra.

Esse processo (a **intercalação**) é rápido, porque você nunca precisa olhar além do topo de cada pilha. O Merge Sort apenas aplica essa ideia de forma recursiva:

1. **Dividir:** parte o array ao meio.
2. **Conquistar:** ordena cada metade recursivamente (um array de 0 ou 1 elemento já está ordenado).
3. **Combinar:** intercala as duas metades ordenadas em um único array ordenado.

### Exemplo passo a passo

Array inicial: `[38, 27, 43, 3, 9, 82, 10]`

**Fase 1: divisão**

```
                [38, 27, 43, 3, 9, 82, 10]
               /                          \
      [38, 27, 43, 3]                [9, 82, 10]
       /           \                  /        \
  [38, 27]      [43, 3]            [9]       [82, 10]
   /    \        /    \                       /     \
 [38]  [27]    [43]   [3]                  [82]    [10]
```

**Fase 2: intercalação** (de baixo para cima)

| Intercala | Resultado |
|---|---|
| `[38]` + `[27]` | `[27, 38]` |
| `[43]` + `[3]` | `[3, 43]` |
| `[82]` + `[10]` | `[10, 82]` |
| `[27, 38]` + `[3, 43]` | `[3, 27, 38, 43]` |
| `[9]` + `[10, 82]` | `[9, 10, 82]` |
| `[3, 27, 38, 43]` + `[9, 10, 82]` | `[3, 9, 10, 27, 38, 43, 82]` |

Resultado final: `[3, 9, 10, 27, 38, 43, 82]`

**Detalhe da última intercalação** (`[3, 27, 38, 43]` + `[9, 10, 82]`):

| Topo esquerdo | Topo direito | Menor | Saída até agora |
|---|---|---|---|
| 3 | 9 | 3 | `[3]` |
| 27 | 9 | 9 | `[3, 9]` |
| 27 | 10 | 10 | `[3, 9, 10]` |
| 27 | 82 | 27 | `[3, 9, 10, 27]` |
| 38 | 82 | 38 | `[3, 9, 10, 27, 38]` |
| 43 | 82 | 43 | `[3, 9, 10, 27, 38, 43]` |
| (acabou) | 82 | 82 | `[3, 9, 10, 27, 38, 43, 82]` |

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
*   **Melhor Caso:** $\mathcal{O}(n \log n)$
*   **Pior Caso:** $\mathcal{O}(n \log n)$
*   **Caso Médio:** $\mathcal{O}(n \log n)$
    *   O array é dividido ao meio $\log_2 n$ vezes (a **altura** da recursão), e em cada nível a intercalação percorre os $n$ elementos uma vez. Logo, o custo é $n \cdot \log n$, independentemente da disposição dos dados.

> **Detalhe importante:** a recorrência do algoritmo é $T(n) = 2T(n/2) + \mathcal{O}(n)$, cuja solução é $\mathcal{O}(n \log n)$. Para 1 milhão de elementos, são cerca de 20 níveis de recursão, contra um número da ordem de $10^{12}$ operações de um algoritmo $\mathcal{O}(n^2)$.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(n)$
    *   **Não é in-place** na versão clássica para arrays. A intercalação precisa de um array auxiliar do tamanho do trecho sendo combinado. Existem versões in-place, mas são bem mais complexas e lentas.
    *   Para **listas encadeadas**, a intercalação pode ser feita apenas religando ponteiros, e o espaço extra cai para $\mathcal{O}(\log n)$ (a pilha da recursão).

### 3. Estabilidade
*   **É Estável?** Sim.
    *   Na intercalação, quando os dois topos são **iguais**, o elemento da metade **esquerda** é escolhido primeiro (`<=` em vez de `<`). Assim, elementos iguais mantêm a ordem relativa original.

### 4. Baseado em Comparação?
*   **Sim.** E atinge o limite inferior teórico de $\Omega(n \log n)$ para algoritmos desse tipo, ou seja, é **assintoticamente ótimo** entre os algoritmos por comparação.

### 5. Adaptabilidade
*   **É Adaptável?** Não (na versão clássica).
    *   Ele sempre divide e intercala, mesmo que o array já esteja ordenado. Variações como o *Natural Merge Sort* e o **Timsort** aproveitam trechos já ordenados.

### 6. Algoritmo *Online*
*   **É Online?** Não.
    *   Precisa de todos os dados antes de começar a dividir.

---

## 📊 Comparação com Outros Algoritmos

| Característica | Insertion Sort | Selection Sort | **Merge Sort** |
|---|---|---|---|
| Melhor caso | $\mathcal{O}(n)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n \log n)$ |
| Pior caso | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | **$\mathcal{O}(n \log n)$** |
| Espaço extra | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ | $\mathcal{O}(n)$ |
| Estável | Sim | Não | **Sim** |
| Adaptável | Sim | Não | Não |
| Estratégia | Inserção | Seleção | Dividir para conquistar |

---

## 🔀 Variações

*   **Top-down (recursivo):** a versão clássica, apresentada neste guia.
*   **Bottom-up (iterativo):** começa intercalando pares de elementos, depois pares de pares, e assim por diante, sem recursão.
*   **Natural Merge Sort:** detecta trechos já ordenados (*runs*) e os intercala diretamente. É a ideia por trás do Timsort.
*   **Merge Sort em listas encadeadas:** muito eficiente, pois não precisa de acesso aleatório nem de array auxiliar.
*   **Merge Sort externo:** ordena arquivos maiores que a memória, intercalando blocos ordenados gravados em disco.

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Desempenho garantido:** $\mathcal{O}(n \log n)$ em qualquer caso, sem pior caso quadrático.
*   **Estável:** preserva a ordem de elementos iguais.
*   **Previsível:** o tempo varia pouco conforme a entrada.
*   **Ótimo para listas encadeadas e dados externos:** acessa os dados de forma sequencial.
*   **Paralelizável:** as duas metades podem ser ordenadas ao mesmo tempo.

**Desvantagens:**
*   **Usa memória extra:** $\mathcal{O}(n)$ para o array auxiliar (versão clássica).
*   **Mais lento em arrays pequenos:** o overhead da recursão e das cópias pesa. Por isso, implementações práticas trocam para Insertion Sort em pedaços pequenos.
*   **Não é adaptável:** não aproveita dados já ordenados (na versão clássica).
*   **Não é online.**

---

## 💻 Exemplo Clássico em C

```c
#include <stdlib.h>

// Intercala arr[l..m] e arr[m+1..r], que já estão ordenados
static void merge(int arr[], int tmp[], int l, int m, int r) {
    int i = l;       // início da metade esquerda
    int j = m + 1;   // início da metade direita
    int k = l;       // posição no array auxiliar

    while (i <= m && j <= r) {
        // "<=" garante a estabilidade: em empate, sai o da esquerda
        if (arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }

    // Despeja o que sobrou de qualquer uma das metades
    while (i <= m) tmp[k++] = arr[i++];
    while (j <= r) tmp[k++] = arr[j++];

    // Copia o trecho intercalado de volta para o array original
    for (k = l; k <= r; k++)
        arr[k] = tmp[k];
}

static void mergeSortRec(int arr[], int tmp[], int l, int r) {
    if (l >= r) return;              // 0 ou 1 elemento: já está ordenado

    int m = l + (r - l) / 2;         // evita overflow de (l + r) / 2
    mergeSortRec(arr, tmp, l, m);    // ordena a metade esquerda
    mergeSortRec(arr, tmp, m + 1, r);// ordena a metade direita
    merge(arr, tmp, l, m, r);        // intercala as duas
}

void mergeSort(int arr[], int n) {
    int *tmp = malloc(n * sizeof(int));  // um único array auxiliar
    mergeSortRec(arr, tmp, 0, n - 1);
    free(tmp);
}
```

**Pontos de atenção no código:**
*   O array auxiliar é alocado **uma única vez** e reaproveitado em todas as intercalações, evitando `malloc` dentro da recursão.
*   O caso base `l >= r` interrompe a recursão quando o trecho tem 0 ou 1 elemento.
*   `m = l + (r - l) / 2` é mais seguro do que `(l + r) / 2`, que pode estourar o limite de `int` com índices muito grandes.
*   O `<=` na comparação é o que mantém o algoritmo **estável**. Trocando por `<`, ele continua ordenando, mas perde a estabilidade.

---

## 🎯 Quando devo usar o Merge Sort?

*   **Quando é preciso garantia de desempenho:** sem risco de pior caso quadrático.
*   **Quando a estabilidade importa:** por exemplo, ordenar registros por mais de um critério em etapas.
*   **Listas encadeadas:** é considerado o melhor algoritmo de ordenação para esse tipo de estrutura.
*   **Dados maiores que a memória (ordenação externa):** blocos são ordenados e depois intercalados a partir do disco.
*   **Ordenação paralela ou distribuída:** a divisão em metades se encaixa naturalmente em vários processadores.

Na prática, bibliotecas padrão usam variações do Merge Sort. O `sort()` do **Python** e o `Arrays.sort()` para objetos no **Java** usam o **Timsort**, um híbrido de Merge Sort com Insertion Sort que aproveita trechos já ordenados. Evite a versão clássica quando a memória extra for um problema sério.

---

## 📝 Resumo Rápido

*   **Ideia central:** divida o array ao meio, ordene cada metade e intercale as metades ordenadas.
*   **Tempo:** $\mathcal{O}(n \log n)$ em todos os casos.
*   **Espaço:** $\mathcal{O}(n)$, **não** é in-place (versão clássica).
*   **Estável:** sim. **Adaptável:** não. **Online:** não.
*   **Estratégia:** dividir para conquistar.
*   **Destaque:** desempenho garantido e estabilidade, ideal para grandes volumes, listas encadeadas e ordenação externa.
