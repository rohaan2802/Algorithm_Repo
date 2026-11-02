# Shortest Paths with Negative Edge Weights

Dijkstra fails when an edge is negative, because it finalises a vertex before a later negative edge could make it cheaper.

## Bellman–Ford (single source)
1. `d[source] = 0`, every other `d[v] = ∞`.
2. Repeat `V − 1` times: for every edge `(u, v, w)`, if `d[u] + w < d[v]` set `d[v] = d[u] + w`.
3. One more pass: if any edge can still be relaxed, a negative cycle is reachable from the source.

Why `V − 1`: a shortest simple path has at most `V − 1` edges, and round `k` fixes every path of `k` edges.

Time O(V·E).

Example: `A→B (4)`, `A→C (5)`, `B→C (−3)`, source `A`.

| Round | d[A] | d[B] | d[C] |
|---|---|---|---|
| start | 0 | ∞ | ∞ |
| 1 | 0 | 4 | min(5, 4 − 3) = 1 |
| 2 | 0 | 4 | 1 (no change) |

Shortest path to C is A→B→C with cost 1. Dijkstra would have fixed C at 5.

## Floyd–Warshall (all pairs)
```
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])   for k = 1..V, all i, j
```
Time O(V³). A negative value on the diagonal (`dist[i][i] < 0`) means vertex `i` is on a negative cycle.

## Johnson's algorithm (all pairs, sparse graphs)
Add a new vertex joined to every vertex with weight 0, run Bellman–Ford to get potentials `h(v)`, reweight every edge as `w'(u,v) = w(u,v) + h(u) − h(v)` (now non-negative), then run Dijkstra from each vertex. Time O(V·E log V).

## Shortest paths in a DAG
Topologically sort the vertices and relax outgoing edges in that order. Works with negative edges (a DAG has no cycles). Time O(V + E).

## Summary
| Algorithm | Problem | Negative edges | Negative cycle |
|---|---|---|---|
| Bellman–Ford | single source | yes | detects |
| Floyd–Warshall | all pairs | yes | detects |
| Johnson | all pairs | yes | detects (via Bellman–Ford) |
| DAG relaxation | single source, DAG | yes | cannot occur |
| Dijkstra | single source | **no** | – |
