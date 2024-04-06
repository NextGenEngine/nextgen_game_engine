# Benchmarks

## Comparing performance of move semantics versus references

Measuring performance of identical classes by functionality,
but using different constructor definitions.

One is using pass-by-const-reference, another is using move semantics
modern language feature.

Results:

| Benchmark                                 | Time    | CPU     | Iterations |
| ----------------------------------------- | ------- | ------- | ---------- |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 2.08 us | 2.08 us | 1000000    |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 1.90 us | 1.90 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 3.43 us | 3.43 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 2.91 us | 2.91 us | 1000000    |

Move semantic shows noticeable performance boost. And it seems to align better
with cache locality, because warmup loop is less different from working loop.
Difference between warmup and working loops in "references" approach is much
higher.
Move semantics here is about 1.5x times faster.
