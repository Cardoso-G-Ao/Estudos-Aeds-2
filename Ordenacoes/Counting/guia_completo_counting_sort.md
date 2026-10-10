# Guia Completo: Algoritmo Counting Sort (Ordenação por Contagem)

O **Counting Sort** (ou Ordenação por Contagem) é um algoritmo de ordenação **que não compara elementos entre si**. Em vez disso, ele *conta* quantas vezes cada valor aparece e usa essas contagens para calcular diretamente a posição final de cada elemento.

Por fugir da comparação, ele consegue quebrar o limite teórico de $\mathcal{O}(n \log n)$ dos algoritmos baseados em comparação (como Quick Sort e Merge Sort), mas com uma condição: os valores precisam ser **inteiros dentro de um intervalo pequeno e conhecido**.

---

## 🗳️ Como Funciona? (A Analogia da Urna de Votação)

Imagine uma eleição com candidatos numerados de 0 a 8. Em vez de comparar votos entre si, você faz o seguinte:
1. Cria uma folha de apuração com uma linha para cada candidato e vai marcando um traço a cada voto lido (**contagem**).
2. Soma os totais de cima para baixo: assim, cada linha passa a dizer "até aqui já foram contados X votos" (**soma acumulada**). Esse número indica **onde termina o bloco** daquele candidato na lista final.
3. Percorre os votos e coloca cada um exatamente na posição indicada pela folha, diminuindo o contador a cada uso (**posicionamento**).

Em termos de algoritmo, são três fases:

1. **Contar:** percorre o array e incrementa `count[valor]` para cada elemento.
2. **Acumular:** transforma `count` em uma soma de prefixos, de modo que `count[v]` indique quantos elementos são menores ou iguais a `v`.
3. **Posicionar:** percorre o array original **de trás para frente**, e para cada elemento `v` faz `output[--count[v]] = v`.

### Exemplo passo a passo

Array inicial: `[4, 2, 2, 8, 3, 3, 1]`

**Fase 1: contagem** (índice = valor)

| Valor | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|---|
| `count` | 0 | 1 | 2 | 2 | 1 | 0 | 0 | 0 | 1 |

**Fase 2: soma acumulada**

| Valor | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|---|
| `count` | 0 | 1 | 3 | 5 | 6 | 6 | 6 | 6 | 7 |

**Fase 3: posicionamento** (de trás para frente)

| Lê | `count[v]` depois de diminuir | Grava em `output[...]` |
|---|---|---|
| 1 | 0 | `output[0] = 1` |
| 3 | 4 | `output[4] = 3` |
| 3 | 3 | `output[3] = 3` |
| 8 | 6 | `output[6] = 8` |
| 2 | 2 | `output[2] = 2` |
| 2 | 1 | `output[1] = 2` |
| 4 | 5 | `output[5] = 4` |

Resultado final: `[1, 2, 2, 3, 3, 4, 8]`

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
Seja $n$ o número de elementos e $k$ o maior valor do array (o tamanho do intervalo).
*   **Melhor Caso:** $\mathcal{O}(n + k)$
*   **Pior Caso:** $\mathcal{O}(n + k)$
*   **Caso Médio:** $\mathcal{O}(n + k)$
    *   O custo não depende da ordem dos dados: o algoritmo sempre faz uma passada para contar, uma passada de tamanho $k$ para acumular e uma passada para posicionar.

> **Detalhe importante:** quando $k$ é da ordem de $n$, o Counting Sort é **linear**. Mas se $k$ for muito maior que $n$ (por exemplo, ordenar 10 números entre 0 e 1.000.000), o custo $\mathcal{O}(k)$ domina e o algoritmo vira um péssimo negócio.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(n + k)$
    *   **Não é in-place.** Precisa do array de contagem (tamanho $k+1$) e do array de saída (tamanho $n$).

### 3. Estabilidade
*   **É Estável?** Sim (se o posicionamento for feito de trás para frente).
    *   Percorrer a entrada do fim para o começo garante que, entre valores iguais, o que apareceu por último na entrada fique na última posição do bloco. Isso preserva a ordem original dos iguais.
    *   Essa propriedade é **essencial** para o Radix Sort, que usa o Counting Sort como sub-rotina.

