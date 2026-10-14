# Guia Completo: Pesquisa Binária (Busca Binária)

A **Pesquisa Binária** é um algoritmo de busca extremamente eficiente que funciona em **arrays ordenados**. Em vez de olhar os elementos um a um, ela olha o elemento do **meio** e, com uma única comparação, **descarta metade** das possibilidades. Repetindo isso, o espaço de busca encolhe muito rápido.

Para encontrar um valor entre **1 milhão** de elementos ordenados, bastam cerca de **20 comparações**. Uma pesquisa sequencial poderia precisar de um milhão.

---

## 📖 Como Funciona? (A Analogia da Lista Telefônica)

Você quer achar "Marcos" em uma lista telefônica de ordem alfabética:
1. Abre o livro **no meio**. Lá está "Helena".
2. "Marcos" vem **depois** de "Helena" no alfabeto, então você descarta toda a primeira metade.
3. Abre no meio da metade que sobrou, e repete o raciocínio.
4. Em poucos passos, você chega ao nome (ou percebe que ele não está ali).

Em termos de algoritmo, mantemos um intervalo `[esq, dir]` onde o valor `x` pode estar:

1. **Calcular o meio:** `meio = esq + (dir - esq) / 2`.
2. **Comparar:**
   * `arr[meio] == x`: achou, devolve `meio`.
   * `arr[meio] < x`: o valor está à direita, então `esq = meio + 1`.
   * `arr[meio] > x`: o valor está à esquerda, então `dir = meio - 1`.
3. **Repetir** enquanto `esq <= dir`. Se o intervalo ficar vazio, devolve `-1`.

### Exemplo passo a passo

Array **ordenado**: `[3, 9, 10, 27, 38, 43, 82]` (posições 0 a 6)

**Procurando o valor 43** (encontrado)

| Passo | `esq` | `dir` | `meio` | `arr[meio]` | Decisão |
|---|---|---|---|---|---|
| 1 | 0 | 6 | 3 | 27 | 27 < 43: `esq = 4` |
| 2 | 4 | 6 | 5 | 43 | 43 = 43: **achou na posição 5** |

São **2 passos**, contra 6 da pesquisa sequencial.

**Procurando o valor 12** (não encontrado)

| Passo | `esq` | `dir` | `meio` | `arr[meio]` | Decisão |
|---|---|---|---|---|---|
| 1 | 0 | 6 | 3 | 27 | 27 > 12: `dir = 2` |
| 2 | 0 | 2 | 1 | 9 | 9 < 12: `esq = 2` |
| 3 | 2 | 2 | 2 | 10 | 10 < 12: `esq = 3` |
| fim | 3 | 2 | | | `esq > dir`: **não encontrado** |

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
*   **Melhor Caso:** $\mathcal{O}(1)$
    *   O valor está exatamente no meio do array: uma comparação.
*   **Pior Caso:** $\mathcal{O}(\log n)$
    *   O valor está em uma ponta ou não existe: o intervalo é dividido ao meio até restar um elemento, em no máximo $\lfloor \log_2 n \rfloor + 1$ passos.
*   **Caso Médio:** $\mathcal{O}(\log n)$

> **Detalhe importante:** a cada passo, o intervalo cai pela metade. Por isso, **dobrar o tamanho do array adiciona apenas 1 passo**.

| Tamanho do array ($n$) | Sequencial (pior caso) | Binária (pior caso) |
|---|---|---|
| 10 | 10 | 4 |
| 1.000 | 1.000 | 10 |
| 1.000.000 | 1.000.000 | 20 |
| 1.000.000.000 | 1.000.000.000 | 30 |

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(1)$ na versão iterativa.
*   Na versão **recursiva**, a pilha de chamadas ocupa $\mathcal{O}(\log n)$.

### 3. Pré-requisitos
*   **Os dados precisam estar ordenados** e em uma estrutura com **acesso direto** por posição (como um array).
*   Em **listas encadeadas** ela não compensa, pois chegar ao "meio" exige percorrer a lista.

### 4. Elementos repetidos
*   Se o valor aparece várias vezes, a versão básica devolve **uma** das ocorrências, sem garantir qual. Existem variações que devolvem a **primeira** ou a **última** (os chamados *lower bound* e *upper bound*).

---

## 📊 Comparação com a Pesquisa Sequencial

| Característica | Pesquisa Sequencial | **Pesquisa Binária** |
|---|---|---|
| Exige dados ordenados | Não | **Sim** |
| Pior caso | $\mathcal{O}(n)$ | **$\mathcal{O}(\log n)$** |
| Funciona em lista encadeada | Sim | Não |
| Custo de preparação | Nenhum | Ordenar os dados ($\mathcal{O}(n \log n)$) |
| Vale a pena quando... | Poucas buscas ou poucos dados | Muitas buscas sobre os mesmos dados |

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Muito rápida:** crescimento logarítmico, que quase não sente o tamanho do array.
*   **Pouca memória:** $\mathcal{O}(1)$ na versão iterativa.
*   **Base de várias técnicas:** inserção em posição ordenada, busca de limites, "busca binária sobre a resposta".

**Desvantagens:**
*   **Exige dados ordenados:** se o array não estiver ordenado, o resultado fica errado.
*   **Exige acesso direto:** não serve para listas encadeadas.
*   **Manter a ordem custa caro:** inserir ou remover em um array ordenado exige deslocar elementos.

---

## 💻 Exemplo Clássico em C

O código completo, com um comentário em cada linha e um `main` de exemplo, está no arquivo `pesquisabinaria.c`. Abaixo, o essencial:

```c
int pesquisaBinaria(int arr[], int n, int x) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (arr[meio] == x) return meio;     // achou
        if (arr[meio] < x) esq = meio + 1;   // descarta a metade esquerda
        else dir = meio - 1;                 // descarta a metade direita
    }
    return -1;                               // não existe
}
```

**Pontos de atenção no código:**
*   `meio = esq + (dir - esq) / 2` evita o **estouro de inteiro** que `(esq + dir) / 2` pode causar com arrays muito grandes.
*   A condição do laço é `esq <= dir` (com o `=`): quando sobra um único elemento, `esq == dir` e ele ainda precisa ser testado.
*   Ao descartar, sempre use `meio + 1` ou `meio - 1`, e não `meio`: o elemento do meio já foi testado, e usar `meio` pode gerar um laço infinito.

---

## 🎯 Quando devo usar a Pesquisa Binária?

*   **Muitas consultas sobre dados que mudam pouco:** ordene uma vez e busque rápido muitas vezes.
*   **Grandes volumes de dados ordenados:** dicionários, tabelas, índices, listas de preços.
*   **Descobrir onde inserir** um novo elemento para manter um array ordenado.
*   **Problemas em que se "adivinha" um valor** (por exemplo, o menor valor que satisfaz uma condição), pesquisando sobre o espaço de respostas.

Evite quando os dados não estão ordenados e só serão consultados uma vez, ou quando a estrutura é uma lista encadeada.

---

## 📝 Resumo Rápido

*   **Ideia central:** olhar o meio do intervalo e descartar a metade onde o valor não pode estar.
*   **Tempo:** $\mathcal{O}(1)$ no melhor caso, $\mathcal{O}(\log n)$ no médio e no pior.
*   **Espaço:** $\mathcal{O}(1)$ (iterativa) ou $\mathcal{O}(\log n)$ (recursiva).
*   **Exige ordenação:** sim. **Exige acesso direto:** sim.
*   **Destaque:** entre 1 milhão de elementos, encontra qualquer um em cerca de 20 passos.