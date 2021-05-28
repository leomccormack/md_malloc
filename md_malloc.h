/*
 Copyright (c) 2019 Leo McCormack
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/**
 * @file md_malloc.h
 * @brief Contiguous memory allocation functions for multi-dimensional arrays
 *
 * An example of allocating, indexing and freeing a 3-D "array":
 * \code{.c}
 *   float*** example3D = (float***)malloc3d(10, 20, 5, sizeof(float);
 *   // Due to the contiguous nature of the allocation, this is possible:
 *   memset(FLATTEN3D(example3D), 0, 10*20*5*sizeof(float));
 *   // And it may also be indexed normally as:
 *   example3D[3][19][2] = 22.0f;
 *   // To free, simply call:
 *   free(example3D);
 * \endcode
 *
 * @author Leo McCormack
 * @date 11.06.2019
 */

/**********
 * PUBLIC:
 *********/

#ifndef MD_MALLOC_INCLUDED
#define MD_MALLOC_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * Use this macro when passing a 2-D dynamic multi-dimensional array to
 * memset, memcpy or any other function that expects a flat contiguous 1-D block
 * of data
 *
 * e.g.
 * \code{.c}
 *   float** array2D = (float**)malloc2d(10, 40, sizeof(float));
 *   memset(FLATTEN2D(array2D), 0, 10*40*sizeof(float));
 *   // ...
 *   free(array2D);
 * \endcode
 */
#define FLATTEN2D(A) (*A)  /* || (&A[0][0]) */

/**
 * Use this macro when passing a 3-D dynamic multi-dimensional array to
 * memset, memcpy or any other function that expects a flat contiguous 1-D block
 * of data
 */
#define FLATTEN3D(A) (**A) /* || (&A[0][0][0]) */

/**
 * Use this macro when passing a 4-D dynamic multi-dimensional array to
 * memset, memcpy or any other function that expects a flat contiguous 1-D block
 * of data
 */
#define FLATTEN4D(A) (***A) /* || (&A[0][0][0][0]) */

/**
 * Use this macro when passing a 5-D dynamic multi-dimensional array to
 * memset, memcpy or any other function that expects a flat contiguous 1-D block
 * of data
 */
#define FLATTEN5D(A) (****A) /* || (&A[0][0][0][0][0]) */

/**
 * Use this macro when passing a 6-D dynamic multi-dimensional array to
 * memset, memcpy or any other function that expects a flat contiguous 1-D block
 * of data
 */
#define FLATTEN6D(A) (*****A) /* || (&A[0][0][0][0][0][0]) */

/** 1-D malloc (same as malloc, but with error checking) */
void* malloc1d(size_t dim1_data_size);

/** 1-D calloc (same as calloc, but with error checking) */
void* calloc1d(size_t dim1, size_t data_size);

/** 1-D realloc (same as realloc, but with error checking) */
void* realloc1d(void* ptr, size_t dim1_data_size);

/** 2-D malloc (contiguously allocated, so use free() as usual to deallocate) */
void** malloc2d(size_t dim1, size_t dim2, size_t data_size);

/** 2-D calloc (contiguously allocated, so use free() as usual to deallocate) */
void** calloc2d(size_t dim1, size_t dim2, size_t data_size);

/** 2-D realloc which does NOT retain previous data order */
void** realloc2d(void** ptr, size_t dim1, size_t dim2, size_t data_size);

/** 3-D malloc (contiguously allocated, so use free() as usual to deallocate) */
void*** malloc3d(size_t dim1, size_t dim2, size_t dim3, size_t data_size);

/** 3-D calloc (contiguously allocated, so use free() as usual to deallocate) */
void*** calloc3d(size_t dim1, size_t dim2, size_t dim3, size_t data_size);

/** 3-D realloc which does NOT retain previous data order */
void*** realloc3d(void*** ptr, size_t dim1, size_t dim2, size_t dim3,
                  size_t data_size);

/** 4-D malloc (contiguously allocated, so use free() as usual to deallocate) */
void**** malloc4d(size_t dim1, size_t dim2, size_t dim3, size_t dim4,
                  size_t data_size);

/** 4-D calloc (contiguously allocated, so use free() as usual to deallocate) */
void**** calloc4d(size_t dim1, size_t dim2, size_t dim3, size_t dim4,
                  size_t data_size);

