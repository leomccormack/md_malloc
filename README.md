# md_malloc

A header file comprising dynamic memory allocation functions for contiguous multi-dimensional arrays. The code is written in C and is MSVC compliant.

## Motivation

The main reasons for consolidating these multi-dimensional memory allocation functions are threefold. 

1. To discourage the wide-spread  - Non-Contiguous memory allocation
```c
/* "2-D array" */
float** array2D = malloc(20*sizeof(float*));
for(int i=0; i<20; i++)
    array2D[i] = malloc(10*sizeof(float));

for(int i=0; i<20; i++)
    free(array2D[i]);
free(array2D);
```

2. To still retain the easy indexing
```c
/* "2-D array" */
float** array2D = malloc(20*sizeof(float*));
for(int i=0; i<20; i++)
array2D[i] = malloc(10*sizeof(float));

for(int i=0; i<20; i++)
free(array2D[i]);
free(array2D);
```



3. To compile on the ancient MSVC C-compiler. For cross-platform development this is (unfortunetaly) a big requirement.




## Getting Started

To use this simple add the following:

```c
#define MD_MALLOC_ENABLE
#include "md_malloc.h"
```

## Test


## License

The code is distributed under the MIT license

