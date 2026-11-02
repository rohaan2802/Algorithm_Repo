# O(√n) Time Complexity

An O(√n) algorithm does about √n steps: n = 100 → 10 steps, n = 10,000 → 100 steps, n = 10⁶ → 1,000 steps. It is faster than O(n) and slower than O(log n).

## Why √n appears
If `n = a × b`, then at least one of `a`, `b` is ≤ √n. So searching for a divisor only needs to go up to √n. Loops of the form `for (i = 1; i * i <= n; i++)` run about √n times.

## Example 1: primality test
```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}
```
Dry run, `n = 37`: `i = 2, 3, 4, 5, 6` (since 7·7 = 49 > 37), no divisor found → prime. Five checks instead of 35.

## Example 2: printing all divisors
```cpp
for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
        cout << i << " ";
        if (i != n / i) cout << n / i << " ";
    }
}
```
For `n = 36`: i = 1 → 1, 36; 2 → 2, 18; 3 → 3, 12; 4 → 4, 9; 6 → 6 (printed once). Six iterations.

## Example 3: loop with a growing step
```cpp
int s = 0, i = 1;
while (s < n) { s += i; i++; }
```
After `k` iterations `s = k(k+1)/2`. The loop stops when `k²/2 ≈ n`, so `k ≈ √(2n)` → O(√n).

## Example 4: square-root decomposition
Split an array of `n` elements into about √n blocks of √n elements and store each block's sum. A range-sum query then touches at most two partial blocks plus √n whole blocks: O(√n) per query instead of O(n).

## Comparison
| n | log₂ n | √n | n |
|---|---|---|---|
| 100 | 7 | 10 | 100 |
| 10,000 | 14 | 100 | 10,000 |
| 1,000,000 | 20 | 1,000 | 1,000,000 |
