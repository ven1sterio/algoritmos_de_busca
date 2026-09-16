# Busca em Espaço de Estados — BFS, DFS e Custo Uniforme

Implementação em C++ de três algoritmos de busca clássicos, aplicados a um
espaço de estados representado como uma grade `N x M`. O estado inicial e o
estado final são sorteados aleatoriamente a cada execução.

Contexto: mundo do aspirador de pó (Russell & Norvig), com duas casas.
Rodando com `N=1 M=2` o programa reproduz exatamente esse cenário; com
grades maiores dá para observar o comportamento de cada algoritmo.

## Arquivos

| Arquivo | Algoritmo | Estrutura de dados da fronteira |
|---|---|---|
| `BFS.cpp` | Busca em largura | Fila (FIFO) |
| `DFS.cpp` | Busca em profundidade | Pilha (recursão) |
| `Dijkstra.cpp` | Busca de custo uniforme | Fila de prioridade (min-heap) |

## Como compilar e rodar

Cada arquivo é independente:

```bash
g++ -std=c++17 -O2 BFS.cpp -o bfs
./bfs
```

```bash
g++ -std=c++17 -O2 DFS.cpp -o dfs
./dfs
```

```bash
g++ -std=c++17 -O2 Dijkstra.cpp -o dijkstra
./dijkstra
```

Em todos os casos, o programa pede duas dimensões pela entrada padrão:

```
10 10
```

Sugestões de entrada:
- `1 2` — reproduz o mundo do aspirador com duas casas
- `10 10` — bom tamanho para visualizar a busca acontecendo

## O que cada algoritmo imprime

- `S` — estado inicial
- `E` — estado final
- `#` — estado expandido durante a busca
- `X` — estado final alcançado (BFS/DFS)

O `Dijkstra.cpp` também sorteia um custo de 1 a 9 para cada célula, imprime
a matriz de custos antes da busca, e ao final reconstrói e imprime o
caminho de menor custo total.

## Legenda rápida por arquivo

**BFS.cpp** — expande por camadas (nível de profundidade). Encontra o
caminho com o menor número de passos.

**DFS.cpp** — desce por um ramo até o fim antes de voltar (backtracking via
recursão). Não garante o caminho mais curto.

**Dijkstra.cpp** — expande sempre o estado de menor custo acumulado
(`dist`), com relaxamento de distâncias. Reduz-se ao BFS quando todos os
custos são iguais.
