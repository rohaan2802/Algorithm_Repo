# Dynamic Programming: Top-Down vs Bottom-Up

Dynamic programming applies when a problem has **overlapping subproblems** and **optimal substructure**. Each subproblem is solved once and its answer is stored.

## Plain recursion (exponential)
```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);   // recomputes the same values: about 2^n calls
}
```

## Top-down (memoization)
Keep the recursive structure, but cache each answer.
```cpp
int memo[100];                       // fill with -1 before the first call
int fib(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib(n - 1) + fib(n - 2);
}
```
* Solves only the subproblems that are actually needed.
* Easy to write from the recurrence.
* Uses the call stack (deep recursion can overflow).

## Bottom-up (tabulation)
Fill a table from the smallest subproblems upward.
```cpp
int fib(int n) {
    if (n <= 1) return n;
    int dp[100]; dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++) dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}
```
Only the last two values are needed, so space can drop to O(1):
```cpp
int a = 0, b = 1;
for (int i = 2; i <= n; i++) { int c = a + b; a = b; b = c; }
```

## Comparison
| | Top-down | Bottom-up |
|---|---|---|
| Style | Recursive + cache | Iterative loops |
| Order | Decided by recursion | Must be chosen by hand |
| Subproblems solved | Only needed ones | All of them |
| Overhead | Function calls, stack | None |
| Time for Fibonacci | O(n) | O(n) |

## Steps for any DP problem
1. Define the state (what `dp[i]` or `dp[i][j]` means).
2. Write the recurrence.
3. Set the base cases.
4. Choose the fill order (bottom-up) or add a cache (top-down).
5. Read the answer, and trace back if the actual solution is needed.
