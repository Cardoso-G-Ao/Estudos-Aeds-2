# Guia Completo: Algoritmo Radix Sort (Ordenação por Raiz)

O **Radix Sort** (ou Ordenação por Raiz) é um algoritmo de ordenação **que não compara elementos entre si**. Ele ordena os números **dígito por dígito**, começando pelo dígito menos significativo (as unidades) e indo até o mais significativo, usando a cada passada um algoritmo **estável** (normalmente o Counting Sort).

É a versão digital de uma ideia antiga: as máquinas de cartões perfurados e as antigas classificadoras de correspondência já ordenavam documentos exatamente assim, uma coluna de cada vez.

---

## 🔢 Como Funciona? (A Analogia da Triagem de Cartas)

Imagine um funcionário dos Correios com uma pilha de cartas numeradas e dez caixas rotuladas de 0 a 9:
1. **Primeira rodada:** ele olha só o **último dígito** de cada carta (unidades) e joga a carta na caixa correspondente. Depois recolhe as caixas na ordem de 0 a 9, sem embaralhar o conteúdo de cada uma.
2. **Segunda rodada:** repete o processo, agora olhando o **penúltimo dígito** (dezenas).
3. **Terceira rodada:** repete com as **centenas**, e assim por diante, até o dígito mais significativo.

Parece que cada rodada "bagunça" o trabalho da anterior, mas não bagunça: como cada rodada é **estável**, empates no dígito atual mantêm a ordem que já foi conquistada nos dígitos menos significativos. Ao final, a lista está totalmente ordenada.

### Exemplo passo a passo

Array inicial: `[170, 45, 75, 90, 802, 24, 2, 66]`

**Passada 1: dígito das unidades**

| Balde | 0 | 2 | 4 | 5 | 6 |
|---|---|---|---|---|---|
| Conteúdo | 170, 90 | 802, 2 | 24 | 45, 75 | 66 |

Resultado: `[170, 90, 802, 2, 24, 45, 75, 66]`

**Passada 2: dígito das dezenas**

| Balde | 0 | 2 | 4 | 6 | 7 | 9 |
|---|---|---|---|---|---|---|
| Conteúdo | 802, 2 | 24 | 45 | 66 | 170, 75 | 90 |

Resultado: `[802, 2, 24, 45, 66, 170, 75, 90]`

**Passada 3: dígito das centenas**

| Balde | 0 | 1 | 8 |
|---|---|---|---|
| Conteúdo | 2, 24, 45, 66, 75, 90 | 170 | 802 |

Resultado final: `[2, 24, 45, 66, 75, 90, 170, 802]`

> Repare como a estabilidade trabalha: na passada 3, os números `2, 24, 45, 66, 75, 90` caem todos no balde 0 e **saem na mesma ordem em que entraram**, que já era a ordem correta graças às passadas anteriores. Sem estabilidade, essa ordem se perderia.

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
Seja $n$ o número de elementos, $d$ o número de dígitos do maior valor e $b$ a base numérica (10 no exemplo).
*   **Melhor Caso:** $\mathcal{O}(d \cdot (n + b))$
*   **Pior Caso:** $\mathcal{O}(d \cdot (n + b))$
*   **Caso Médio:** $\mathcal{O}(d \cdot (n + b))$
    *   São $d$ passadas, e cada uma custa $\mathcal{O}(n + b)$ (é um Counting Sort sobre um dígito). Se $d$ e $b$ são constantes, o algoritmo é **linear**: $\mathcal{O}(n)$.

> **Detalhe importante:** o tempo depende da **quantidade de dígitos**, não do valor numérico em si. Ordenar um milhão de números de até 6 dígitos exige apenas 6 passadas.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(n + b)$
    *   A versão clássica **não é in-place**: precisa de um array de saída e de $b$ contadores/baldes.

### 3. Estabilidade
*   **É Estável?** Sim, desde que a sub-rotina de cada passada seja estável.
    *   Esta é a condição de correção do algoritmo. Se a ordenação por dígito não fosse estável, as passadas anteriores seriam desfeitas.

### 4. Baseado em Comparação?
*   **Não.** Ele usa o valor de cada dígito como índice de um balde. Por isso não está sujeito ao limite $\Omega(n \log n)$.

### 5. Adaptabilidade
*   **É Adaptável?** Não.
    *   Dados já ordenados não reduzem o número de passadas.

