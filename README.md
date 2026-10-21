# 📚 Estudos de AEDS 2

Repositório de estudos da disciplina **Algoritmos e Estruturas de Dados 2**. Aqui estão reunidos, em um só lugar, os **códigos em C**, os **guias de estudo** e as **demonstrações interativas** dos principais algoritmos de ordenação, dos algoritmos de pesquisa, dos fundamentos de complexidade e das estruturas de dados vistas na disciplina (células, listas, filas, pilhas, matriz flexível e árvore binária de pesquisa).

Este repositório foi feito por **Gabriel Cardoso Alvares de Oliveira**. Para **praticar** o que está aqui, existe um repositório só de exercícios, o [**Exercicios-Estudos-Aeds-2-**](https://github.com/Cardoso-G-Ao/Exercicios-Estudos-Aeds-2-), com listas de exercícios e soluções em C.

A ideia do projeto é simples: para cada assunto, você tem três formas de aprender.

| Formato | O que é | Para que serve |
|---|---|---|
| 📖 **Guia** (`.md`) | Texto explicativo com analogia, passo a passo, complexidade e quando usar | Entender a teoria |
| 🎮 **Demonstração** (`.html`) | Página interativa que executa o algoritmo passo a passo | Ver o algoritmo acontecendo |
| 💻 **Código** (`.c`) | Implementação em C, pronta para compilar | Praticar e testar |

> 📌 Nem todo assunto tem os três formatos. **Complexidade** tem guia e código; **listas, filas encadeadas, pilha e células** têm só código (a **fila circular** tem também guia e demonstração); e as plataformas interativas da pasta `Estudos/` reúnem animações de várias dessas estruturas.

---

## 📑 Sumário

1. [Como navegar pelo projeto](#-como-navegar-pelo-projeto)
2. [Estrutura de pastas](#-estrutura-de-pastas)
3. [Complexidade de algoritmos](#-complexidade-de-algoritmos)
4. [Algoritmos de ordenação](#-algoritmos-de-ordenação)
5. [Algoritmos de pesquisa](#-algoritmos-de-pesquisa)
6. [Estruturas de dados](#-estruturas-de-dados)
7. [Matriz flexível](#-matriz-flexível)
8. [Árvore binária de pesquisa](#-árvore-binária-de-pesquisa)
9. [Pasta Estudos](#-pasta-estudos)
10. [Como usar as demonstrações](#-como-usar-as-demonstrações)
11. [Como compilar e executar os códigos em C](#-como-compilar-e-executar-os-códigos-em-c)
12. [Como funciona o index.html](#-como-funciona-o-indexhtml)
13. [Publicar no GitHub Pages](#-publicar-no-github-pages-opcional)
14. [Sugestão de roteiro de estudo](#-sugestão-de-roteiro-de-estudo)
15. [Repositório de exercícios](#-repositório-de-exercícios)
16. [Autor](#-autor)

---

## 🧭 Como navegar pelo projeto

Existem duas formas de usar o repositório.

**1. Pelo `index.html` (recomendado)**

Abra o arquivo `index.html` no navegador. Ele funciona como um "mini site" do repositório:

- barra lateral com todas as pastas e arquivos, com **busca** por nome;
- cada algoritmo tem abas **Guia**, **Demonstração** e **Código**;
- os guias aparecem formatados (tabelas, fórmulas e código colorido);
- as demonstrações rodam dentro da própria página;
- tema claro e escuro, e funciona no celular.

**2. Pelas pastas**

Entre na pasta do assunto e abra o arquivo que quiser: o `.md` no próprio GitHub, o `.html` no navegador e o `.c` no seu editor.

---

## 🗂️ Estrutura de pastas

```
Estudos-Aeds-2/
├── index.html                 # navegador do repositório (gerado pelo script)
├── gerar_index.py             # script que gera o index.html
├── README.md                  # este arquivo
│
├── Complexidade/              # fundamentos de complexidade de algoritmos
│   ├── Guiacomplexidade.md    # guia: notação O, Ω, Θ, classes e como analisar um código
│   └── complexidade.c         # conta operações para ver o crescimento de cada classe
│
├── Ordenacoes/                # 9 algoritmos de ordenação
│   ├── Bubble/                # Bubble Sort
│   ├── Insercao/              # Insertion Sort
│   ├── Selecao/               # Selection Sort
│   ├── Counting/              # Counting Sort
│   ├── Radix/                 # Radix Sort
│   ├── Bucket/                # Bucket Sort
│   ├── Merge/                 # Merge Sort
│   ├── Quick/                 # Quick Sort
│   ├── Heap/                  # Heap Sort
│   └── OrdenacaoParcial/      # ordenação parcial: os k menores, em ordem
│       (cada pasta: guia .md + demonstração .html + código .c)
│
├── Pesquisa/                  # algoritmos de pesquisa (busca)
│   ├── PesquisaSequencial/    # guia + demonstração + código da pesquisa sequencial
│   └── PesquisaBinaria/       # guia + demonstração + código da pesquisa binária
│
├── LIsta/                     # listas
│   ├── LIstaSimples/          # lista com vetor (array)
│   ├── LIstaFlexivel/         # lista com vetor alocado dinamicamente
│   ├── ListaEncadeada/        # lista com células encadeadas
│   └── ListaDuplaEncadeada/   # lista com células duplas
│
├── Fila/                      # filas
│   ├── FilaEncadeadaNormal/   # fila com células
│   ├── FIlaDuplamenteEncadeada/
│   └── FilaCircular/          # fila circular
│
├── Pilha/                     # pilha com células encadeadas
│   ├── PilhaInserir.c         # empilhar
│   └── PilhaRemover.c         # desempilhar
│
├── CelulaEstrutura/           # as "células" (nós) usadas nas estruturas encadeadas
│   ├── Celula.c
│   ├── CelulaDupla.c
│   └── Celulacabeca.c
│
├── MatrizFlexivel/            # matriz feita de células com 4 ponteiros (lista ortogonal)
│   ├── guia_completo_matriz_flex_vel.md
│   ├── demonstra_o_interativa_matriz_flex_vel.html
│   └── MatrizFlexivel.c
│
├── Arvore/                    # árvores
│   └── ArvoreBinariadePesquisa/   # árvore binária de pesquisa (BST)
│       ├── guia_completo_rvore_bin_ria_de_pesquisa.md
│       ├── arvore_bin_ria_de_pesquisa.html
│       └── Arvore.c
│
└── Estudos/                   # materiais extras e plataformas interativas
    ├── FIlaCircularEstudos/   # estudo sobre fila circular
    └── *.html                 # plataformas interativas de estruturas de dados
```

> 💡 O `.gitignore` do projeto ignora arquivos `*.exe`, para que os executáveis compilados não subam para o GitHub.

---

## 📏 Complexidade de algoritmos

A pasta `Complexidade/` explica de onde vêm os termos usados em todos os outros guias do repositório (`O(n)`, `O(n log n)`, melhor e pior caso, *in-place*...). Ela responde a uma pergunta central: **quanto um algoritmo "custa" quando o tamanho do problema cresce?**

| Arquivo | O que tem |
|---|---|
| `Guiacomplexidade.md` | Guia com os conceitos: por que analisar algoritmos, melhor/pior/caso médio, contagem de operações, notação assintótica (`O`, `Ω`, `Θ`), regras de simplificação, classes de complexidade, análise de código com 5 exemplos, algoritmos recursivos, complexidade de espaço e uma tabela com a complexidade de todos os algoritmos deste repositório |
| `complexidade.c` | Código em C que **conta operações** (em vez de medir segundos) de funções `O(1)`, `O(log n)`, `O(n)`, `O(n log n)`, `O(n²)` e `O(2^n)`, para você ver a "forma" do crescimento com `n = 10`, `100` e `1000` |

> 💡 Vale ler esse guia **antes** dos algoritmos de ordenação e de pesquisa: o resto do repositório usa esse vocabulário.

---

## 🔢 Algoritmos de ordenação

A pasta `Ordenacoes/` tem um guia, uma demonstração interativa e um código em C para cada um dos nove algoritmos abaixo.

### Resumo comparativo

| Algoritmo | Ideia em uma frase | Melhor caso | Caso médio | Pior caso | Memória extra | Estável |
|---|---|---|---|---|---|---|
| **Bubble Sort** | Compara vizinhos e troca os fora de ordem; o maior "sobe" até o fim a cada passada | O(n) | O(n²) | O(n²) | O(1) | Sim |
| **Insertion Sort** | Insere cada elemento na posição certa da parte já ordenada | O(n) | O(n²) | O(n²) | O(1) | Sim |
| **Selection Sort** | Seleciona o menor elemento restante e o coloca na posição | O(n²) | O(n²) | O(n²) | O(1) | Não |
| **Counting Sort** | Conta quantas vezes cada valor aparece | O(n + k) | O(n + k) | O(n + k) | O(n + k) | Sim |
| **Radix Sort** | Ordena dígito por dígito, do menos significativo ao mais | O(d·(n + b)) | O(d·(n + b)) | O(d·(n + b)) | O(n + b) | Sim |
| **Bucket Sort** | Espalha em faixas (baldes), ordena cada uma e junta | O(n + k) | O(n + k) | O(n²) | O(n + k) | Depende |
| **Merge Sort** | Divide ao meio, ordena cada metade e intercala | O(n log n) | O(n log n) | O(n log n) | O(n) | Sim |
| **Quick Sort** | Escolhe um pivô, separa menores e maiores, repete | O(n log n) | O(n log n) | O(n²) | O(log n) | Não |
| **Heap Sort** | Monta um heap e extrai o maior repetidamente | O(n log n) | O(n log n) | O(n log n) | O(1) | Não |

**Legenda:** *n* = quantidade de elementos · *k* = maior valor (ou número de baldes) · *d* = quantidade de dígitos · *b* = base numérica (ex.: 10).

### Como os algoritmos se agrupam

- **Simples, de O(n²):** Bubble Sort, Insertion Sort e Selection Sort. São fáceis de entender e ótimos para começar, mas lentos em listas grandes.
- **Dividir para conquistar, de O(n log n):** Merge Sort e Quick Sort. É a base do que as bibliotecas padrão usam.
- **Baseado em estrutura de dados:** Heap Sort, que usa uma árvore binária guardada em um array.
- **Sem comparar elementos:** Counting Sort, Radix Sort e Bucket Sort. Usam os próprios valores como índices e podem ser lineares, mas só funcionam em condições específicas (por exemplo, inteiros em um intervalo conhecido).

### O que tem em cada pasta de algoritmo

Cada guia segue o mesmo modelo, para facilitar a comparação entre eles (o do Bubble Sort inclui a parada antecipada, que o torna adaptável, com melhor caso O(n)):

1. **Como funciona**, com uma analogia do dia a dia;
2. **Exemplo passo a passo** com um array concreto;
3. **Características**: tempo, espaço, estabilidade, adaptabilidade e se é *online*;
4. **Vantagens e desvantagens**;
5. **Código em C**;
6. **Quando usar**;
7. **Resumo rápido**.

### Ordenação parcial

A pasta `Ordenacoes/OrdenacaoParcial/` resolve um problema diferente: em vez de ordenar os n elementos, queremos só os **k menores, já em ordem**, nas k primeiras posições (o "top-k"). O resto do array fica sem ordem. Ela tem o guia (`OrdenacaoParcial.md`), uma demonstração com uma aba para cada método (`Demo_ Ordenacao Parcial.html`) e o código em C (`OrdenacaoParcial.c`).

| Método | Ideia em uma frase | Tempo |
|---|---|---|
| **Seleção parcial** | Repete só k vezes o passo do Selection Sort | O(n·k) |
| **Inserção parcial** | Mantém os k primeiros ordenados; só entra quem for menor que o maior deles | O(n·k) no pior caso, O(n) no melhor |
| **Heapsort parcial** | Monta um min-heap e retira o menor k vezes | O(n + k·log n) |
| **Quicksort parcial** | Particiona como o Quick Sort, mas ignora os lados que não têm posições entre as k primeiras | O(n + k·log k) no caso médio |

A vantagem aparece quando **k é muito menor que n**. Quando k = n, vira ordenação completa.

---

## 🔍 Algoritmos de pesquisa

A pasta `Pesquisa/` reúne os dois algoritmos clássicos de busca de um valor em um array. Cada um tem um guia (`.md`), uma demonstração interativa (`.html`) e um código em C (`.c`), no mesmo modelo dos guias de ordenação (analogia, exemplo passo a passo, complexidade, quando usar).

| Algoritmo | Ideia em uma frase | Melhor caso | Caso médio | Pior caso | Memória extra | Precisa de dados ordenados? |
|---|---|---|---|---|---|---|
| **Pesquisa Sequencial** | Olha os elementos um a um, do início ao fim | O(1) | O(n) | O(n) | O(1) | Não |
| **Pesquisa Binária** | Olha o elemento do meio e descarta metade a cada passo | O(1) | O(log n) | O(log n) | O(1) iterativa · O(log n) recursiva | **Sim** |

### O que tem em cada pasta

| Pasta | Guia | Demonstração | Código |
|---|---|---|---|
| `PesquisaSequencial/` | `GuiaPesquisaSequencial.md`: analogia do chaveiro, exemplo, variações (sentinela, em array ordenado, mover para a frente, transposição) e comparação com a binária | `Demo_ Pesquisa Sequencial.html`: percorre o array posição por posição até achar o valor ou chegar ao fim | `PesquisaSequencial.c`: pesquisa sequencial com contador de comparações e a **versão com sentinela** |
| `PesquisaBinaria/` | `GuiaPesquisaBinaria.md`: analogia da lista telefônica, exemplos com valor encontrado e não encontrado, pré-requisitos e elementos repetidos | `Demo_ Pesquisa Binaria.html`: mostra `esq`, `meio` e `dir` e a metade descartada a cada passo | `PesquisaBinaria.c`: versão **iterativa** (com contador de passos) e versão **recursiva** |

### Sequencial × Binária

| | Sequencial | Binária |
|---|---|---|
| Dados | qualquer ordem | **precisam estar ordenados** |
| Estrutura | array ou lista encadeada | precisa de acesso direto (array) |
| 1.000.000 de elementos (pior caso) | 1.000.000 comparações | cerca de 20 comparações |
| Quando usar | dados desordenados, poucos elementos ou lista encadeada | dados ordenados e muitas buscas |

> 💡 A pesquisa binária depende de ordenação: por isso o estudo de **ordenação** vem antes no roteiro.

---

## 🧱 Estruturas de dados

As pastas `LIsta/`, `Fila/`, `Pilha/` e `CelulaEstrutura/` reúnem códigos em C que mostram, uma operação por arquivo, como cada estrutura é construída. A **matriz flexível** e a **árvore binária de pesquisa**, que também são feitas de células com ponteiros, têm seções próprias logo abaixo, cada uma com guia, demonstração e código.

### Conceito central: a célula

Nas estruturas encadeadas, cada elemento fica dentro de uma **célula** (também chamada de nó), que guarda o valor e o endereço da próxima célula:

```c
typedef struct Celula {
    int elemento;          // o dado guardado
    struct Celula *prox;   // ponteiro para a próxima célula
} Celula;
```

Na versão **dupla**, a célula também guarda o endereço da anterior (`ant`), o que permite andar nos dois sentidos. A pasta `CelulaEstrutura/` traz a célula simples, a célula dupla e a célula com cabeça.

### Listas (`LIsta/`)

| Pasta | Como armazena | Exemplos de operações |
|---|---|---|
| `LIstaSimples` | Vetor (array) de tamanho fixo | inserir, remover e mostrar elementos |
| `LIstaFlexivel` | Vetor alocado dinamicamente (cresce e diminui) | inserir/remover no início e no final, remover por valor |
| `ListaEncadeada` | Células ligadas por ponteiros | inserir, remover do início, do final e de uma posição |
| `ListaDuplaEncadeada` | Células com ponteiro para a próxima e a anterior | remover do primeiro e do último |

### Filas (`Fila/`)

Uma fila segue a regra **FIFO** (*First In, First Out*): o primeiro que entra é o primeiro que sai.

| Pasta | Como armazena | Exemplos de operações |
|---|---|---|
| `FilaEncadeadaNormal` | Células ligadas | inserir e remover |
| `FIlaDuplamenteEncadeada` | Células duplas | inserir e remover |
| `FilaCircular` | Vetor circular com uma posição extra de segurança; os índices "dão a volta" com `% (MAX + 1)` | inicializar, inserir, remover e mostrar |

### Pilhas (`Pilha/`)

Uma pilha segue a regra **LIFO** (*Last In, First Out*): o último que entra é o primeiro que sai, como uma pilha de pratos.

| Arquivo | Operação | O que faz |
|---|---|---|
| `PilhaInserir.c` | `empilhar` | cria uma célula nova e a coloca no **topo** |
| `PilhaRemover.c` | `desempilhar` | remove a célula do **topo** e avisa `erro` se a pilha estiver vazia |

A pilha é feita com células encadeadas e, diferente da fila, só precisa guardar o ponteiro `topo`:

```c
void empilhar(Celula **topo) {
    // ... lê o valor x e cria a célula nova
    nova->prox = (*topo);   // a nova célula aponta para o antigo topo
    (*topo) = nova;         // e passa a ser o topo
}
```

**Fila × Pilha:**

| | Fila | Pilha |
|---|---|---|
| Regra | FIFO (primeiro a entrar, primeiro a sair) | LIFO (último a entrar, primeiro a sair) |
| Onde entra | no final | no topo |
| Onde sai | no início | no topo |
| Ponteiros guardados | `primeiro` e `ultimo` | só o `topo` |
| Exemplo do dia a dia | fila de banco | pilha de pratos, botão "desfazer" |

### Qual escolher?

| Estrutura | Vantagem | Desvantagem |
|---|---|---|
| Vetor (lista simples) | Acesso direto a qualquer posição | Tamanho fixo; inserir no meio exige deslocar elementos |
| Vetor dinâmico (lista flexível) | Cresce conforme a necessidade | Realocar memória tem custo |
| Lista encadeada | Insere e remove sem deslocar elementos | Não há acesso direto; gasta memória com ponteiros |
| Lista dupla | Anda nos dois sentidos; remover o último é simples | Mais ponteiros para cuidar |
| Fila circular | Reaproveita o espaço liberado | Precisa controlar bem os índices |
| Pilha encadeada | Empilhar e desempilhar são simples e rápidos, sempre no topo | Só dá acesso ao elemento do topo |

---

## 🔲 Matriz flexível

A pasta `MatrizFlexivel/` leva a ideia da célula para **duas dimensões**. Em vez de um bloco contínuo de memória (`int m[3][3]`), cada elemento é uma célula alocada separadamente e ligada às quatro vizinhas. Essa estrutura também aparece com os nomes de matriz dinamicamente encadeada e **lista ortogonal**.

```c
typedef struct Celula {
    int elemento;
    struct Celula *esq, *dir, *sup, *inf;   // vizinhas: esquerda, direita, cima e baixo
} Celula;
```

Um ponteiro `inicio` guarda a célula `[0][0]`. Para chegar à posição `(i, j)`, o código anda `i` vezes por `inf` e `j` vezes por `dir`.

| Arquivo | O que tem |
|---|---|
| `guia_completo_matriz_flex_vel.md` | Guia com a analogia da malha urbana (cada cruzamento liga norte, sul, leste e oeste), a estrutura da célula, complexidade, vantagens, desvantagens e quando usar |
| `demonstra_o_interativa_matriz_flex_vel.html` | Demonstração animada com os botões **+ Adicionar Linha**, **+ Adicionar Coluna**, **Aleatorizar Valores** e **Reset**. Tem controle de velocidade, abas com o código de `adicionarLinha()` e `adicionarColuna()` e mensagens que descrevem cada ponteiro sendo ligado |
| `MatrizFlexivel.c` | Código em C com `novaCelula`, `criarMatriz(linhas, colunas)`, `inserir(inicio, linha, coluna, elemento)` e `imprimir`. O `main` lê as dimensões e depois os valores |

| Operação | Custo | Por quê |
|---|---|---|
| Acessar a posição `(i, j)` | O(N + M) | Não há cálculo de endereço como no array: é preciso caminhar pelas células |
| Adicionar linha ou coluna | O(M) ou O(N) | Percorre a última linha (ou coluna) ligando os ponteiros um a um |
| Memória | O(N × M) | Mas com 4 ponteiros extras por elemento |

(*N* = número de linhas, *M* = número de colunas.)

**Vantagem:** cresce em tempo de execução, e inserir no meio só exige religar ponteiros. **Desvantagem:** gasta muito mais memória que um array 2D e o acesso é mais lento. Na prática, a ideia serve de base para **matrizes esparsas**.

---

## 🌳 Árvore binária de pesquisa

A pasta `Arvore/ArvoreBinariadePesquisa/` apresenta a **árvore binária de pesquisa** (*Binary Search Tree*, BST): uma estrutura hierárquica em que cada nó tem no máximo dois filhos. Diferente das listas, ela não é linear, e isso permite buscar, inserir e remover sem varrer todos os elementos.

A regra que define a BST: para qualquer nó, os valores da **subárvore esquerda são menores** e os da **subárvore direita são maiores**.

```c
typedef struct Arvore {
    int elemento;
    struct Arvore *esq, *dir;   // filho esquerdo (menores) e direito (maiores)
} Arvore;
```

| Arquivo | O que tem |
|---|---|
| `guia_completo_rvore_bin_ria_de_pesquisa.md` | Guia com a analogia do jogo de adivinhação, complexidade de tempo e de espaço, vantagens, desvantagens, um exemplo clássico em C (inserir e buscar) e quando usar |
| `arvore_bin_ria_de_pesquisa.html` | Demonstração animada: digite um valor e use **Inserir**, **Pesquisar** ou **Remover**; **Limpar Árvore** recomeça. Tem controle de velocidade, abas com o código de cada operação e a caixa **Status da Execução**, que narra cada comparação. A remoção mostra o caso do nó com dois filhos, trocado pelo sucessor |
| `Arvore.c` | Código em C com `novoNo`, `inserir` (recursiva, valores repetidos são ignorados) e `imprimir` (em ordem). O `main` lê números até o fim da entrada, monta a árvore e imprime os valores já ordenados |

| Característica | Valor |
|---|---|
| Buscar, inserir e remover (árvore balanceada) | O(log n) |
| Buscar, inserir e remover (pior caso) | O(n): acontece quando os valores entram já ordenados e a árvore vira uma "linha reta" |
| Memória | O(n): cada nó guarda o dado e dois ponteiros |
| Percurso **em ordem** (esquerda, nó, direita) | Visita os valores do menor para o maior, sem precisar de um algoritmo de ordenação |

**Ligações com o resto do repositório:**

- é a mesma lógica da **pesquisa binária**, só que com os dados em nós ligados por ponteiros, o que torna inserir e remover baratos (no array ordenado seria preciso deslocar elementos);
- usa **recursão** e **alocação dinâmica**, como o Merge Sort e as listas encadeadas;
- o **Heap Sort** também usa uma árvore binária, mas guardada em um array.

---

## 🔬 Pasta Estudos

A pasta `Estudos/` guarda materiais extras:

- **`FIlaCircularEstudos/`**: um texto (`Filacircular.md`) que explica a fila circular com alocação dinâmica em C, e uma demonstração interativa sobre a **fila circular com espaço de segurança**.
- **Plataformas interativas**: páginas HTML que reúnem animações de algoritmos e de estruturas de dados (versões em C e Java).
- **`image.png`**: imagem de apoio para os estudos.

---

## 🎮 Como usar as demonstrações

As demonstrações de **Counting, Radix, Bucket, Quick, Heap e Bubble Sort**, da **ordenação parcial** e das **pesquisas sequencial e binária** funcionam assim:

1. **Digite seus números**, separados por vírgula (de 2 a 12 números), ou clique em **Sortear**.
2. Clique em **Aplicar** para carregar.
3. Nas pesquisas, preencha também o campo **Valor procurado** (a pesquisa binária coloca os números em ordem crescente sozinha, porque exige array ordenado). Na ordenação parcial, escolha o método na aba e preencha o campo **Quantidade k** (de 1 até a quantidade de números).
4. Use **Próximo passo** e **Voltar** para andar quadro a quadro, ou **Reproduzir** para ver a animação sozinha. A barra de **Velocidade** controla o ritmo.
5. Leia a frase abaixo da animação: ela explica o que acabou de acontecer.

**Valores aceitos:** Counting Sort, de 0 a 15 · Radix Sort, de 0 a 999 · Bucket, Quick, Heap e Bubble Sort, ordenação parcial e as duas pesquisas, de 0 a 99.

**O que cada cor significa** (nas demonstrações de Quick, Heap e Bubble Sort, da ordenação parcial e das pesquisas):

- **Azul-petróleo:** pivô (Quick), filho maior / posição da troca (Heap), par que acabou de trocar (Bubble) ou elemento do meio (Pesquisa Binária);
- **Âmbar:** elemento sendo comparado ou nó atual;
- **Verde:** elemento já na posição final ou valor encontrado;
- **Sublinhado:** as k primeiras posições, onde ficam os k menores (ordenação parcial);
- **Esmaecido:** fora do trecho atual (Quick), já verificado (Pesquisa Sequencial) ou metade já descartada (Pesquisa Binária).

**Demonstrações de estruturas de dados (Árvore e Matriz Flexível):** funcionam com botões em vez de uma lista de números.

- **Árvore binária de pesquisa:** digite um valor no campo e clique em **Inserir**, **Pesquisar** ou **Remover**. A barra **Velocidade** controla a animação e **Limpar Árvore** esvazia tudo. A área de desenho mostra até 4 níveis.
- **Matriz flexível:** use **+ Adicionar Linha** e **+ Adicionar Coluna** para ver os ponteiros sendo ligados, **Aleatorizar Valores** para preencher as células e **Reset** para recomeçar.
- Nas duas, a caixa de **Status** explica cada passo, e as abas de código mostram a função correspondente em C.

> As demonstrações são arquivos HTML independentes. Basta dar dois cliques no arquivo para abrir no navegador. Algumas usam fontes e bibliotecas da internet, então precisam de conexão.

---

## ⚙️ Como compilar e executar os códigos em C

### O que você precisa

Um compilador C, como o **GCC**:

- **Linux:** `sudo apt install build-essential`
- **macOS:** `xcode-select --install`
- **Windows:** instale o [MinGW-w64](https://www.mingw-w64.org/) ou use o WSL

### Compilando e rodando

```bash
# exemplo com o Quick Sort
gcc -Wall -o quicksort Ordenacoes/Quick/Quicksort.c
./quicksort          # no Windows: quicksort.exe
```

A flag `-Wall` ativa os avisos do compilador, o que ajuda a achar erros cedo.

### Observações importantes

- **Arquivos com `main`:** a maioria dos códigos de listas, filas, pilhas, células, de ordenação (como o `Bubblesort.c`), de pesquisa (`PesquisaSequencial.c` e `PesquisaBinaria.c`), o `Arvore.c`, o `MatrizFlexivel.c` e o `complexidade.c` já vêm com `main` e rodam direto.
- **Arquivos só com a função:** alguns códigos de ordenação (como `insercao.c`, `selecao.c` e `countingsort.c`) trazem apenas a função do algoritmo. Para testá-los, escreva um `main` que crie um array e chame a função, ou copie a função para um arquivo seu.
- **Entrada de dados:** vários códigos de listas e filas leem números com `scanf`. Digite os valores e termine a entrada com **Ctrl + D** (Linux e macOS) ou **Ctrl + Z** e Enter (Windows).
- **Formato da entrada na fila encadeada e na pilha:** digite os números da primeira linha separados por espaço e **termine a sequência com uma letra** (por exemplo, `10 20 30 x`). Nos arquivos que inserem um valor, digite-o na linha seguinte (por exemplo, `40`).
- **Árvore e matriz flexível:** o `Arvore.c` lê números até o fim da entrada e imprime a árvore em ordem; o `MatrizFlexivel.c` lê primeiro as dimensões (`linhas colunas`) e depois os valores. Dá para testar sem digitar, usando um pipe:

  ```bash
  gcc -Wall -o arvore Arvore/ArvoreBinariadePesquisa/Arvore.c
  echo "50 30 70 20 40 60 80" | ./arvore        # imprime: 20 30 40 50 60 70 80

  gcc -Wall -o matriz MatrizFlexivel/MatrizFlexivel.c
  printf "2 3\n1 2 3\n4 5 6\n" | ./matriz        # imprime a matriz 2x3
  ```

- **Um programa por arquivo:** cada `.c` tem o seu próprio `main`, então compile um arquivo de cada vez.

---

## 🧩 Como funciona o `index.html`

O `index.html` **não é escrito à mão**: ele é gerado pelo script `gerar_index.py`, que lê todas as pastas do repositório e coloca o conteúdo (guias, demonstrações, códigos e imagens) dentro de um único arquivo. Isso faz com que o índice funcione em qualquer lugar, sem servidor.

### Atualizando o índice

Sempre que adicionar, renomear ou editar arquivos, rode na raiz do repositório:

```bash
python gerar_index.py
```

Você só precisa do **Python 3** (nenhuma biblioteca extra).

### Personalizando

No topo do `gerar_index.py` há uma área de configuração:

| Variável | O que muda |
|---|---|
| `TITULO` e `DESCRICAO` | Título e texto da página inicial |
| `NOMES_PASTAS` | Nome exibido para cada pasta |
| `NOMES_ARQUIVOS` | Nome exibido para cada arquivo |
| `ORDEM_PASTAS` | Ordem em que as pastas aparecem |
| `IGNORAR_PASTAS` e `IGNORAR_ARQUIVOS` | O que não entra no índice |

Pastas e arquivos que começam com ponto (como `.vscode`) são ignorados automaticamente.

> 🌐 Os guias usam bibliotecas da internet para exibir fórmulas e colorir o código. Sem conexão, o conteúdo aparece em texto simples, mas continua legível.

---

## 🚀 Publicar no GitHub Pages (opcional)

O GitHub não executa páginas HTML dentro da visualização de arquivos, mas você pode publicar o `index.html` como um site gratuito:

1. No repositório, vá em **Settings → Pages**.
2. Em **Source**, escolha **Deploy from a branch**.
3. Selecione a branch `main` e a pasta `/ (root)`, e salve.
4. Após alguns minutos, o site estará em `https://SEU-USUARIO.github.io/NOME-DO-REPOSITORIO/`.

---

## 🎓 Sugestão de roteiro de estudo

Uma ordem que vai do mais simples ao mais avançado:

1. **Complexidade:** o vocabulário (`O`, melhor e pior caso) usado em todos os guias.
2. **Bubble, Insertion e Selection Sort:** a lógica básica de ordenar.
3. **Merge Sort e Quick Sort:** a estratégia de dividir para conquistar e a recursão.
4. **Heap Sort:** uma estrutura de dados (o heap) a serviço da ordenação.
5. **Counting, Radix e Bucket Sort:** como ordenar sem comparar elementos.
6. **Pesquisa sequencial e binária:** como achar um valor, e por que ter os dados ordenados faz diferença.
7. **Células, listas, filas e pilhas:** ponteiros, alocação dinâmica e estruturas encadeadas.
8. **Matriz flexível:** a célula ganha quatro ponteiros e a estrutura passa a ter duas dimensões.
9. **Árvore binária de pesquisa:** une recursão, ponteiros e a lógica da pesquisa binária.
10. **Fila circular e materiais da pasta Estudos:** aprofundamento.
11. **Exercícios:** pratique no [repositório de exercícios](https://github.com/Cardoso-G-Ao/Exercicios-Estudos-Aeds-2-), que segue a mesma ordem de assuntos deste.

**Dica de estudo para cada algoritmo:**

1. Leia o **guia** até a seção do exemplo passo a passo.
2. Abra a **demonstração** e rode com o mesmo array do guia, conferindo cada passo.
3. Rode com **números seus** e tente prever o próximo passo antes de clicar.
4. Compile o **código em C** e tente reescrevê-lo sem olhar.

---

## 🏋️ Repositório de exercícios

Estudar só lendo não basta para fixar estruturas de dados. Por isso existe um repositório separado, só de prática:

**👉 [Exercicios-Estudos-Aeds-2-](https://github.com/Cardoso-G-Ao/Exercicios-Estudos-Aeds-2-)**

| Repositório | Papel | O que tem |
|---|---|---|
| **Estudos-Aeds-2** (este) | Teoria e referência | Guias (`.md`), demonstrações (`.html`) e códigos em C |
| [**Exercicios-Estudos-Aeds-2-**](https://github.com/Cardoso-G-Ao/Exercicios-Estudos-Aeds-2-) | Prática | Listas de exercícios (PDF) em dois níveis, básico e intermediário, e soluções em C |

Os exercícios seguem a mesma ordem deste repositório (**células → listas → filas → pilha → ordenações**) e usam os mesmos arquivos e nomes (`Celula.c`, `LIstaFlexivel.c`, `testefilacircular.c`, `MAX`, `ant` e assim por diante).

Fluxo sugerido:

1. Estude o assunto aqui (guia, demonstração e código).
2. Resolva os exercícios daquele assunto no repositório de exercícios.
3. Volte e confira o resultado nas demonstrações interativas.

---

## 📝 Resumo

- **9 algoritmos de ordenação**, cada um com guia, demonstração interativa e código em C.
- **2 algoritmos de pesquisa** (sequencial e binária), também com guia, demonstração interativa e código em C.
- **Guia de complexidade** de algoritmos, com um código em C que conta operações.
- **Listas, filas, pilhas e células** em C, com uma operação por arquivo.
- **Matriz flexível** (lista ortogonal), com guia, demonstração interativa e código em C.
- **Árvore binária de pesquisa**, com guia, demonstração interativa (inserir, pesquisar e remover) e código em C.
- **Materiais extras** na pasta `Estudos/`.
- **Repositório de exercícios** complementar: [Exercicios-Estudos-Aeds-2-](https://github.com/Cardoso-G-Ao/Exercicios-Estudos-Aeds-2-).
- **`index.html`** para navegar por tudo, gerado por `gerar_index.py`.
- Tudo pensado para **estudar por três caminhos**: ler, ver e programar.

---

## 👤 Autor

**Gabriel Cardoso Alvares de Oliveira**

Autor deste repositório de estudos e do [repositório de exercícios](https://github.com/Cardoso-G-Ao/Exercicios-Estudos-Aeds-2-) que o complementa.