/** 4-D realloc which does NOT retain previous data order */
void**** realloc4d(void**** ptr, size_t dim1, size_t dim2, size_t dim3,
                   size_t dim4, size_t data_size);

/** 5-D malloc (contiguously allocated, so use free() as usual to deallocate) */
void***** malloc5d(size_t dim1, size_t dim2, size_t dim3, size_t dim4,
                   size_t dim5, size_t data_size);

/** 5-D calloc (contiguously allocated, so use free() as usual to deallocate) */
void***** calloc5d(size_t dim1, size_t dim2, size_t dim3, size_t dim4,
                   size_t dim5, size_t data_size);

/** 5-D realloc which does NOT retain previous data order */
void***** realloc5d(void***** ptr, size_t dim1, size_t dim2, size_t dim3,
                    size_t dim4, size_t dim5, size_t data_size);

/** 6-D malloc (contiguously allocated, so use free() as usual to deallocate) */
void****** malloc6d(size_t dim1, size_t dim2, size_t dim3, size_t dim4,
                    size_t dim5, size_t dim6, size_t data_size);

/** 6-D malloc (contiguously allocated, so use free() as usual to deallocate) */
void****** calloc6d(size_t dim1, size_t dim2, size_t dim3, size_t dim4,
                    size_t dim5, size_t dim6, size_t data_size);

/** 6-D realloc which does NOT retain previous data order */
void****** realloc6d(void****** ptr, size_t dim1, size_t dim2, size_t dim3,
                     size_t dim4, size_t dim5, size_t dim6, size_t data_size);


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* MD_MALLOC_INCLUDED */


/************
 * INTERNAL:
 ***********/

#ifdef MD_MALLOC_ENABLE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "md_malloc.h"

void* malloc1d(size_t dim1_data_size)
{
    void *ptr = malloc(dim1_data_size);
#if !defined(NDEBUG)
    if (ptr == NULL && dim1_data_size!=0)
        fprintf(stderr, "Error: 'malloc1d' failed to allocate %zu bytes.\n", dim1_data_size);
#endif
    return ptr;
}

void* calloc1d(size_t dim1, size_t data_size)
{
    void *ptr = calloc(dim1, data_size);
#if !defined(NDEBUG)
    if (ptr == NULL && dim1!=0)
        fprintf(stderr, "Error: 'calloc1d' failed to allocate %zu bytes.\n", dim1*data_size);
#endif
    return ptr;
}

void* realloc1d(void* ptr, size_t dim1_data_size)
{
    ptr = realloc(ptr, dim1_data_size);
#if !defined(NDEBUG)
    if (ptr == NULL && dim1_data_size!=0)
        fprintf(stderr, "Error: 'realloc1d' failed to allocate %zu bytes.\n", dim1_data_size);
#endif
    return ptr;
}

void** malloc2d(size_t dim1, size_t dim2, size_t data_size)
{
    size_t i, stride;
    void** ptr;
    unsigned char* p2;
    stride = dim2*data_size;
    ptr = malloc1d(dim1*sizeof(void*) + dim1*stride);
    p2 = (unsigned char*)(ptr + dim1);
    for(i=0; i<dim1; i++)
        ptr[i] = &p2[i*stride];
    return ptr;
}

void** calloc2d(size_t dim1, size_t dim2, size_t data_size)
{
    size_t i, stride;
    void** ptr;
    unsigned char* p2;
    stride = dim2*data_size;
    ptr = calloc1d(dim1, sizeof(void*) + stride);
    p2 = (unsigned char*)(ptr + dim1);
    for(i=0; i<dim1; i++)
        ptr[i] = &p2[i*stride];
    return ptr;
}

void** realloc2d(void** ptr, size_t dim1, size_t dim2, size_t data_size)
{
    size_t i, stride;
    unsigned char* p2;
    stride = dim2*data_size;
    ptr = realloc1d(ptr, dim1*sizeof(void*) + dim1*stride);
    p2 = (unsigned char*)(ptr + dim1);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*stride];
    return ptr;
}

void*** malloc3d(size_t dim1, size_t dim2, size_t dim3, size_t data_size)
{
    size_t i, j, stride1, stride2;
    void*** ptr;
    void** p2;
    unsigned char* p3;
    stride1 = dim2*dim3*data_size;
    stride2 = dim3*data_size;
    ptr = malloc1d(dim1*sizeof(void**) + dim1*dim2*sizeof(void*) + dim1*stride1);
    p2 = (void**)(ptr + dim1);
    p3 = (unsigned char*)(p2 + dim1*dim2);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*stride1 + j*stride2];
    return ptr;
}