### 6. Algoritmo *Online*
*   **É Online?** Não.
    *   Todos os elementos precisam estar presentes para cada passada.

---

## 🔀 Variações: LSD e MSD

| Variação | Direção | Características |
|---|---|---|
| **LSD** (*Least Significant Digit*) | Do dígito menos significativo para o mais significativo | A mais comum e simples. Funciona bem para inteiros e chaves de tamanho fixo. |
| **MSD** (*Most Significant Digit*) | Do dígito mais significativo para o menos significativo | Divide em grupos e ordena cada grupo recursivamente. Pode parar cedo e funciona bem com strings de tamanhos diferentes. |

Este guia usa a versão **LSD**.

**Escolha da base:** usar base 10 é didático, mas na prática costuma-se usar bases potência de 2 (como 256), que permitem extrair dígitos com operações de bits e reduzem o número de passadas.

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Velocidade linear:** $\mathcal{O}(d \cdot (n + b))$ é muito rápido para inteiros com poucos dígitos.
*   **Estável:** preserva a ordem de elementos iguais.
*   **Desempenho previsível:** não tem pior caso quadrático.
*   **Ótimo para chaves de tamanho fixo:** CEPs, CPFs, datas, IPs, números de telefone.

**Desvantagens:**
*   **Usa memória extra:** $\mathcal{O}(n + b)$, não é in-place.
*   **Limitado a dados "digitáveis":** inteiros, strings, ou tipos que possam ser decompostos em dígitos/caracteres.
*   **Pode perder para algoritmos por comparação** quando $d$ é grande (chaves muito longas) em relação a $\log n$.
*   **Não é adaptável nem online.**

---

## 💻 Exemplo Clássico em C

```c
#include <stdlib.h>

// Counting Sort estável aplicado a UM dígito (definido por exp = 1, 10, 100...)
static void countingSortByDigit(int arr[], int n, int exp) {
    int *output = malloc(n * sizeof(int));
    int count[10] = {0};
    int i;

    // Conta as ocorrências de cada dígito (0 a 9)
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Soma acumulada: posição final de cada bloco de dígito
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // De trás para frente, para manter a estabilidade
    for (i = n - 1; i >= 0; i--) {
        int d = (arr[i] / exp) % 10;
        output[--count[d]] = arr[i];
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

void radixSort(int arr[], int n) {
    int i, max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];

    // Uma passada para cada dígito do maior valor
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortByDigit(arr, n, exp);
}
```

**Pontos de atenção no código:**
*   `exp` vale 1, 10, 100... e `(arr[i] / exp) % 10` extrai o dígito da vez.
*   O número de passadas é definido pelo **maior valor**: o laço para quando `max / exp` chega a zero.
*   A sub-rotina precisa ser **estável**, por isso o posicionamento é feito de trás para frente.
*   Este código assume valores **não negativos**. Para negativos, separe os grupos ou some um deslocamento a todos os valores.

---

## 🎯 Quando devo usar o Radix Sort?

*   **Muitos inteiros com poucos dígitos:** identificadores, códigos, timestamps, endereços IPv4.
*   **Chaves de tamanho fixo:** CEPs, CPFs, placas, datas no formato AAAAMMDD.
*   **Strings de mesmo comprimento:** ordenação lexicográfica por caractere, usando a variação LSD.
*   **Grandes volumes de dados** em que $d$ é pequeno: é um dos poucos casos em que se ganha de $\mathcal{O}(n \log n)$ na prática.

Evite quando as chaves tiverem muitos dígitos em relação a $\log n$, quando os dados não puderem ser decompostos em dígitos, ou quando a memória extra for um problema.

---

## 📝 Resumo Rápido

*   **Ideia central:** ordene dígito por dígito, do menos significativo para o mais significativo, sempre com uma ordenação estável.
*   **Tempo:** $\mathcal{O}(d \cdot (n + b))$ em todos os casos, linear quando $d$ e $b$ são constantes.
*   **Espaço:** $\mathcal{O}(n + b)$, **não** é in-place.
*   **Estável:** sim (se a sub-rotina for estável). **Adaptável:** não. **Online:** não.
*   **Não compara elementos:** usa dígitos como índices de baldes.
*   **Destaque:** ordenação linear para inteiros e chaves de tamanho fixo.
