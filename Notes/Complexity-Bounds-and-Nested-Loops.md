# Asymptotic Bounds: O, Ω and Θ

## Time complexity
Time complexity describes how the running time `T(n)` grows with input size `n`, ignoring constant factors and small inputs.

## The three notations
| Notation | Bound | Formal meaning (for all n ≥ n₀) | Reads as |
|---|---|---|---|
| `T(n) = O(f(n))` | Upper | `T(n) ≤ c·f(n)` | grows no faster than f |
| `T(n) = Ω(f(n))` | Lower | `T(n) ≥ c·f(n)` | grows no slower than f |
| `T(n) = Θ(f(n))` | Tight | `c₁·f(n) ≤ T(n) ≤ c₂·f(n)` | grows like f |

`Θ` holds exactly when both `O` and `Ω` hold.

Example: `T(n) = 3n² + 5n + 20`. For `n ≥ 10`, `3n² ≤ T(n) ≤ 4n²`, so `T(n) = Θ(n²)` (and therefore also `O(n²)` and `Ω(n²)`).

## Best and worst case: linear search
* Best case (key at index 0): Θ(1).
* Worst case (key last or missing): exactly `n` comparisons, Θ(n).
* Overall the running time is O(n) and Ω(1).

## Common growth rates
`1 < log n < √n < n < n log n < n² < n³ < 2ⁿ < n!`

## Dependent nested loop
```c
for (int i = 1; i <= n; i++)
    for (int j = 1; j <= i; j++)
        s++;
```
For a fixed `i` the inner loop runs `i` times, so `s++` runs

```
1 + 2 + ... + n = n(n+1)/2
```

Derivation: write `S = 1 + 2 + ... + n` and `S = n + (n-1) + ... + 1`; adding term by term gives `2S = n(n+1)`.

`n(n+1)/2 = n²/2 + n/2`, and the dominant term is `n²/2`, so the loop is **Θ(n²)**.

Counting the loop overhead as well (outer test `n+1` times, inner tests `Σ(i+1)`) only adds lower-order terms, so the result stays Θ(n²).
