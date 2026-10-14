# Guia Completo: Pesquisa Sequencial (Busca Linear)

A **Pesquisa Sequencial** (ou Busca Linear) é o jeito mais direto de procurar um valor: **olhar os elementos um a um, do início ao fim**, até encontrar o que se procura ou acabar a lista. Não exige nenhuma preparação dos dados, e por isso funciona em qualquer array ou lista, ordenados ou não.

---

## 🔎 Como Funciona? (A Analogia do Chaveiro)

Você tem um chaveiro com 30 chaves e precisa achar a da porta de casa. Sem nenhuma organização, o que você faz?
1. Pega a **primeira chave** e tenta na porta.
2. Se não abriu, tenta a **segunda**, depois a **terceira**, e assim por diante.
3. Para quando uma chave abrir, ou quando as chaves acabarem (e aí você sabe que ela não está ali).

Em termos de algoritmo:

1. **Percorrer:** visita as posições `0, 1, 2, ..., n - 1` em ordem.
2. **Comparar:** a cada posição, compara o elemento com o valor procurado `x`.
3. **Parar:** se forem iguais, devolve a posição. Se o array acabar, devolve `-1` (não encontrado).

### Exemplo passo a passo

Array: `[38, 27, 43, 3, 9, 82, 10]`

**Procurando o valor 9** (encontrado)

| Passo | Posição | Elemento | Comparação | Resultado |
|---|---|---|---|---|
| 1 | 0 | 38 | 38 = 9? | não |
| 2 | 1 | 27 | 27 = 9? | não |
| 3 | 2 | 43 | 43 = 9? | não |
| 4 | 3 | 3 | 3 = 9? | não |
| 5 | 4 | 9 | 9 = 9? | **sim, devolve 4** |

São **5 comparações**.

**Procurando o valor 50** (não encontrado): o algoritmo compara com os 7 elementos, sem sucesso, e devolve `-1` depois de **7 comparações**.

---

## ⚙️ Características Mais Importantes

### 1. Complexidade de Tempo (Velocidade)
*   **Melhor Caso:** $\mathcal{O}(1)$
    *   O valor está na **primeira posição**: uma única comparação.
*   **Pior Caso:** $\mathcal{O}(n)$
    *   O valor está na **última posição** ou **não existe**: são $n$ comparações.
*   **Caso Médio:** $\mathcal{O}(n)$
    *   Se o valor existe e qualquer posição é igualmente provável, são em média $\frac{n + 1}{2}$ comparações, ou seja, cerca de metade do array.

> **Detalhe importante:** dobrar o tamanho do array **dobra** o tempo da busca. Para um milhão de elementos, o pior caso são um milhão de comparações.

### 2. Complexidade de Espaço (Memória)
*   **Espaço:** $\mathcal{O}(1)$
    *   Só usa o índice do laço.

### 3. Pré-requisitos
*   **Precisa de dados ordenados?** Não.
    *   Funciona com qualquer disposição dos dados, em arrays e também em **listas encadeadas**, onde a pesquisa binária nem seria possível.

### 4. Várias ocorrências
*   Em sua forma básica, devolve a **primeira** ocorrência do valor. Para achar todas, basta não parar no primeiro acerto e continuar até o fim.

---

## 🔀 Variações

| Variação | Ideia | Ganho |
|---|---|---|
| **Com sentinela** | Coloca o valor procurado como "guarda" depois do último elemento, para o laço não precisar testar `i < n` a cada volta | Menos comparações por volta (continua $\mathcal{O}(n)$) |
| **Em array ordenado** | Pode parar assim que encontrar um elemento **maior** que `x`, porque `x` não pode estar mais à frente | Busca sem sucesso mais rápida |
| **Mover para a frente** | A cada acerto, leva o elemento para o início da lista | Valores muito buscados ficam mais perto do começo |
| **Transposição** | A cada acerto, troca o elemento com o anterior | O mesmo efeito, de forma mais gradual |

---

## 📊 Comparação com a Pesquisa Binária

| Característica | **Pesquisa Sequencial** | Pesquisa Binária |
|---|---|---|
| Exige dados ordenados | **Não** | Sim |
| Melhor caso | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| Pior caso | $\mathcal{O}(n)$ | **$\mathcal{O}(\log n)$** |
| Funciona em lista encadeada | **Sim** | Não (precisa de acesso direto) |
| Complexidade do código | **Mínima** | Média |

---

## ✅ Vantagens e ❌ Desvantagens

**Vantagens:**
*   **Simplicidade:** poucas linhas e quase impossível de errar.
*   **Sem pré-processamento:** não precisa ordenar nem montar estruturas.
*   **Funciona em qualquer estrutura sequencial:** arrays, listas encadeadas, arquivos.
*   **Ótima para poucos elementos** ou para buscas isoladas.

**Desvantagens:**
*   **Lenta em grandes volumes:** o custo cresce linearmente com $n$.
*   **Não aproveita a ordem dos dados** (a versão básica).
*   **Ineficiente para buscas repetidas:** se você vai buscar muitas vezes nos mesmos dados, vale a pena organizá-los e usar outra técnica.

---

## 💻 Exemplo Clássico em C

O código completo, com um comentário em cada linha e um `main` de exemplo, está no arquivo `pesquisasequencial.c`. Abaixo, o essencial:

```c
int pesquisaSequencial(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i;      // achou: devolve a posição
        }
    }
    return -1;             // não achou
}
```

**Pontos de atenção no código:**
*   Devolver `-1` é uma convenção: como posições válidas são `0` ou maiores, `-1` nunca é confundido com um resultado real.
*   Em listas encadeadas, o `for` vira um laço `while (atual != NULL)` percorrendo as células.
*   Na versão com sentinela, o array precisa ter **uma posição extra** no final.

---

## 🎯 Quando devo usar a Pesquisa Sequencial?

*   **Dados desordenados** que você vai consultar poucas vezes.
*   **Arrays pequenos**, em que qualquer outra técnica seria exagero.
*   **Listas encadeadas**, que não permitem acesso direto às posições.
*   **Quando o custo de ordenar os dados não compensa** (por exemplo, uma única busca).

Se você vai fazer **muitas buscas** sobre os mesmos dados, ordene uma vez e use a Pesquisa Binária.

---

## 📝 Resumo Rápido

*   **Ideia central:** olhar elemento por elemento até achar o valor ou acabar o array.
*   **Tempo:** $\mathcal{O}(1)$ no melhor caso, $\mathcal{O}(n)$ no médio e no pior.
*   **Espaço:** $\mathcal{O}(1)$.
*   **Exige ordenação:** não. **Funciona em lista encadeada:** sim.
*   **Destaque:** a busca mais simples e universal, mas lenta para grandes volumes.