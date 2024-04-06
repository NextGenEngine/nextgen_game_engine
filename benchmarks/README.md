# Benchmarks

## Comparing performance of move semantics versus references

Measuring performance of identical classes by functionality,
but using different constructor definitions.

One is using pass-by-const-reference, another is using move semantics
modern language feature.

Results:

| Benchmark                                 | Time    | CPU     | Iterations |
| ----------------------------------------- | ------- | ------- | ---------- |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 4.19 us | 4.19 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 3.16 us | 3.16 us | 1000000    |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 3.00 us | 3.00 us | 1000000    |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 2.91 us | 2.91 us | 1000000    |

Reordering:

| Benchmark                                 | Time    | CPU     | Iterations |
| ----------------------------------------- | ------- | ------- | ---------- |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 4.05 us | 4.05 us | 1000000    |
| BM_CONFIG_MANAGER_MOVE/iterations:1000000 | 3.26 us | 3.26 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 2.97 us | 2.97 us | 1000000    |
| BM_CONFIG_MANAGER_REF/iterations:1000000  | 2.89 us | 2.89 us | 1000000    |

There is no difference. Difference you see is about the order tests are running.
In first case "references" are running first and are a bit slower (especially
first warmup loop). In second test "move semantic" goes first and the same
a bit slower.

BTW in previous commit (check history) I made a mistake. And "move semantic"
was showing 1.5x boost in performance, but it was related only to the fact,
that "reference" was using additional inline function call (and clang compiler
did not inlined this function for some reason), but "move semantic" was running
same code, but without function. That give 1.5x faster execution. Now it is
a question for me: how to ensure compiler inlines this function call.
