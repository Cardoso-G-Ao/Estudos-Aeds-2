# Guia Completo: Algoritmo Selection Sort (Ordenação por Seleção)

O **Selection Sort** (ou Ordenação por Seleção) é um algoritmo de ordenação simples e fácil de entender. Ele ordena o array repetindo um processo bem direto: **encontrar o menor elemento da parte não ordenada e colocá-lo na posição correta**, uma posição de cada vez.

Embora não seja eficiente para grandes volumes de dados, ele tem uma propriedade muito particular: realiza **pouquíssimas trocas**, o que o torna interessante em cenários onde escrever na memória é caro.

---

## 🏆 Como Funciona? (A Analogia da Fila por Altura)

Imagine que você precisa organizar uma fila de pessoas da mais baixa para a mais alta:
1. Você olha a fila inteira e procura a pessoa **mais baixa**.
2. Você troca essa pessoa com quem está na primeira posição.
3. Agora a primeira posição está definitiva. Você ignora ela e repete o processo com o restante da fila: procura a mais baixa entre as que sobraram e a coloca na segunda posição.
4. Repete até a fila inteira estar organizada.

O algoritmo divide virtualmente o array em uma parte **ordenada** (à esquerda) e uma parte **não ordenada** (à direita). A cada iteração, ele **seleciona o menor elemento** da parte não ordenada e o **troca** com o primeiro elemento dessa parte. Assim, a parte ordenada cresce uma posição por vez, e cada elemento colocado ali já está em sua posição final.

### Exemplo passo a passo

Array inicial: `[64, 25, 12, 22, 11]`

| Passo | Parte não ordenada | Menor encontrado | Array após a troca |
|---|---|---|---|
| 1 | `[64, 25, 12, 22, 11]` | 11 | `[11, 25, 12, 22, 64]` |
| 2 | `[25, 12, 22, 64]` | 12 | `[11, 12, 25, 22, 64]` |
| 3 | `[25, 22, 64]` | 22 | `[11, 12, 22, 25, 64]` |
| 4 | `[25, 64]` | 25 | `[11, 12, 22, 25, 64]` (já estava no lugar) |

Resultado final: `[11, 12, 22, 25, 64]`

---

## ⚙️ Características Mais Importantes

Aqui estão as propriedades técnicas que definem o Selection Sort e determinam quando ele deve ser usado:

### 1. Complexidade de Tempo (Velocidade)
*   **Melhor Caso:** $\mathcal{O}(n^2)$
    *   Mesmo que o array *já esteja ordenado*, o algoritmo **não tem como saber disso**. Ele sempre varre toda a parte não ordenada para ter certeza de que encontrou o menor elemento.
*   **Pior Caso:** $\mathcal{O}(n^2)$
    *   Em qualquer ordem, o número de comparações é o mesmo.
*   **Caso Médio:** $\mathcal{O}(n^2)$
    *   Em uma lista aleatória, o desempenho também é quadrático.

> **Detalhe importante:** o número de comparações é sempre exatamente $\frac{n(n-1)}{2}$, independentemente da disposição dos dados. Essa é uma diferença fundamental em relação ao Insertion Sort, que tem melhor caso $\mathcal{O}(n)$.

### 2. Número de Trocas (Escritas na Memória)
*   **Trocas:** no máximo $n - 1$, ou seja, $\mathcal{O}(n)$.
    *   Esta é a **grande característica** do Selection Sort. Cada elemento é movido no máximo uma vez, diretamente para sua posição final. Algoritmos como Insertion Sort e Bubble Sort podem fazer $\mathcal{O}(n^2)$ movimentações no pior caso.

### 3. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(1)$
    *   É um algoritmo **in-place** (in-loco). Não precisa de arrays auxiliares, apenas de algumas variáveis temporárias (o índice do menor elemento e uma variável para a troca).

### 4. Estabilidade
*   **É Estável?** Não (na implementação clássica).
    *   Um algoritmo estável preserva a ordem relativa de elementos com valores iguais. O Selection Sort pode quebrar essa ordem porque a troca "salta" por cima de outros elementos.
    *   **Exemplo:** considere `[4a, 4b, 2]`, onde `4a` e `4b` têm o mesmo valor. O menor é o `2`, que é trocado com `4a`, resultando em `[2, 4b, 4a]`. Agora o `4b` aparece antes do `4a`, ou seja, a ordem original foi perdida.
    *   É possível torná-lo estável, mas isso exige deslocar elementos em vez de trocar (como o Insertion Sort faz), o que elimina sua vantagem de poucas escritas.

