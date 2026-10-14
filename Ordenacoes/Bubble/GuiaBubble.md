# Guia Completo: Algoritmo Bubble Sort (Ordenação por Bolha)

O **Bubble Sort** (ou Ordenação por Bolha) é um dos algoritmos de ordenação mais simples. Ele percorre o array várias vezes, **comparando elementos vizinhos** e trocando-os de lugar quando estão fora de ordem. A cada passada, o maior elemento restante "sobe" até o fim do array, como uma bolha que sobe na água.

É raramente usado na prática, mas é um excelente ponto de partida: mostra com clareza o que é comparar, trocar, fazer uma passada e parar quando não há mais nada a fazer.

---

## 🫧 Como Funciona? (A Analogia das Bolhas)

Imagine bolhas de tamanhos diferentes dentro de um tubo vertical. As maiores sobem mais rápido. Em cada rodada:
1. Você olha **duas bolhas vizinhas** de baixo para cima.
2. Se a de baixo é **maior** que a de cima, elas trocam de lugar.
3. Ao terminar a rodada, a maior bolha de todas chegou ao topo e **não precisa mais ser mexida**.
4. Repete-se com as bolhas que sobraram, até uma rodada em que ninguém troca de lugar.

Em termos de algoritmo:

1. **Passada:** percorre o array comparando `arr[j]` com `arr[j + 1]`; se `arr[j] > arr[j + 1]`, troca os dois.
2. **Fixação:** ao final da passada, o maior elemento restante está na sua posição final. A próxima passada pode parar uma posição antes.
3. **Parada antecipada:** se uma passada inteira não fez nenhuma troca, o array já está ordenado e o algoritmo termina.

### Exemplo passo a passo

Array inicial: `[5, 1, 4, 2, 8]`

| Passada | Comparação | Ação | Array |
|---|---|---|---|
| 1 | 5 e 1 | troca | `[1, 5, 4, 2, 8]` |
| 1 | 5 e 4 | troca | `[1, 4, 5, 2, 8]` |
| 1 | 5 e 2 | troca | `[1, 4, 2, 5, 8]` |
| 1 | 5 e 8 | já em ordem | `[1, 4, 2, 5, 8]` |
| 2 | 1 e 4 | já em ordem | `[1, 4, 2, 5, 8]` |
| 2 | 4 e 2 | troca | `[1, 2, 4, 5, 8]` |
| 2 | 4 e 5 | já em ordem | `[1, 2, 4, 5, 8]` |
| 3 | 1 e 2 | já em ordem | `[1, 2, 4, 5, 8]` |
| 3 | 2 e 4 | já em ordem | `[1, 2, 4, 5, 8]` |

Na passada 3 não houve nenhuma troca, então o algoritmo para.

Resultado final: `[1, 2, 4, 5, 8]` (9 comparações e 4 trocas).

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
*   **Melhor Caso:** $\mathcal{O}(n)$
    *   Com a parada antecipada, um array **já ordenado** exige apenas uma passada, com $n - 1$ comparações e nenhuma troca.
*   **Pior Caso:** $\mathcal{O}(n^2)$
    *   Em um array em ordem **inversa**, toda comparação resulta em troca: são $\frac{n(n-1)}{2}$ comparações e o mesmo número de trocas.
*   **Caso Médio:** $\mathcal{O}(n^2)$
    *   Em uma lista aleatória, cerca de metade dos pares está fora de ordem.

> **Detalhe importante:** sem a parada antecipada, o Bubble Sort faz sempre $\frac{n(n-1)}{2}$ comparações, e o melhor caso também seria $\mathcal{O}(n^2)$. É a flag `trocou` que o torna adaptável.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(1)$
    *   É **in-place**: usa só algumas variáveis auxiliares (a flag e a variável da troca).

### 3. Estabilidade
*   **É Estável?** Sim.
    *   Só troca vizinhos quando o da esquerda é **estritamente maior** (`>`). Elementos iguais nunca passam um pelo outro.

### 4. Adaptabilidade
*   **É Adaptável?** Sim (com a parada antecipada).
    *   Quanto mais próximo de ordenado o array estiver, menos passadas são necessárias.

### 5. Algoritmo *Online*
*   **É Online?** Não.
    *   Um novo elemento exigiria percorrer o array de novo para encontrar o lugar dele.

---

## 📊 Comparação com Outros Algoritmos Simples

| Característica | **Bubble Sort** | Insertion Sort | Selection Sort |
|---|---|---|---|
| Melhor caso | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(n^2)$ |
| Pior caso | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ |
| Trocas (pior caso) | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | **$\mathcal{O}(n)$** |
| Estável | Sim | Sim | Não |
| Adaptável | Sim | Sim | Não |
| Na prática | O mais lento dos três | O melhor dos três | Poucas escritas |

O Bubble Sort costuma ser mais lento que o Insertion Sort porque faz **muito mais trocas** (cada troca move só uma posição).

---

## 🔀 Variações

*   **Com parada antecipada:** a versão deste guia, usando a flag `trocou`.
*   **Cocktail Shaker Sort (ordenação bidirecional):** alterna passadas da esquerda para a direita e da direita para a esquerda, levando o maior para o fim e o menor para o início em cada ida e volta.
*   **Comb Sort:** compara elementos separados por uma distância (*gap*) que vai diminuindo, resolvendo o problema dos "elementos pequenos no fim", as chamadas **tartarugas**.

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Simplicidade:** código curtíssimo, fácil de entender e de lembrar.
*   **Estável e in-place:** preserva a ordem dos iguais e não usa memória extra.
*   **Detecta array ordenado:** com a flag, termina em $\mathcal{O}(n)$ quando não há nada a fazer.

**Desvantagens:**
*   **Muito lento em arrays grandes:** $\mathcal{O}(n^2)$ comparações e trocas.
*   **Muitas trocas:** pior que Insertion Sort e Selection Sort nesse aspecto.
*   **"Tartarugas":** um elemento pequeno no final do array só anda **uma posição por passada** para a esquerda, enquanto os grandes ("lebres") correm para a direita.

---

## 💻 Exemplo Clássico em C

O código completo, com um comentário em cada linha e um `main` de exemplo, está no arquivo `Bubblesort.c`. Abaixo, o essencial:

```c
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break;   // nenhuma troca: já está ordenado
    }
}
```

**Pontos de atenção no código:**
*   O laço interno vai até `n - 1 - i`: os `i` últimos elementos já estão na posição final e não precisam ser comparados.
*   Sem o `if (!trocou) break;`, o algoritmo continua correto, mas perde a vantagem do melhor caso.
*   O `>` (e não `>=`) é o que mantém o algoritmo **estável**.

---

## 🎯 Quando devo usar o Bubble Sort?

*   **Ensino:** para aprender os conceitos de comparação, troca e passada.
*   **Arrays minúsculos ou quase ordenados:** onde o custo extra não faz diferença.
*   **Verificar se um array está ordenado:** uma passada sem trocas já responde.

Para qualquer coisa séria, prefira Insertion Sort (arrays pequenos), Merge Sort ou Quick Sort.

---

## 📝 Resumo Rápido

*   **Ideia central:** compare vizinhos e troque os que estão fora de ordem; a cada passada, o maior vai para o fim.
*   **Tempo:** $\mathcal{O}(n)$ no melhor caso (com flag), $\mathcal{O}(n^2)$ no médio e no pior.
*   **Espaço:** $\mathcal{O}(1)$, in-place.
*   **Estável:** sim. **Adaptável:** sim (com flag). **Online:** não.
*   **Destaque:** simples e didático, mas lento por causa do excesso de trocas.