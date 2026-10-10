# Guia Completo: Algoritmo Quick Sort (Ordenação Rápida)

O **Quick Sort** (ou Ordenação Rápida) é um algoritmo de ordenação baseado na estratégia **dividir para conquistar**. Ele escolhe um elemento chamado **pivô**, reorganiza o array de modo que os elementos **menores** fiquem de um lado do pivô e os **maiores** do outro, e então repete o processo recursivamente em cada lado.

Criado por Tony Hoare em 1959, é um dos algoritmos mais usados no mundo. Apesar de ter pior caso $\mathcal{O}(n^2)$, na prática costuma ser **mais rápido que o Merge Sort e o Heap Sort**, porque trabalha *in-place*, acessa a memória de forma sequencial e tem constantes pequenas.

---

## 🎯 Como Funciona? (A Analogia da Fila por Altura com uma Pessoa de Referência)

Imagine que você precisa organizar uma multidão por altura, sem uma fita métrica:
1. Você escolhe **uma pessoa** como referência (o **pivô**).
2. Pede para todos os **mais baixos** irem para a esquerda dela e todos os **mais altos** para a direita.
3. Pronto: a pessoa-referência já está **exatamente no lugar definitivo** dela na fila final.
4. Agora você repete o processo separadamente com o grupo da esquerda e com o grupo da direita, cada um escolhendo seu próprio pivô.
5. Quando um grupo tiver 0 ou 1 pessoa, ele já está organizado.

Em termos de algoritmo, são três passos:

1. **Escolher o pivô:** neste guia, o último elemento do trecho.
2. **Particionar:** reorganizar o trecho para que todos os elementos $\le$ pivô fiquem à esquerda e todos os $>$ pivô à direita, deixando o pivô na posição final.
3. **Recursão:** aplicar o mesmo processo ao trecho à esquerda e ao trecho à direita do pivô.

A versão usada aqui é o **particionamento de Lomuto**: um índice `i` marca o fim da "zona dos menores" e um índice `j` percorre o trecho. Quando `arr[j] <= pivô`, o elemento é trocado para dentro da zona dos menores.

### Exemplo passo a passo

Array inicial: `[38, 27, 43, 3, 9, 82, 10]` (o pivô é sempre o último elemento do trecho)

**Primeiro particionamento** (trecho 0–6, pivô = 10)

| `j` | `arr[j]` | Comparação | Ação | Array |
|---|---|---|---|---|
| 0 | 38 | 38 > 10 | fica na zona dos maiores | `[38, 27, 43, 3, 9, 82, 10]` |
| 1 | 27 | 27 > 10 | fica na zona dos maiores | `[38, 27, 43, 3, 9, 82, 10]` |
| 2 | 43 | 43 > 10 | fica na zona dos maiores | `[38, 27, 43, 3, 9, 82, 10]` |
| 3 | 3 | 3 ≤ 10 | troca com a posição 0 | `[3, 27, 43, 38, 9, 82, 10]` |
| 4 | 9 | 9 ≤ 10 | troca com a posição 1 | `[3, 9, 43, 38, 27, 82, 10]` |
| 5 | 82 | 82 > 10 | fica na zona dos maiores | `[3, 9, 43, 38, 27, 82, 10]` |
| fim | | | pivô vai para a posição 2 | `[3, 9, 10, 38, 27, 82, 43]` |

O `10` já está na posição final. À esquerda ficou `[3, 9]` e à direita `[38, 27, 82, 43]`.

**Recursão**

| Trecho | Pivô | Resultado após particionar |
|---|---|---|
| `[3, 9]` | 9 | `[3, 9]` (o 9 fica no lugar; sobra `[3]`) |
| `[38, 27, 82, 43]` | 43 | `[38, 27, 43, 82]` (43 na posição 5) |
| `[38, 27]` | 27 | `[27, 38]` |

Resultado final: `[3, 9, 10, 27, 38, 43, 82]`

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
*   **Melhor Caso:** $\mathcal{O}(n \log n)$
    *   Ocorre quando o pivô divide o trecho em duas partes de tamanho parecido a cada particionamento.
*   **Caso Médio:** $\mathcal{O}(n \log n)$
    *   Mesmo com divisões desequilibradas (por exemplo, 90% / 10%), a profundidade da recursão continua logarítmica.
*   **Pior Caso:** $\mathcal{O}(n^2)$
    *   Ocorre quando o pivô é sempre o **menor ou o maior** elemento do trecho. Com o último elemento como pivô, isso acontece justamente em arrays **já ordenados** ou em ordem inversa: cada particionamento remove apenas um elemento.

> **Detalhe importante:** o pior caso depende da **estratégia de escolha do pivô**, não só dos dados. Com pivô aleatório ou "mediana de três", o pior caso fica extremamente improvável.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(\log n)$ em média
    *   É um algoritmo **in-place**: não precisa de array auxiliar. O único custo extra é a **pilha de recursão**.
    *   No pior caso, a pilha pode chegar a $\mathcal{O}(n)$. Uma otimização clássica é recorrer primeiro ao lado **menor** e tratar o maior com um laço, garantindo $\mathcal{O}(\log n)$ sempre.

