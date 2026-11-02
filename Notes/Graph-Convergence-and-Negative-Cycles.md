# Convergence, Divergence and Cycles in Shortest-Path Algorithms

## Convergence and divergence (directed graphs)
* **Convergence:** several edges enter one vertex (`A→C`, `B→C`, `D→C`). C has a high in-degree.
* **Divergence:** one vertex sends edges to several vertices (`A→B`, `A→C`, `A→D`). A has a high out-degree.

In shortest-path algorithms the word "converge" is also used for distance estimates that stop changing. Bellman–Ford converges after at most `V−1` rounds when there is no negative cycle; with a negative cycle the estimates keep decreasing (they diverge).

## Cycles
* A **cycle** is a path that starts and ends at the same vertex.
* A **negative cycle** is a cycle whose edge weights add to a negative number. Going round it again always makes a path cheaper, so a shortest path through it does not exist.

## Which algorithm handles what
| Algorithm | Negative edges | Detects negative cycle | Graph type | Time |
|---|---|---|---|---|
| BFS | No (unweighted) | No | any | O(V+E) |
| Dijkstra | No | No | non-negative weights | O((V+E) log V) |
| Bellman–Ford | Yes | Yes (V-th round still relaxes) | directed | O(V·E) |
| Floyd–Warshall | Yes | Yes (`dist[i][i] < 0`) | all pairs | O(V³) |
| DAG shortest path | Yes | Not needed (no cycles) | DAG only | O(V+E) |
| DFS | – | Detects any cycle (back edge) | any | O(V+E) |

## Summary
* Ordinary cycle detection: DFS (back edge) or topological sort failing.
* Negative-cycle detection: Bellman–Ford or Floyd–Warshall.
* Negative edges without negative cycles: Bellman–Ford, Floyd–Warshall, Johnson's algorithm, or the DAG method.
* Dijkstra must not be used when any edge is negative.