void*** calloc3d(size_t dim1, size_t dim2, size_t dim3, size_t data_size)
{
    size_t i, j, stride1, stride2;
    void*** ptr;
    void** p2;
    unsigned char* p3;
    stride1 = dim2*dim3*data_size;
    stride2 = dim3*data_size;
    ptr = calloc1d(dim1, sizeof(void**) + dim2*sizeof(void*) + stride1);
    p2 = (void**)(ptr + dim1);
    p3 = (unsigned char*)(p2 + dim1*dim2);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*stride1 + j*stride2];
    return ptr;
}

void*** realloc3d(void*** ptr, size_t new_dim1, size_t new_dim2, size_t new_dim3, size_t data_size)
{
    size_t i, j, stride1, stride2;
    void** p2;
    unsigned char* p3;
    stride1 = new_dim2*new_dim3*data_size;
    stride2 = new_dim3*data_size;
    ptr = realloc1d(ptr, new_dim1*sizeof(void**) + new_dim1*new_dim2*sizeof(void*) + new_dim1*stride1);
    p2 = (void**)(ptr + new_dim1);
    p3 = (unsigned char*)(p2 + new_dim1*new_dim2);
    for(i=0;i<new_dim1;i++)
        ptr[i] = &p2[i*new_dim2];
    for(i=0;i<new_dim1;i++)
        for(j=0;j<new_dim2;j++)
            p2[i*new_dim2+j] = &p3[i*stride1 + j*stride2];
    return ptr;
}

void**** malloc4d(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t data_size)
{
    size_t i, j, k, stride1, stride2, stride3;
    void**** ptr;
    void*** p2;
    void** p3;
    unsigned char* p4;
    stride1 = dim2*dim3*dim4*data_size;
    stride2 = dim3*dim4*data_size;
    stride3 = dim4*data_size;
    ptr = malloc1d(dim1*sizeof(void***) + dim1*dim2*sizeof(void**) + dim1*dim2*dim3*sizeof(void*) + dim1*stride1);
    p2 = (void***)(ptr + dim1);
    p3 = (void**)(p2 + dim1*dim2);
    p4 = (unsigned char*)(p3 + dim1*dim2*dim3);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3+j*dim3+k] = &p4[i*stride1 + j*stride2 + k*stride3];
    return ptr;
}

void**** calloc4d(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t data_size)
{
    size_t i, j, k, stride1, stride2, stride3;
    void**** ptr;
    void*** p2;
    void** p3;
    unsigned char* p4;
    stride1 = dim2*dim3*dim4*data_size;
    stride2 = dim3*dim4*data_size;
    stride3 = dim4*data_size;
    ptr = calloc1d(dim1, sizeof(void***) + dim2*sizeof(void**) + dim2*dim3*sizeof(void*) + stride1);
    p2 = (void***)(ptr + dim1);
    p3 = (void**)(p2 + dim1*dim2);
    p4 = (unsigned char*)(p3 + dim1*dim2*dim3);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3+j*dim3+k] = &p4[i*stride1 + j*stride2 + k*stride3];
    return ptr;
}

void**** realloc4d(void**** ptr, size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t data_size)
{
    size_t i, j, k, stride1, stride2, stride3;
    void*** p2;
    void** p3;
    unsigned char* p4;
    stride1 = dim2*dim3*dim4*data_size;
    stride2 = dim3*dim4*data_size;
    stride3 = dim4*data_size;
    ptr = realloc1d(ptr, dim1*sizeof(void***) + dim1*dim2*sizeof(void**) + dim1*dim2*dim3*sizeof(void*) + dim1*stride1);
    p2 = (void***)(ptr + dim1);
    p3 = (void**)(p2 + dim1*dim2);
    p4 = (unsigned char*)(p3 + dim1*dim2*dim3);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3+j*dim3+k] = &p4[i*stride1 + j*stride2 + k*stride3];
    return ptr;
}

