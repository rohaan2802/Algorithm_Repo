# Rod Cutting (Dynamic Programming)

## Problem
A rod of length `n` can be cut into integer pieces. A piece of length `i` sells for `p[i]`. Find the maximum revenue `r[n]`.

## Recurrence
```
r[0] = 0
r[i] = max over 1 <= j <= i of ( p[j] + r[i - j] )
```
`j` is the length of the first piece; the rest of the rod (`i − j`) is already solved. Time Θ(n²), space Θ(n).

## C++ (no libraries beyond iostream)
```cpp
#include <iostream>
using namespace std;

int main() {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20};   // p[i] = price of length i
    int n = 8;
    int r[20], cut[20];
    r[0] = 0;
    for (int i = 1; i <= n; i++) {
        int best = -1;
        for (int j = 1; j <= i; j++) {
            if (p[j] + r[i - j] > best) { best = p[j] + r[i - j]; cut[i] = j; }
        }
        r[i] = best;
    }
    cout << "Max revenue: " << r[n] << endl;
    cout << "Pieces: ";
    for (int x = n; x > 0; x -= cut[x]) cout << cut[x] << " ";
    cout << endl;
    return 0;
}
```

## Dry run (prices 1, 5, 8, 9, 10, 17, 17, 20)
| Length i | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---|---|---|---|---|---|---|---|---|
| price p[i] | – | 1 | 5 | 8 | 9 | 10 | 17 | 17 | 20 |
| best r[i] | 0 | 1 | 5 | 8 | 10 | 13 | 17 | 18 | 22 |
| first cut | – | 1 | 2 | 3 | 2 | 2 | 6 | 1 | 2 |

Answer: `r[8] = 22`, pieces [2, 6].

Example cell, `r[4]`: options are `p1+r3 = 1+8`, `p2+r2 = 5+5`, `p3+r1 = 8+1`, `p4+r0 = 9`; the maximum is 10.

## Quick rule for filling the table
For cell `i`, pair up the **price row read left to right** with the **answer row read right to left**, starting from `r[i−1]`:

```
r[i] = max( p1 + r[i-1], p2 + r[i-2], ..., pi + r[0] )
```

So you add "price of the first piece" to "best value of what is left", for every first-piece length, and keep the largest sum. It always works because it is the recurrence itself.

## 2-D table form (unbounded knapsack view)
`dp[i][L]` = best revenue for length `L` using piece sizes `1..i`:
```
dp[i][L] = dp[i-1][L]                               if i > L
dp[i][L] = max(dp[i-1][L], p[i] + dp[i][L - i])     otherwise
```
The difference from 0/1 knapsack is that the second option stays in the **same row** (`dp[i][...]`), because a piece size can be used again.
