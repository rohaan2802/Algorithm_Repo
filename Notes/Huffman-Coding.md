# Huffman Coding and Decoding

Huffman coding is a lossless compression method. Frequent characters get short codes, rare characters get long codes, and no code is a prefix of another (a **prefix code**), so decoding is unambiguous.

## Encoding algorithm
1. Count the frequency of every character.
2. Put each character in a min-priority queue keyed by frequency.
3. While more than one node remains: remove the two smallest nodes `x` and `y`, create a parent with frequency `x + y`, make `x` its left child and `y` its right child, insert the parent.
4. The last node is the root. Label every left edge `0` and every right edge `1`; a character's code is the path from the root to its leaf.

Time: O(n log n) for `n` distinct characters (n−1 merges, each O(log n) with a heap).

## Worked example
| Char | a | b | c | d | e | f |
|---|---|---|---|---|---|---|
| Frequency | 5 | 9 | 12 | 13 | 16 | 45 |

Merges:
1. a(5) + b(9) → 14
2. c(12) + d(13) → 25
3. 14 + e(16) → 30
4. 25 + 30 → 55
5. f(45) + 55 → 100 (root)

Resulting codes:

| Char | f | c | d | a | b | e |
|---|---|---|---|---|---|---|
| Code | 0 | 100 | 101 | 1100 | 1101 | 111 |
| Bits × freq | 45 | 36 | 39 | 20 | 36 | 48 |

Total = 224 bits, compared with 300 bits for a fixed 3-bit code (100 characters × 3).

## Decoding
Start at the root and read bits one by one: `0` moves left, `1` moves right. On reaching a leaf, output its character and return to the root.

Example: `0 101 100 1100` decodes to `f d c a`.

## Notes
* Ties can be broken either way; codes may differ, but the total length is the same (optimal).
* Huffman coding is a greedy algorithm: merging the two least frequent symbols first is provably optimal.