void***** malloc5d(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t data_size)
{
    size_t i, j, k, l, stride1, stride2, stride3, stride4;
    void***** ptr;
    void**** p2;
    void*** p3;
    void** p4;
    unsigned char* p5;
    stride1 = dim2*dim3*dim4*dim5*data_size;
    stride2 = dim3*dim4*dim5*data_size;
    stride3 = dim4*dim5*data_size;
    stride4 = dim5*data_size;
    ptr = malloc1d(dim1*sizeof(void****) + dim1*dim2*sizeof(void***) + dim1*dim2*dim3*sizeof(void**) + dim1*dim2*dim3*dim4*sizeof(void*) + dim1*stride1);
    p2 = (void****)(ptr + dim1);
    p3 = (void***)(p2 + dim1*dim2);
    p4 = (void**)(p3 + dim1*dim2*dim3);
    p5 = (unsigned char*)(p4 + dim1*dim2*dim3*dim4);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3 + j*dim3 + k] = &p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(l=0;l<dim4;l++)
                    p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l] = &p5[i*stride1 + j*stride2 + k*stride3 + l*stride4];
    return ptr;
}

void***** calloc5d(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t data_size)
{
    size_t i, j, k, l, stride1, stride2, stride3, stride4;
    void***** ptr;
    void**** p2;
    void*** p3;
    void** p4;
    unsigned char* p5;
    stride1 = dim2*dim3*dim4*dim5*data_size;
    stride2 = dim3*dim4*dim5*data_size;
    stride3 = dim4*dim5*data_size;
    stride4 = dim5*data_size;
    ptr = calloc1d(dim1, sizeof(void****) + dim2*sizeof(void***) + dim2*dim3*sizeof(void**) + dim2*dim3*dim4*sizeof(void*) + stride1);
    p2 = (void****)(ptr + dim1);
    p3 = (void***)(p2 + dim1*dim2);
    p4 = (void**)(p3 + dim1*dim2*dim3);
    p5 = (unsigned char*)(p4 + dim1*dim2*dim3*dim4);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3 + j*dim3 + k] = &p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(l=0;l<dim4;l++)
                    p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l] = &p5[i*stride1 + j*stride2 + k*stride3 + l*stride4];
    return ptr;
}

void***** realloc5d(void***** ptr, size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t data_size)
{
    size_t i, j, k, l, stride1, stride2, stride3, stride4;
    void**** p2;
    void*** p3;
    void** p4;
    unsigned char* p5;
    stride1 = dim2*dim3*dim4*dim5*data_size;
    stride2 = dim3*dim4*dim5*data_size;
    stride3 = dim4*dim5*data_size;
    stride4 = dim5*data_size;
    ptr = realloc1d(ptr, dim1*sizeof(void****) + dim1*dim2*sizeof(void***) + dim1*dim2*dim3*sizeof(void**) + dim1*dim2*dim3*dim4*sizeof(void*) + dim1*stride1);
    p2 = (void****)(ptr + dim1);
    p3 = (void***)(p2 + dim1*dim2);
    p4 = (void**)(p3 + dim1*dim2*dim3);
    p5 = (unsigned char*)(p4 + dim1*dim2*dim3*dim4);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3 + j*dim3 + k] = &p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(l=0;l<dim4;l++)
                    p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + l] = &p5[i*stride1 + j*stride2 + k*stride3 + l*stride4];
    return ptr;
}

void****** malloc6d(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6, size_t data_size)
{
    size_t i, j, k, l, p, stride1, stride2, stride3, stride4, stride5;
    void****** ptr;
    void***** p2;
    void**** p3;
    void*** p4;
    void** p5;
    unsigned char* p6;
    stride1 = dim2*dim3*dim4*dim5*dim6*data_size;
    stride2 = dim3*dim4*dim5*dim6*data_size;
    stride3 = dim4*dim5*dim6*data_size;
    stride4 = dim5*dim6*data_size;
    stride5 = dim6*data_size;
    ptr = malloc1d(dim1*sizeof(void*****) + dim1*dim2*sizeof(void****) + dim1*dim2*dim3*sizeof(void***) +
                   dim1*dim2*dim3*dim4*sizeof(void**) + dim1*dim2*dim3*dim4*dim5*sizeof(void*) + dim1*stride1);
    p2 = (void*****)(ptr + dim1);
    p3 = (void****)(p2 + dim1*dim2);
    p4 = (void***)(p3 + dim1*dim2*dim3);
    p5 = (void**)(p4 + dim1*dim2*dim3*dim4);
    p6 = (unsigned char*)(p5 + dim1*dim2*dim3*dim4*dim5);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3 + j*dim3 + k] = &p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(p=0;p<dim4;p++)
                    p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + p] = &p5[i*dim2*dim3*dim4*dim5 + j*dim3*dim4*dim5 + k*dim4*dim5 + p*dim5];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(l=0;l<dim4;l++)
                    for(p=0;p<dim5;p++)
                         p5[i*dim2*dim3*dim4*dim5 + j*dim3*dim4*dim5 + k*dim4*dim5 + l*dim5 + p] = &p6[i*stride1 + j*stride2 + k*stride3 + l*stride4 + p*stride5];
    return ptr;
}