### 3. Estabilidade
*   **É Estável?** Não.
    *   As trocas do particionamento "saltam" por cima de outros elementos e podem inverter a ordem de valores iguais.
    *   **Exemplo:** em `[4a, 4b, 2]`, com pivô `2`, o `4a` é trocado com o `2` ao final, gerando `[2, 4b, 4a]`. A ordem original dos dois `4` se perdeu.

### 4. Baseado em Comparação?
*   **Sim.** Atinge o limite inferior $\Omega(n \log n)$ no caso médio.

### 5. Adaptabilidade
*   **É Adaptável?** Não (com pivô fixo). Com pivô no fim, dados já ordenados são o **pior** caso, não o melhor.

### 6. Algoritmo *Online*
*   **É Online?** Não.
    *   Precisa de todos os elementos para particionar.

---

## 🔧 Estratégias de Escolha do Pivô

| Estratégia | Como funciona | Observação |
|---|---|---|
| **Último elemento** | `pivô = arr[high]` | Simples, mas péssimo para dados já ordenados. |
| **Primeiro elemento** | `pivô = arr[low]` | Mesmo problema do anterior. |
| **Aleatório** | sorteia uma posição do trecho e troca com `arr[high]` | Torna o pior caso muito improvável. |
| **Mediana de três** | mediana entre primeiro, meio e último | Boa proteção contra entradas ordenadas e barata de calcular. |

**Outras otimizações usadas na prática:**
*   **Particionamento de Hoare:** faz menos trocas que o de Lomuto.
*   **Partição em três vias (*3-way*):** separa `<`, `=` e `>` do pivô, excelente quando há muitos valores repetidos.
*   **Insertion Sort em trechos pequenos:** abaixo de uns 10 a 20 elementos, troca de algoritmo.
*   **Introsort:** se a recursão ficar fundo demais, troca para Heap Sort, garantindo $\mathcal{O}(n \log n)$ no pior caso. É a base do `std::sort` do C++.

---

## 📊 Comparação com Outros Algoritmos

| Característica | Merge Sort | Heap Sort | **Quick Sort** |
|---|---|---|---|
| Melhor caso | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ |
| Pior caso | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | **$\mathcal{O}(n^2)$** |
| Espaço extra | $\mathcal{O}(n)$ | $\mathcal{O}(1)$ | $\mathcal{O}(\log n)$ |
| Estável | **Sim** | Não | Não |
| In-place | Não | **Sim** | **Sim** |
| Velocidade prática | Boa | Mais lenta | **Geralmente a melhor** |

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Muito rápido na prática:** laços internos simples e acesso sequencial à memória (bom uso do cache).
*   **In-place:** quase nenhuma memória extra.
*   **Versátil:** muitas variações e otimizações conhecidas.
*   **Paralelizável:** os dois lados do pivô podem ser ordenados ao mesmo tempo.

**Desvantagens:**
*   **Pior caso quadrático:** pivôs ruins degradam o desempenho para $\mathcal{O}(n^2)$.
*   **Não é estável:** pode alterar a ordem de elementos iguais.
*   **Recursão profunda no pior caso:** risco de estouro de pilha se não for tratado.
*   **Não é adaptável nem online.**

---

## 💻 Exemplo Clássico em C

O código completo, com um comentário em cada linha e um `main` de exemplo, está no arquivo `quick_sort.c`. Abaixo, o essencial:

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Particiona arr[low..high] usando arr[high] como pivô (Lomuto)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   // pivô = último elemento
    int i = low - 1;         // fim da zona dos elementos <= pivô

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);   // leva o elemento para a zona dos menores
        }
    }
    swap(&arr[i + 1], &arr[high]);    // coloca o pivô na posição final
    return i + 1;                     // devolve a posição do pivô
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);   // ordena os menores
        quickSort(arr, p + 1, high);  // ordena os maiores
    }
}
```

**Pontos de atenção no código:**
*   A chamada inicial é `quickSort(arr, 0, n - 1)`.
*   Depois do particionamento, o pivô fica na posição `p` **definitiva**, por isso a recursão exclui `p` dos dois lados.
*   O caso base `low < high` encerra a recursão em trechos de 0 ou 1 elemento.

---

## 🎯 Quando devo usar o Quick Sort?

*   **Ordenação de arrays em memória:** é a escolha padrão em muitas bibliotecas (`qsort` em C, `std::sort` em C++ via Introsort).
*   **Memória limitada:** por ser in-place.
*   **Dados aleatórios ou sem padrão conhecido:** é aí que ele mais brilha.

Evite (ou use pivô aleatório/mediana de três) quando os dados puderem vir ordenados, e prefira o **Merge Sort** quando precisar de **estabilidade** ou de desempenho garantido $\mathcal{O}(n \log n)$.

---

## 📝 Resumo Rápido

*   **Ideia central:** escolha um pivô, separe menores e maiores, repita nos dois lados.
*   **Tempo:** $\mathcal{O}(n \log n)$ em média e no melhor caso; $\mathcal{O}(n^2)$ no pior caso.
*   **Espaço:** $\mathcal{O}(\log n)$ (pilha de recursão), in-place.
*   **Estável:** não. **Adaptável:** não. **Online:** não.
*   **Estratégia:** dividir para conquistar.
*   **Destaque:** o mais rápido na prática para arrays em memória, desde que o pivô seja bem escolhido.
