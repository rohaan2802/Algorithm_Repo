# Matrix Chain Multiplication

## Problem
Given matrices `A1 … An` where `Ai` has size `p[i−1] × p[i]`, choose the parenthesisation that minimises the number of scalar multiplications. Matrix multiplication is associative, so every order gives the same product, but costs differ a lot. Multiplying a `p × q` matrix by a `q × r` matrix costs `p·q·r`.

## Example
A1 = 5×10, A2 = 10×3, A3 = 3×12, A4 = 12×5, so `p = [5, 10, 3, 12, 5]`.

## Recurrence
```
m[i][i] = 0
m[i][j] = min over i <= k < j of ( m[i][k] + m[k+1][j] + p[i-1]·p[k]·p[j] )
s[i][j] = the k that gives the minimum
```
Fill by chain length L = 2, 3, …, n (diagonal by diagonal). Time Θ(n³), space Θ(n²).

## Every computation
| Cell | k | m[i][k] + m[k+1][j] + cost | Total |
|---|---|---|---|
| m[1][2] | 1 | 0 + 0 + 5·10·3 | 150 |
| m[2][3] | 2 | 0 + 0 + 10·3·12 | 360 |
| m[3][4] | 3 | 0 + 0 + 3·12·5 | 180 |
| m[1][3] | 1 | 0 + 360 + 5·10·12 | 960 |
| m[1][3] | 2 | 150 + 0 + 5·3·12 | 330 |
| m[2][4] | 2 | 0 + 180 + 10·3·5 | 330 |
| m[2][4] | 3 | 360 + 0 + 10·12·5 | 960 |
| m[1][4] | 1 | 0 + 330 + 5·10·5 | 580 |
| m[1][4] | 2 | 150 + 180 + 5·3·5 | 405 |
| m[1][4] | 3 | 330 + 0 + 5·12·5 | 630 |

## Final tables
Cost table `m`:

| i \ j | 1 | 2 | 3 | 4 |
|---|---|---|---|---|
| 1 | 0 | 150 | 330 | 405 |
| 2 | – | 0 | 360 | 330 |
| 3 | – | – | 0 | 180 |
| 4 | – | – | – | 0 |

Split table `s`:

| i \ j | 2 | 3 | 4 |
|---|---|---|---|
| 1 | 1 | 2 | 2 |
| 2 | – | 2 | 2 |
| 3 | – | – | 3 |

Minimum cost: **405** scalar multiplications.

Optimal order: **((A1A2)(A3A4))**.

Reading it from `s`: `s[1][4] = 2` splits the chain into `A1..A2` and `A3..A4`; then use `s` again on each half.

## Quick rule for filling a cell
For cell `m[i][j]`:
1. Pair cells from **row i going right** (`m[i][i], m[i][i+1], …`) with cells from **column j going down** (`m[i+1][j], m[i+2][j], …`). Each pair is one split `k`.
2. To each pair add `p[i−1] · p[k] · p[j]`: the first and last dimensions of the chain stay fixed, only the middle `p[k]` changes.
3. Write the smallest sum, and its `k` in `s[i][j]`.

The diagonal is all zeros, the table is filled one diagonal at a time, and the answer is the top-right cell.

## Subproblems for n = 4
* Length 2: A1A2, A2A3, A3A4
* Length 3: A1A2A3, A2A3A4
* Length 4: A1A2A3A4
