# Guia Completo: Algoritmo Heap Sort (Ordenação por Heap)

O **Heap Sort** (ou Ordenação por Heap) é um algoritmo de ordenação baseado em uma estrutura chamada **heap binário**: uma árvore binária quase completa em que todo **pai é maior ou igual aos seus filhos** (*max-heap*). Como a raiz de um max-heap é sempre o maior elemento, o algoritmo repete duas ideias simples: **tirar o maior da raiz** e **reorganizar o heap**.

Ele une o melhor de dois mundos: garante $\mathcal{O}(n \log n)$ em **todos os casos**, como o Merge Sort, e é **in-place**, como o Quick Sort, usando apenas $\mathcal{O}(1)$ de memória extra.

---

## 🏔️ Como Funciona? (A Analogia do Campeonato)

Imagine um torneio em que cada jogador só precisa ser **melhor que os dois adversários logo abaixo dele** na chave. O campeão fica no topo:
1. Você monta a chave de modo que cada jogador seja melhor que seus dois "filhos". O maior de todos está no topo (**construção do heap**).
2. Você tira o campeão do topo e o coloca na **última posição** do ranking final.
3. Pega o último jogador da chave, coloca-o no topo (onde não deveria estar) e deixa que ele **desça** trocando com o melhor dos dois filhos até ocupar um lugar justo (**sift down**, ou "peneirar").
4. Repete: o novo campeão está no topo, vai para a penúltima posição, e assim por diante.

### O heap dentro de um array

Um heap não precisa de ponteiros: ele cabe direto em um array. Para o elemento na posição `i` (começando em 0):

| Relação | Posição |
|---|---|
| Filho esquerdo | `2*i + 1` |
| Filho direito | `2*i + 2` |
| Pai | `(i - 1) / 2` |

O array `[82, 27, 43, 3, 9, 38, 10]` representa esta árvore:

```
            82
          /    \
       27        43
      /  \      /  \
     3    9   38    10
```

### As duas fases do algoritmo

1. **Construir o max-heap:** percorre os nós que têm filhos, do **último pai até a raiz**, aplicando o *sift down* em cada um.
2. **Extrair o máximo repetidamente:** troca a raiz (maior) com o último elemento do heap, **diminui o tamanho do heap em 1** (o maior já está na posição final) e aplica *sift down* na nova raiz.

### Exemplo passo a passo

Array inicial: `[38, 27, 43, 3, 9, 82, 10]`

**Fase 1: construção do max-heap** (último pai = posição 2)

| Nó processado | Filhos | Ação | Array |
|---|---|---|---|
| 43 (pos. 2) | 82, 10 | 82 é o maior: troca | `[38, 27, 82, 3, 9, 43, 10]` |
| 27 (pos. 1) | 3, 9 | 27 já é maior: nada | `[38, 27, 82, 3, 9, 43, 10]` |
| 38 (pos. 0) | 27, 82 | 82 é o maior: troca; depois, 43 > 38: troca | `[82, 27, 43, 3, 9, 38, 10]` |

**Fase 2: extração do máximo** (a parte à direita de `|` já está ordenada)

| Passo | Troca raiz com | Depois de reorganizar o heap |
|---|---|---|
| 1 | 10 | `[43, 27, 38, 3, 9, 10 \| 82]` |
| 2 | 10 | `[38, 27, 10, 3, 9 \| 43, 82]` |
| 3 | 9 | `[27, 9, 10, 3 \| 38, 43, 82]` |
| 4 | 3 | `[10, 9, 3 \| 27, 38, 43, 82]` |
| 5 | 3 | `[9, 3 \| 10, 27, 38, 43, 82]` |
| 6 | 3 | `[3 \| 9, 10, 27, 38, 43, 82]` |

Resultado final: `[3, 9, 10, 27, 38, 43, 82]`

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
*   **Melhor Caso:** $\mathcal{O}(n \log n)$
*   **Pior Caso:** $\mathcal{O}(n \log n)$
*   **Caso Médio:** $\mathcal{O}(n \log n)$
    *   Cada *sift down* percorre no máximo a altura do heap, que é $\log_2 n$. A extração faz $n - 1$ delas.

> **Detalhe importante:** construir o heap, apesar de parecer custar $n \log n$, custa apenas $\mathcal{O}(n)$. A maioria dos nós está perto das folhas e desce pouquíssimo; só poucos nós, perto da raiz, descem muito. O custo total da ordenação é dominado pela fase de extração.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(1)$ (na versão iterativa)
    *   É **in-place**: o heap vive dentro do próprio array. Com o *sift down* recursivo, a pilha usa $\mathcal{O}(\log n)$, mas a versão com laço usa apenas $\mathcal{O}(1)$.