void****** calloc6d(size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6, size_t data_size)
{
    size_t i, j, k, l, p, stride1, stride2, stride3, stride4, stride5;
    void****** ptr;
    void***** p2;
    void**** p3;
    void*** p4;
    void** p5;
    unsigned char* p6;
    stride1 = dim2*dim3*dim4*dim5*dim6*data_size;
    stride2 = dim3*dim4*dim5*dim6*data_size;
    stride3 = dim4*dim5*dim6*data_size;
    stride4 = dim5*dim6*data_size;
    stride5 = dim6*data_size;
    ptr = calloc1d(dim1, sizeof(void*****) + dim2*sizeof(void****) + dim2*dim3*sizeof(void***) +
                   dim2*dim3*dim4*sizeof(void**) + dim2*dim3*dim4*dim5*sizeof(void*) + stride1);
    p2 = (void*****)(ptr + dim1);
    p3 = (void****)(p2 + dim1*dim2);
    p4 = (void***)(p3 + dim1*dim2*dim3);
    p5 = (void**)(p4 + dim1*dim2*dim3*dim4);
    p6 = (unsigned char*)(p5 + dim1*dim2*dim3*dim4*dim5);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3 + j*dim3 + k] = &p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(p=0;p<dim4;p++)
                    p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + p] = &p5[i*dim2*dim3*dim4*dim5 + j*dim3*dim4*dim5 + k*dim4*dim5 + p*dim5];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(l=0;l<dim4;l++)
                    for(p=0;p<dim5;p++)
                         p5[i*dim2*dim3*dim4*dim5 + j*dim3*dim4*dim5 + k*dim4*dim5 + l*dim5 + p] = &p6[i*stride1 + j*stride2 + k*stride3 + l*stride4 + p*stride5];
    return ptr;
}

void****** realloc6d(void****** ptr, size_t dim1, size_t dim2, size_t dim3, size_t dim4, size_t dim5, size_t dim6, size_t data_size)
{
    size_t i, j, k, l, p, stride1, stride2, stride3, stride4, stride5;
    void***** p2;
    void**** p3;
    void*** p4;
    void** p5;
    unsigned char* p6;
    stride1 = dim2*dim3*dim4*dim5*dim6*data_size;
    stride2 = dim3*dim4*dim5*dim6*data_size;
    stride3 = dim4*dim5*dim6*data_size;
    stride4 = dim5*dim6*data_size;
    stride5 = dim6*data_size;
    ptr = realloc1d(ptr, dim1*sizeof(void*****) + dim1*dim2*sizeof(void****) + dim1*dim2*dim3*sizeof(void***) +
                    dim1*dim2*dim3*dim4*sizeof(void**) + dim1*dim2*dim3*dim4*dim5*sizeof(void*) + dim1*stride1);
    p2 = (void*****)(ptr + dim1);
    p3 = (void****)(p2 + dim1*dim2);
    p4 = (void***)(p3 + dim1*dim2*dim3);
    p5 = (void**)(p4 + dim1*dim2*dim3*dim4);
    p6 = (unsigned char*)(p5 + dim1*dim2*dim3*dim4*dim5);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*dim2*dim3 + j*dim3];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                p3[i*dim2*dim3 + j*dim3 + k] = &p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(p=0;p<dim4;p++)
                    p4[i*dim2*dim3*dim4 + j*dim3*dim4 + k*dim4 + p] = &p5[i*dim2*dim3*dim4*dim5 + j*dim3*dim4*dim5 + k*dim4*dim5 + p*dim5];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            for(k=0;k<dim3;k++)
                for(l=0;l<dim4;l++)
                    for(p=0;p<dim5;p++)
                         p5[i*dim2*dim3*dim4*dim5 + j*dim3*dim4*dim5 + k*dim4*dim5 + l*dim5 + p] = &p6[i*stride1 + j*stride2 + k*stride3 + l*stride4 + p*stride5];
    return ptr;
}


#endif /* MD_MALLOC_ENABLE */

