### Results:

C code:

|         | **Original** (Debug) | **Original (Release)** | **SSE** (Debug) | SSE (Release) | AVX (Debug) | **AVX (Release)** |
| ------- | -------------------- | ---------------------- | --------------- | ------------- | ----------- | ----------------- |
| 1       | 166                  | 78                     | 69              | 77            | 65          | 81                |
| 2       | 164                  | 94                     | 67              | 71            | 61          | 97                |
| 3       | 167                  | 94                     | 71              | 66            | 61          | 88                |
| 4       | 169                  | 94                     | 65              | 63            | 74          | 98                |
| 5       | 167                  | 95                     | 68              | 70            | 60          | 78                |
|         |                      |                        |                 |               |             |                   |
| AVG     | 166.60               | 91.00                  | 68.00           | 75.40         | 64.20       | 88.40             |
| Speedup |                      | **183%**               | **244%**        |               | **259%**    |                   |



C++ code:

|         | AVX (Debug) | **AVX (Release)** |
| ------- | ----------- | ----------------- |
| 1       | 563         | 60                |
| 2       | 544         | 56                |
| 3       | 543         | 55                |
| 4       | 752         | 56                |
| 5       | 553         | 56                |
|         |             |                   |
| AVG     | 591.00      | 56.60             |
| Speedup |             | **294%**          |



Theres no conclusion, the activity only demonstrated that the compiler optimization configurations have great impact on the results. Furthermore C++ debug code adds a large overhead, probably because of name mangling and other mechanisms, plus the default compiler options. The next steps are to undesrtand how to tune the compiler and to make a comparission with auto vectorization features.