### 3. Estabilidade
*   **É Estável?** Não.
    *   As trocas entre a raiz e o último elemento levam valores para longe de suas posições originais, quebrando a ordem de elementos iguais.

### 4. Baseado em Comparação?
*   **Sim.** Atinge o limite inferior $\Omega(n \log n)$ e é assintoticamente ótimo entre os algoritmos por comparação.

### 5. Adaptabilidade
*   **É Adaptável?** Não.
    *   Dados já ordenados não ajudam: o algoritmo constrói o heap e extrai todos os elementos do mesmo jeito.

### 6. Algoritmo *Online*
*   **É Online?** Não.
    *   Precisa de todos os dados para construir o heap inicial. (Mas a estrutura de heap, em si, aceita inserções, e é a base das **filas de prioridade**.)

---

## 📊 Comparação com Outros Algoritmos

| Característica | Merge Sort | Quick Sort | **Heap Sort** |
|---|---|---|---|
| Melhor caso | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ |
| Pior caso | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n^2)$ | **$\mathcal{O}(n \log n)$** |
| Espaço extra | $\mathcal{O}(n)$ | $\mathcal{O}(\log n)$ | **$\mathcal{O}(1)$** |
| Estável | **Sim** | Não | Não |
| In-place | Não | Sim | **Sim** |
| Velocidade prática | Boa | **A melhor** | Mais lenta que as outras duas |

Na prática, o Heap Sort costuma perder para o Quick Sort por ter **pior localidade de cache**: os saltos entre pai e filhos (`i`, `2i+1`, `2i+2`) pulam por regiões distantes da memória.

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Desempenho garantido:** $\mathcal{O}(n \log n)$ no pior caso, sem surpresas.
*   **Memória mínima:** $\mathcal{O}(1)$ de espaço extra.
*   **Não depende de pivôs nem da disposição dos dados.**
*   **Reaproveita a estrutura de heap:** a mesma ideia sustenta as filas de prioridade.

**Desvantagens:**
*   **Mais lento na prática** que o Quick Sort, por causa do acesso à memória pouco amigável ao cache.
*   **Não é estável.**
*   **Não é adaptável:** não aproveita dados já ordenados.
*   **Não é online.**

---

## 💻 Exemplo Clássico em C

O código completo, com um comentário em cada linha e um `main` de exemplo, está no arquivo `heap_sort.c`. Abaixo, o essencial:

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// "Peneira" o nó i para baixo, considerando que o heap tem n elementos
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])   largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {                 // algum filho é maior que o pai
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);       // continua descendo
    }
}

void heapSort(int arr[], int n) {
    // Fase 1: constrói o max-heap, do último pai até a raiz
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Fase 2: move o maior para o fim e reorganiza o heap restante
    for (int end = n - 1; end > 0; end--) {
        swap(&arr[0], &arr[end]);
        heapify(arr, end, 0);
    }
}
```

**Pontos de atenção no código:**
*   O último nó com filhos está na posição `n / 2 - 1`; os nós depois dele são folhas e não precisam de *sift down*.
*   Na fase 2, `heapify(arr, end, 0)` usa `end` como novo tamanho do heap: as posições a partir de `end` já estão ordenadas e ficam de fora.
*   Os dois `if` consecutivos escolhem o maior entre o pai e os dois filhos, comparando o filho direito com o **vencedor** da primeira comparação.

---

## 🎯 Quando devo usar o Heap Sort?

*   **Quando é preciso garantia de $\mathcal{O}(n \log n)$ sem memória extra:** sistemas embarcados e de tempo real, onde o pior caso do Quick Sort e a memória do Merge Sort são problemas.
*   **Como proteção no Introsort:** quando a recursão do Quick Sort fica profunda demais, troca-se para Heap Sort.
*   **Quando só se precisa dos $k$ maiores (ou menores) elementos:** basta extrair $k$ vezes do heap, sem ordenar tudo.
*   **Filas de prioridade:** a estrutura de heap é a base de agendadores de tarefas, algoritmo de Dijkstra e compressão de Huffman.

Evite quando a estabilidade for necessária (prefira o **Merge Sort**) ou quando a velocidade média for o principal critério (prefira o **Quick Sort**).

---

## 📝 Resumo Rápido

*   **Ideia central:** construa um max-heap e extraia o maior elemento repetidamente, levando-o para o fim do array.
*   **Tempo:** $\mathcal{O}(n \log n)$ em todos os casos (construção do heap em $\mathcal{O}(n)$).
*   **Espaço:** $\mathcal{O}(1)$, in-place.
*   **Estável:** não. **Adaptável:** não. **Online:** não.
*   **Estrutura-chave:** heap binário armazenado em array (`2i+1`, `2i+2`, `(i-1)/2`).
*   **Destaque:** desempenho garantido com memória mínima.
