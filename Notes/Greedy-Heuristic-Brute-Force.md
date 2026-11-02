# Greedy vs Heuristic vs Brute Force

## Brute force
Try every possible candidate and keep the best (or the one that matches).
* Always correct if the search is complete.
* Usually exponential or factorial time, so only usable for small inputs.
* Examples: trying every 3-letter password `aaa, aab, …, zzz` (26³ = 17,576 tries); linear search in an unsorted list; checking all `n!` tours in the travelling salesman problem.

## Greedy
Build the answer step by step, always taking the choice that looks best right now, and never undoing it.
* Fast and simple.
* Optimal only when the problem has the greedy-choice property, which has to be proved.
* Optimal examples: Dijkstra (non-negative weights), Prim, Kruskal, Huffman coding, activity selection, fractional knapsack.
* Not optimal: coin change with coins {1, 3, 4} and amount 6 (greedy gives 4+1+1, best is 3+3); 0/1 knapsack.

## Heuristic
Use a rule of thumb to reach a good answer quickly, with no guarantee of the best answer.
* Used when exact methods are too slow (NP-hard problems).
* Examples: nearest-neighbour tour for TSP; A* search guided by an estimate (it is exact only when the heuristic never overestimates); hill climbing; genetic algorithms.

## Side-by-side
| | Brute force | Greedy | Heuristic |
|---|---|---|---|
| Idea | Check everything | Best local choice each step | Rule of thumb / estimate |
| Optimal? | Always | Only for some problems | Not guaranteed |
| Speed | Slowest | Fast | Fast |
| Typical use | Small inputs, checking answers | Problems with a greedy proof | Hard problems, large inputs |

Note: every greedy algorithm can be seen as a heuristic, but when a greedy rule is proven optimal it is treated as an exact algorithm.
