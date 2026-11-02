# 0/1 Knapsack (Dynamic Programming)

## Problem
There are `n` items. Item `i` has weight `w[i]` and value `v[i]`. A knapsack holds at most `W` weight. Each item is either taken whole or left out (that is the "0/1"). Pick items so the total weight is at most `W` and the total value is as large as possible.

## State and recurrence
`dp[i][c]` = best value using only the first `i` items with capacity `c`.

```
dp[0][c] = 0,  dp[i][0] = 0
dp[i][c] = dp[i-1][c]                                   if w[i] > c
dp[i][c] = max(dp[i-1][c], v[i] + dp[i-1][c - w[i]])    if w[i] <= c
```

Running time Θ(n·W), space Θ(n·W) (Θ(W) with a single row filled right to left).

## Worked example
Weights `[1, 3, 4, 5]`, values `[1, 4, 5, 7]`, capacity `W = 7`.

| Item \ Capacity | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| none | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 (w=1, v=1) | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| 2 (w=3, v=4) | 0 | 1 | 1 | 4 | 5 | 5 | 5 | 5 |
| 3 (w=4, v=5) | 0 | 1 | 1 | 4 | 5 | 6 | 6 | 9 |
| 4 (w=5, v=7) | 0 | 1 | 1 | 4 | 5 | 7 | 8 | 9 |

Answer: `dp[4][7] = 9`, taking items [2, 3] (weights [3, 4]).

## Quick rule for filling a cell (like the LCS rule)
For row `i` and column `c`:
1. Copy the cell directly **above** (item not taken).
2. If the item fits, go up one row and **left by `w[i]` columns**, add `v[i]`.
3. Write the larger of the two.

So each cell only looks at two cells in the previous row: straight up, and up-and-left by the item's weight. The rule always works because it is exactly the recurrence.

## Tracing back the chosen items
Start at `dp[n][W]`. If the value equals the cell above, item `i` was not taken; move up. Otherwise item `i` was taken; move up and left by `w[i]`. Stop at row 0.
