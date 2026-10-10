# Guia Completo: Algoritmo Bucket Sort (Ordenação por Baldes)

O **Bucket Sort** (ou Ordenação por Baldes) é um algoritmo de ordenação que **distribui os elementos em vários "baldes"** (faixas de valores), ordena cada balde separadamente e depois junta tudo na ordem. A distribuição não usa comparações entre elementos: ela usa uma **fórmula** que diz em qual balde cada valor deve cair.

Ele brilha quando os dados estão **distribuídos de forma mais ou menos uniforme** em um intervalo conhecido, porque cada balde acaba com poucos elementos e a ordenação interna fica barata.

---

## 🪣 Como Funciona? (A Analogia da Biblioteca)

Imagine que você precisa organizar 1.000 livros pelo ano de publicação, entre 1900 e 1999:
1. Você coloca 10 caixas na sala, uma para cada década: 1900–1909, 1910–1919, e assim por diante (**distribuição**).
2. Joga cada livro na caixa da sua década, sem se preocupar com a ordem dentro da caixa.
3. Depois ordena **cada caixa separadamente**, o que é rápido porque cada uma tem poucos livros (**ordenação dos baldes**).
4. Por fim, esvazia as caixas na estante, da primeira à última (**concatenação**).

Em termos de algoritmo, são quatro etapas:

1. **Criar os baldes:** divide o intervalo de valores em $k$ faixas de mesmo tamanho.
2. **Distribuir:** cada elemento `v` vai para o balde de índice $\lfloor v \cdot k / (\text{max} + 1) \rfloor$.
3. **Ordenar cada balde:** geralmente com Insertion Sort, já que os baldes costumam ser pequenos.
4. **Concatenar:** junta os baldes, do primeiro ao último.

### Exemplo passo a passo

Array inicial: `[78, 17, 39, 26, 72, 94, 21, 12, 23, 68]` (valores de 0 a 99, com 5 baldes de tamanho 20)

**Fase 1: distribuição** (índice do balde = $\lfloor v \cdot 5 / 100 \rfloor$)

| Balde | Faixa | Conteúdo (na ordem de chegada) |
|---|---|---|
| 0 | 0–19 | 17, 12 |
| 1 | 20–39 | 39, 26, 21, 23 |
| 2 | 40–59 | (vazio) |
| 3 | 60–79 | 78, 72, 68 |
| 4 | 80–99 | 94 |

**Fase 2: ordenação de cada balde**

| Balde | Antes | Depois |
|---|---|---|
| 0 | 17, 12 | 12, 17 |
| 1 | 39, 26, 21, 23 | 21, 23, 26, 39 |
| 2 | (vazio) | (vazio) |
| 3 | 78, 72, 68 | 68, 72, 78 |
| 4 | 94 | 94 |

**Fase 3: concatenação**

Resultado final: `[12, 17, 21, 23, 26, 39, 68, 72, 78, 94]`

> Para números reais no intervalo $[0, 1)$, a fórmula fica ainda mais simples: o balde de `x` é $\lfloor k \cdot x \rfloor$.

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
Seja $n$ o número de elementos e $k$ o número de baldes.
*   **Melhor Caso:** $\mathcal{O}(n + k)$
    *   Ocorre quando os elementos se espalham uniformemente: cada balde fica com cerca de $n/k$ elementos e a ordenação interna é quase de graça.
*   **Caso Médio:** $\mathcal{O}(n + k)$
    *   Com dados uniformemente distribuídos e $k$ proporcional a $n$, o algoritmo é **linear**.
*   **Pior Caso:** $\mathcal{O}(n^2)$
    *   Ocorre quando quase todos os elementos caem no **mesmo balde**. Aí o algoritmo se reduz à ordenação interna: $\mathcal{O}(n^2)$ com Insertion Sort, ou $\mathcal{O}(n \log n)$ se usar um algoritmo melhor dentro dos baldes.

> **Detalhe importante:** o desempenho depende da **distribuição dos dados**. Se os valores estiverem concentrados em uma faixa estreita, os baldes ficam desequilibrados e a vantagem some.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(n + k)$
    *   **Não é in-place.** Os baldes guardam, no total, cópias dos $n$ elementos, além da estrutura dos $k$ baldes.

### 3. Estabilidade
*   **É Estável?** Depende da ordenação interna.
    *   Se os elementos entrarem nos baldes na ordem original e o algoritmo usado dentro dos baldes for estável (como o Insertion Sort), o Bucket Sort é estável.

### 4. Baseado em Comparação?
*   **Parcialmente.** A distribuição usa uma fórmula, sem comparar elementos entre si. Mas a ordenação *dentro* de cada balde normalmente usa comparações.

### 5. Adaptabilidade
*   **É Adaptável?** Não no sentido clássico.
    *   Dados já ordenados não deixam a distribuição mais rápida. Por outro lado, o Insertion Sort usado nos baldes aproveita dados quase ordenados.

### 6. Algoritmo *Online*
*   **É Online?** Não.
    *   É preciso conhecer o intervalo dos valores (mínimo e máximo) antes de definir as faixas dos baldes.

---

