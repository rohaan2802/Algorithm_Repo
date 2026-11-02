# Ways to Swap Two Variables in C++ (without std::swap)

## 1. Temporary variable (recommended)
```cpp
void swapTemp(int &a, int &b) { int t = a; a = b; b = t; }
```
Clear, works for every type, no overflow risk.

## 2. Addition and subtraction
```cpp
a = a + b;  b = a - b;  a = a - b;
```
No extra variable, but `a + b` can overflow for large signed values.

## 3. Multiplication and division
```cpp
a = a * b;  b = a / b;  a = a / b;
```
Fails when either value is 0 and overflows easily. Only of theoretical interest.

## 4. XOR
```cpp
a = a ^ b;  b = a ^ b;  a = a ^ b;
```
Works for integers without overflow. If `a` and `b` refer to the **same** variable (for example `swap(x, x)` by reference), it sets the value to 0, so guard with `if (&a != &b)`.

## 5. Pointers
```cpp
void swapPtr(int *a, int *b) { int t = *a; *a = *b; *b = t; }
// call: swapPtr(&x, &y);
```

## 6. One-line arithmetic form
```cpp
b = a + b - (a = b);
```
Relies on evaluation order; legal only since C++17 sequencing rules and hard to read. Avoid in real code.

## Summary
| Method | Extra memory | Risks |
|---|---|---|
| Temporary | 1 variable | none |
| + / − | none | overflow |
| × / ÷ | none | zero, overflow |
| XOR | none | same-address case, integers only |
| Pointers | 1 variable | null pointers |

In practice the temporary-variable version is just as fast; compilers optimise it to register moves.
