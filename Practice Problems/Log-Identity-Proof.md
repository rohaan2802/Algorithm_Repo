# Proof: a^(log_b n) = n^(log_b a)

This identity is used in the Master Method, for example `3^(log₄ n) = n^(log₄ 3)`.

Conditions: `a > 0`, `b > 0`, `b ≠ 1`, `n > 0`.

## Proof with natural logarithms
Let `y = a^(log_b n)`.

1. Take `ln` of both sides: `ln y = (log_b n) · ln a`.
2. Change of base: `log_b n = ln n / ln b`, so `ln y = (ln n · ln a) / ln b`.
3. Regroup: `ln y = ln n · (ln a / ln b) = (log_b a) · ln n`.
4. So `ln y = ln( n^(log_b a) )`, and since `ln` is one-to-one, `y = n^(log_b a)`.

## Shorter proof
Write `n = b^(log_b n)`. Then

```
n^(log_b a) = (b^(log_b n))^(log_b a) = (b^(log_b a))^(log_b n) = a^(log_b n)
```

## Application
In `T(n) = 3T(n/4) + f(n)`, the recursion tree has `3^(log₄ n)` leaves. By the identity this equals `n^(log₄ 3) ≈ n^0.793`, which is the term the Master Method compares with `f(n)`.