## 🔍 Escolhendo o Número de Baldes

*   **Poucos baldes:** cada balde fica cheio e a ordenação interna pesa (tende a $\mathcal{O}(n^2)$ com Insertion Sort).
*   **Muitos baldes:** gasta-se memória e tempo percorrendo baldes vazios.
*   **Regra prática:** usar $k \approx n$ (ou $\sqrt{n}$ em alguns cenários), de modo que cada balde receba poucos elementos em média.

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Velocidade linear em média:** $\mathcal{O}(n + k)$ para dados uniformes.
*   **Paralelizável:** cada balde pode ser ordenado de forma independente, inclusive em threads ou máquinas diferentes.
*   **Funciona com números reais:** diferente do Counting Sort, aceita valores fracionários em um intervalo conhecido.
*   **Flexível:** o algoritmo usado dentro dos baldes pode ser trocado conforme a necessidade.

**Desvantagens:**
*   **Depende da distribuição:** dados concentrados degradam o desempenho para $\mathcal{O}(n^2)$.
*   **Usa memória extra:** $\mathcal{O}(n + k)$, não é in-place.
*   **Exige conhecer o intervalo:** é preciso saber (ou calcular) mínimo e máximo.
*   **Não é adaptável nem online.**

---

## 💻 Exemplo Clássico em C

```c
#include <stdlib.h>

#define K 5   // número de baldes

// Ordena valores inteiros de 0 a 99 usando K baldes de mesmo tamanho
void bucketSort(int arr[], int n) {
    int *bucket[K];
    int size[K] = {0};
    int i, b;

    // Cria os baldes (por simplicidade, cada um com capacidade n)
    for (b = 0; b < K; b++)
        bucket[b] = malloc(n * sizeof(int));

    // Fase 1: distribui cada elemento no balde da sua faixa
    for (i = 0; i < n; i++) {
        b = arr[i] * K / 100;          // índice do balde
        bucket[b][size[b]++] = arr[i];
    }

    int pos = 0;
    for (b = 0; b < K; b++) {
        // Fase 2: Insertion Sort dentro do balde (estável)
        for (i = 1; i < size[b]; i++) {
            int key = bucket[b][i];
            int j = i - 1;
            while (j >= 0 && bucket[b][j] > key) {
                bucket[b][j + 1] = bucket[b][j];
                j--;
            }
            bucket[b][j + 1] = key;
        }

        // Fase 3: concatena o balde de volta no array original
        for (i = 0; i < size[b]; i++)
            arr[pos++] = bucket[b][i];

        free(bucket[b]);
    }
}
```

**Pontos de atenção no código:**
*   A fórmula `arr[i] * K / 100` assume valores de **0 a 99**. Para outro intervalo, use `(v - min) * K / (max - min + 1)`.
*   Reservar capacidade `n` para cada balde é simples, mas gasta memória. Em código real, use listas encadeadas ou arrays dinâmicos.
*   O Insertion Sort dentro do balde é o que garante a estabilidade, desde que a distribuição preserve a ordem de chegada.

---

## 🎯 Quando devo usar o Bucket Sort?

*   **Dados com distribuição aproximadamente uniforme:** notas, percentuais, coordenadas, valores sorteados aleatoriamente.
*   **Números reais em um intervalo conhecido**, como valores em $[0, 1)$.
*   **Grandes volumes de dados** que podem ser divididos e processados em paralelo ou em disco (ordenação externa).
*   **Quando se quer um algoritmo linear** e a distribuição dos dados é conhecida.

Evite quando os dados forem muito concentrados em poucas faixas, quando o intervalo for desconhecido, ou quando a memória extra for um problema.

---

## 📊 Counting Sort vs. Radix Sort vs. Bucket Sort

| Característica | Counting Sort | Radix Sort (LSD) | Bucket Sort |
|---|---|---|---|
| Tempo médio | $\mathcal{O}(n + k)$ | $\mathcal{O}(d \cdot (n + b))$ | $\mathcal{O}(n + k)$ |
| Pior caso | $\mathcal{O}(n + k)$ | $\mathcal{O}(d \cdot (n + b))$ | $\mathcal{O}(n^2)$ |
| Espaço extra | $\mathcal{O}(n + k)$ | $\mathcal{O}(n + b)$ | $\mathcal{O}(n + k)$ |
| Estável | Sim | Sim | Depende do algoritmo interno |
| Aceita números reais | Não | Não | **Sim** |
| Depende da distribuição | Não | Não | **Sim** |
| Ideia central | Contar ocorrências | Ordenar dígito a dígito | Espalhar em faixas |

---

## 📝 Resumo Rápido

*   **Ideia central:** espalhe os elementos em faixas (baldes), ordene cada balde e junte.
*   **Tempo:** $\mathcal{O}(n + k)$ em média, $\mathcal{O}(n^2)$ no pior caso.
*   **Espaço:** $\mathcal{O}(n + k)$, **não** é in-place.
*   **Estável:** depende da ordenação interna. **Adaptável:** não. **Online:** não.
*   **Destaque:** excelente para dados uniformemente distribuídos, inclusive números reais.