### 4. Baseado em Comparação?
*   **Não.** Ele usa os valores como **índices** do array de contagem. Por isso não está sujeito ao limite inferior de $\Omega(n \log n)$.

### 5. Adaptabilidade
*   **É Adaptável?** Não.
    *   Dados já ordenados não deixam o algoritmo mais rápido.

### 6. Algoritmo *Online*
*   **É Online?** Não.
    *   Para acumular as contagens, é preciso conhecer todos os dados (ou pelo menos o intervalo) de antemão.

---

## 🧭 Limitações e Adaptações

*   **Só funciona com inteiros** (ou com dados que possam ser mapeados para inteiros, como caracteres ou chaves numéricas).
*   **Números negativos:** subtraia o menor valor (`min`) de todos antes de contar e use `count[v - min]`. O tamanho do array de contagem passa a ser `max - min + 1`.
*   **Ordenar objetos por chave:** a versão estável permite ordenar registros (por exemplo, alunos por nota) sem perder a ordem original dos empates.

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Velocidade linear:** $\mathcal{O}(n + k)$ é imbatível quando $k$ é pequeno.
*   **Estável:** preserva a ordem de elementos iguais.
*   **Desempenho previsível:** o tempo não varia com a disposição dos dados.
*   **Excelente como sub-rotina:** é a base do Radix Sort.

**Desvantagens:**
*   **Depende do intervalo:** se $k$ é enorme, desperdiça tempo e memória.
*   **Usa memória extra:** $\mathcal{O}(n + k)$, não é in-place.
*   **Limitado a inteiros:** não ordena números reais, strings longas ou tipos arbitrários diretamente.
*   **Não é adaptável nem online.**

---

## 💻 Exemplo Clássico em C

```c
#include <stdlib.h>

void countingSort(int arr[], int n) {
    int i, max = arr[0];

    // Descobre o maior valor para definir o tamanho do array de contagem
    for (i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    int *count  = calloc(max + 1, sizeof(int)); // zerado
    int *output = malloc(n * sizeof(int));

    // Fase 1: conta quantas vezes cada valor aparece
    for (i = 0; i < n; i++)
        count[arr[i]]++;

    // Fase 2: soma acumulada (count[v] = quantos elementos são <= v)
    for (i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Fase 3: posiciona de trás para frente (garante a estabilidade)
    for (i = n - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    // Copia o resultado de volta
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(count);
    free(output);
}
```

**Pontos de atenção no código:**
*   `calloc` já inicializa o array de contagem com zeros.
*   O loop da Fase 3 vai de `n - 1` até `0`. Se fosse de `0` até `n - 1`, o algoritmo continuaria ordenando, mas **perderia a estabilidade**.
*   Este código assume valores **não negativos**.

---

## 🎯 Quando devo usar o Counting Sort?

*   **Inteiros em intervalo pequeno:** notas de 0 a 100, idades, dias do mês, valores de pixels (0 a 255), letras do alfabeto.
*   **Quando $k = \mathcal{O}(n)$:** o algoritmo é linear e costuma vencer qualquer ordenação por comparação.
*   **Como sub-rotina do Radix Sort:** ordenar por um dígito de cada vez, com estabilidade.
*   **Contagem de frequências:** a própria fase 1 já resolve problemas como histogramas.

Evite quando o intervalo de valores for muito maior que a quantidade de elementos, ou quando os dados não forem inteiros.

---

## 📝 Resumo Rápido

*   **Ideia central:** conte as ocorrências, acumule as contagens e use-as como posições finais.
*   **Tempo:** $\mathcal{O}(n + k)$ em todos os casos.
*   **Espaço:** $\mathcal{O}(n + k)$, **não** é in-place.
*   **Estável:** sim (posicionando de trás para frente). **Adaptável:** não. **Online:** não.
*   **Não compara elementos:** usa valores como índices.
*   **Destaque:** ordenação linear para inteiros em um intervalo pequeno.
