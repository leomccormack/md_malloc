# md_malloc

A header file comprising dynamic memory allocation functions for contiguous multi-dimensional arrays. The code is written in C and is MSVC compliant.

## Motivation

The reasons for consolidating these dynamic contiguous multi-dimensional memory allocation functions are threefold. 

1. To avoid (and hopefully discourage) the wide-spread adoption non-contiguous memory allocation:
```c
/* For example, let's allocate an A x B, 2-D "array" as: */
float** array2D = malloc(A*sizeof(float*));
for(int i=0; i<A; i++)
    array2D[i] = malloc(B*sizeof(float));
    
/* While it may indeed be easily indexed (i,j) array2D[i][j] (since it employs multiple 
 * malloc calls), the second dimension vectors are not guaranteed to be adjacent to 
 * one-another i.e. the memory is not necessarily "contiguous". Therefore, calls to 
 * memset/memcpy or other functions which rely on contiguous memory allocation may fail
 * and result in crashes or worse */
 
memset(&array2D[0][0], 0, A*B*sizeof(float)); /* could be fine, but likely not */

/* freeing the memory is also slightly cumbersome: */
for(int i=0; i<A; i++)
    free(array2D[i]);
free(array2D);
```

2. To retain easy indexing:
```c
/* One may, however, allocate a contiguous A x B, 2-D "array" with as single malloc 
 * call: */
float* array2D = malloc(A*B*sizeof(float));

/* However, these are also not ideal, as they must be indexed (i,j) as array2D[i*B+j], 
 * which gets messy for high-dimensional arrays; 
 * e.g. (i,j,k,l,p), array5D[i*B*C*D*E + j*C*D*E + k*D*E + l*E +p] */
```

3. To maintain easy passing of N-D arrays to other functions:
```c
/* Since C99, multidimensional arrays can be declared as */
float (*array2D)[B] = malloc(sizeof(float[A][B]));

/* These can be indexed "array2D[i][j]" and freed "free(array2D)" easily. However, 
 * these cannot be easily and flexibly passed to other functions due to the variable 
 * type. */
 
/* Furthermore, for cross-platform developement, supporting the ancient MSVC compiler
 * is (unfortunately) a common requirement. Since Microsoft's C-compiler is still based  
 * on C89/C90, this C99-style is not a viable option regardless. */
```


## Getting Started

To use this simple add the following:

```c
#define MD_MALLOC_ENABLE
#include "md_malloc.h"
```

### Example

```c
/* For example, to allocate an A x B, 2-D "array" */
float** array2D = (float**)malloc2d(A, B, sizeof(float));

/* which is: 1) contiguous, 2) easily indexed and freed, and 3) compiles with MSVC */

memset(array2D[0][0], 



```


## Testing


## License

The code is distributed under the MIT license.