### 5. Adaptabilidade
*   **É Adaptável?** Não.
    *   Seu desempenho **não melhora** se os dados já estiverem total ou parcialmente ordenados. Ele sempre executa o mesmo número de comparações.

### 6. Algoritmo *Online*
*   **É Online?** Não.
    *   Ele precisa ter todos os dados disponíveis desde o início para procurar o menor elemento. Se um novo número chegar depois, é preciso reexecutar a seleção.

---

## 📊 Selection Sort vs. Insertion Sort

| Característica | Selection Sort | Insertion Sort |
|---|---|---|
| Melhor caso | $\mathcal{O}(n^2)$ | **$\mathcal{O}(n)$** |
| Pior caso | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ |
| Número de trocas/escritas | **$\mathcal{O}(n)$** | $\mathcal{O}(n^2)$ |
| Estável | Não | **Sim** |
| Adaptável | Não | **Sim** |
| Online | Não | **Sim** |
| In-place | Sim | Sim |

Em resumo: o Insertion Sort costuma ser melhor na maioria das situações, mas o Selection Sort vence quando o que importa é **minimizar escritas**.

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Simplicidade:** O código é curto e muito fácil de implementar e entender.
*   **Poucas trocas:** Faz no máximo $n - 1$ trocas, o que é ótimo quando escrever é muito mais caro do que comparar (por exemplo, em memórias flash/EEPROM com ciclos de escrita limitados).
*   **Baixo consumo de memória:** Não requer alocação extra ($\mathcal{O}(1)$).
*   **Desempenho previsível:** O tempo de execução é praticamente o mesmo para qualquer entrada, sem surpresas de pior caso.

**Desvantagens:**
*   **Ineficiência em larga escala:** O tempo cresce de forma quadrática. Dobrar o tamanho da lista quadruplica o tempo de execução.
*   **Não aproveita dados ordenados:** Mesmo um array já ordenado custa $\mathcal{O}(n^2)$ comparações.
*   **Não é estável:** Pode alterar a ordem relativa de elementos iguais.
*   **Não é online:** Precisa de todos os dados desde o início.

---

## 💻 Exemplo Clássico em C

```c
void selectionSort(int arr[], int n) {
    int i, j, minIdx, temp;

    // Move a fronteira da parte não ordenada, uma posição por vez
    for (i = 0; i < n - 1; i++) {
        minIdx = i; // Assume que o primeiro elemento da parte não ordenada é o menor

        // Procura o verdadeiro menor elemento no restante do array
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        // Troca o menor encontrado com o elemento da posição i
        if (minIdx != i) {
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}
```

**Pontos de atenção no código:**
*   O loop externo vai até `n - 2`, pois quando restar apenas um elemento, ele já estará na posição correta.
*   O `if (minIdx != i)` evita uma troca desnecessária quando o elemento já está no lugar certo.
*   A troca só acontece **uma vez por iteração do loop externo**, e é isso que mantém o total de trocas em $\mathcal{O}(n)$.

---

## 🎯 Quando devo usar o Selection Sort?

O Selection Sort raramente é a primeira escolha, mas faz sentido em situações específicas:

*   **Escrita é muito cara:** em memórias como flash ou EEPROM, onde cada escrita desgasta o dispositivo, minimizar trocas é uma vantagem real.
*   **Arrays pequenos:** para poucos elementos, a simplicidade do código pesa mais que a eficiência.
*   **Ambientes com memória muito limitada:** por ser in-place com $\mathcal{O}(1)$ de espaço extra.
*   **Fins didáticos:** é um dos algoritmos mais claros para ensinar a ideia de ordenação por comparação e a análise de complexidade.

Já em bibliotecas padrão (como o `sort()` do C++, Java ou Python), o Selection Sort **não é utilizado**. Os algoritmos híbridos, como **Timsort** e **IntroSort**, preferem o Insertion Sort para pedaços pequenos, justamente por ele ser adaptável e estável.

---

## 📝 Resumo Rápido

*   **Ideia central:** a cada passo, selecione o menor elemento restante e coloque-o na posição correta.
*   **Tempo:** $\mathcal{O}(n^2)$ em todos os casos.
*   **Espaço:** $\mathcal{O}(1)$, in-place.
*   **Trocas:** no máximo $n - 1$.
*   **Estável:** não. **Adaptável:** não. **Online:** não.
*   **Destaque:** minimiza o número de escritas na memória.
