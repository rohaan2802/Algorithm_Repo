# Insertion Sort and Selection Sort

## Insertion sort
Idea: like sorting playing cards in your hand. The left part is always sorted; take the next element (`key`) and shift larger elements right until the key's place is found.

```cpp
void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {   // shift bigger elements right
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
```

Dry run on `[5, 2, 4, 6, 1, 3]`:

| i | key | array after pass |
|---|---|---|
| 1 | 2 | 2 5 4 6 1 3 |
| 2 | 4 | 2 4 5 6 1 3 |
| 3 | 6 | 2 4 5 6 1 3 |
| 4 | 1 | 1 2 4 5 6 3 |
| 5 | 3 | 1 2 3 4 5 6 |

## Selection sort
Idea: for each position, find the minimum of the unsorted part and swap it into place.

```cpp
void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx]) minIdx = j;
        int t = a[i]; a[i] = a[minIdx]; a[minIdx] = t;
    }
}
```

Dry run on `[64, 25, 12, 22, 11]`:

| i | minimum found | array after swap |
|---|---|---|
| 0 | 11 | 11 25 12 22 64 |
| 1 | 12 | 11 12 25 22 64 |
| 2 | 22 | 11 12 22 25 64 |
| 3 | 25 | 11 12 22 25 64 |

## Comparison
| | Insertion sort | Selection sort |
|---|---|---|
| Best case | Θ(n) (already sorted) | Θ(n²) |
| Average / worst | Θ(n²) | Θ(n²) |
| Swaps / writes | up to Θ(n²) shifts | at most n − 1 swaps |
| Stable | Yes | No (standard version) |
| In place | Yes | Yes |
| Adaptive | Yes | No |

Use insertion sort for small or nearly sorted data; selection sort when writes are expensive.
