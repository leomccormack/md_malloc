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

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* include md_malloc like so: */
#define MD_MALLOC_ENABLE
#include "../md_malloc.h"

/* TEST CONFIGURATION */
#define ENABLE_C99_SPEED_TESTS  /* compares m_malloc also to C99-style.  */
#define ENABLE_CBLAS_TESTS
#define MAX_DIMENSION_LENGTH 300  /* beware stack overflows */
typedef float test_data_type;

#ifdef ENABLE_CBLAS_TESTS
# ifdef __APPLE__
#  include <Accelerate/Accelerate.h>
# else
/* remove "ENABLE_CBLAS_TESTS" flag, or include some other library that supports CBLAS
 * e.g. Intel MKL: */
#  include "mkl.h"
# endif
#endif


int main(int argc, const char * argv[])
{
    int iter, i, j, k, dim1, dim2, dim3;
    test_data_type** array2d_dynamic;
    test_data_type** array2d_dynamic2;
    test_data_type** array2d_dynamic3;
    test_data_type*** array3d_dynamic;
    test_data_type* mangled_array2d_dynamic;
    test_data_type* mangled_array3d_dynamic;
    test_data_type array2d_static_rand[MAX_DIMENSION_LENGTH*MAX_DIMENSION_LENGTH];
    test_data_type array2d_static_rand2[MAX_DIMENSION_LENGTH*MAX_DIMENSION_LENGTH];
    test_data_type array2d_static_rand3[MAX_DIMENSION_LENGTH*MAX_DIMENSION_LENGTH];
    test_data_type array3d_static[MAX_DIMENSION_LENGTH*MAX_DIMENSION_LENGTH*MAX_DIMENSION_LENGTH];
    float error;
    int msec, msec2;
    clock_t difference;
    clock_t before;
#ifdef ENABLE_C99_SPEED_TESTS
    int msec3;
#endif
    
    /*********************************************************************************************************/
    printf("********** Malloc Contiguity Test - RANDOM 2D DATA **********\n");
    error = 0.0f;
    before = clock();
    for(iter=0; iter<100000; iter++){
        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
        array2d_dynamic = (test_data_type**)malloc2d(dim1, dim2, sizeof(test_data_type));
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                array2d_dynamic[i][j] = rand()/RAND_MAX;
        /* only passes this test if "array2d_dynamic" is truely contiguous */
        memcpy(&array2d_static_rand[0], ADR2D(array2d_dynamic), dim1*dim2*sizeof(test_data_type));
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                error += fabs(array2d_dynamic[i][j]-array2d_static_rand[i*dim2 + j]);
        assert(error <= 2.23e-8f); /* if you land on this assertion, "array2d_dynamic" is not contiguously allocated */
        free2d((void**)array2d_dynamic);
    }
    difference = clock() - before;
    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);


    /*********************************************************************************************************/
    printf("********** Calloc Test - 2D DATA **********\n");
    error = 0.0f;
    before = clock();
    for(iter=0; iter<100000; iter++){
        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
        array2d_dynamic = (test_data_type**)calloc2d(dim1, dim2, sizeof(test_data_type));
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                error += fabs(array2d_dynamic[i][j]);
        assert(error <= 2.23e-8f); /* if you land on this assertion, "array2d_dynamic" was not correctly allocated and/or zero'd */
        free2d((void**)array2d_dynamic);
    }
    difference = clock() - before;
    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);


    /*********************************************************************************************************/
    printf("********** Malloc Speed Test - 2D DATA **********\n");
    before = clock();
    dim1 = MAX_DIMENSION_LENGTH-10;
    dim2 = MAX_DIMENSION_LENGTH;
    for(iter=0; iter<30000; iter++){
        mangled_array2d_dynamic = malloc(dim1* dim2* sizeof(test_data_type));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                mangled_array2d_dynamic[i*dim2+j] = rand();
        free(mangled_array2d_dynamic);
    }
    difference = clock() - before;
    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - Mangled array time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
    
    before = clock();
    for(iter=0; iter<30000; iter++){
        array2d_dynamic = (test_data_type**)malloc2d(dim1, dim2, sizeof(test_data_type));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                array2d_dynamic[i][j] = rand();
        free(array2d_dynamic);
    }
    difference = clock() - before;
    msec2 = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - md_malloc time taken %d seconds %d milliseconds\n", msec2/1000, msec2%1000);

#ifdef ENABLE_C99_SPEED_TESTS
    /* run same test using C99 dynamic arrays */
    before = clock();
    for(iter=0; iter<30000; iter++){
        test_data_type (*array2d_dynamic)[dim2] = malloc(sizeof(test_data_type[dim1][dim2]));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                array2d_dynamic[i][j] = rand();
        free(array2d_dynamic);
    }
    difference = clock() - before;
    msec3 = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - C99-style malloc time taken %d seconds %d milliseconds\n", msec3/1000, msec3%1000);
#endif
    
    if(msec2>msec)
        printf("md_malloc was %d seconds %d milliseconds SLOWER than Mangled array\n", (msec2-msec)/1000, (msec2-msec)%1000);
    else
        printf("md_malloc was %d seconds %d milliseconds FASTER than Mangled array\n", (msec-msec2)/1000, (msec-msec2)%1000);
#ifdef ENABLE_C99_SPEED_TESTS
    if(msec2>msec3)
        printf("md_malloc was %d seconds %d milliseconds SLOWER than C99-style array\n", (msec2-msec3)/1000, (msec2-msec3)%1000);
    else
        printf("md_malloc was %d seconds %d milliseconds FASTER than C99-style array\n", (msec3-msec2)/1000, (msec3-msec2)%1000);
#endif
    printf("\n");

    
    /*********************************************************************************************************/
    printf("********** Realloc Contiguity Test - RANDOM 2D DATA **********\n");
    error = 0.0f;
    before = clock();
    array2d_dynamic = (test_data_type**)malloc2d(20, 20, sizeof(test_data_type));
    for(iter=0; iter<100000; iter++){
        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;

        array2d_dynamic = (test_data_type**)realloc2d((void**)array2d_dynamic, dim1, dim2, sizeof(test_data_type));
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                array2d_dynamic[i][j] = rand()/RAND_MAX;
        /* only passes this test if "array2d_dynamic" is truely contiguous */
        memcpy(&array2d_static_rand[0], ADR2D(array2d_dynamic), dim1*dim2*sizeof(test_data_type));
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                error += fabs(array2d_dynamic[i][j]-array2d_static_rand[i*dim2 + j]);
        assert(error <= 2.23e-8f); /* if you land on this assertion, "array2d_dynamic" is not contiguously allocated */
    }
    free(array2d_dynamic);
    difference = clock() - before;
    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);


#ifdef ENABLE_CBLAS_TESTS
    /*********************************************************************************************************/
    printf("********** Malloc Contiguity Test - CBLAS WITH RANDOM 2D DATA **********\n");
    error = 0.0f;
    before = clock();
    for(iter=0; iter<20000; iter++){
        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        dim3 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
        if(dim3<1 || dim3>MAX_DIMENSION_LENGTH) dim3 = 1;

        array2d_dynamic = (test_data_type**)malloc2d(dim1, dim2, sizeof(test_data_type));
        array2d_dynamic2 = (test_data_type**)malloc2d(dim2, dim3, sizeof(test_data_type));
        array2d_dynamic3 = (test_data_type**)malloc2d(dim1, dim3, sizeof(test_data_type));

        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                array2d_static_rand[i*dim2 + j] = rand()/RAND_MAX;
        for(i=0; i<dim2; i++)
            for(j=0; j<dim3; j++)
                array2d_static_rand2[i*dim3 + j] = rand()/RAND_MAX;
        memcpy(ADR2D(array2d_dynamic),  &array2d_static_rand[0], dim1*dim2*sizeof(test_data_type));
        memcpy(ADR2D(array2d_dynamic2), &array2d_static_rand2[0], dim2*dim3*sizeof(test_data_type));
 
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim1, dim3, dim2, 1.0f,
                    ADR2D(array2d_dynamic), dim2,
                    ADR2D(array2d_dynamic2), dim3, 0.0f,
                    ADR2D(array2d_dynamic3), dim3);
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim1, dim3, dim2, 1.0f,
                    array2d_static_rand, dim2,
                    array2d_static_rand2, dim3, 0.0f,
                    array2d_static_rand3, dim3);
        for(i=0; i<dim1; i++)
            for(j=0; j<dim3; j++)
                error += fabs(array2d_dynamic3[i][j]-array2d_static_rand3[i*dim3 + j]);
        assert(error <= 2.23e-8f);
        free(array2d_dynamic);
        free(array2d_dynamic2);
        free(array2d_dynamic3);
    }
    difference = clock() - before;
    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);
#endif
 
    
    /*********************************************************************************************************/
    printf("********** Malloc Contiguity Test - 3D DATA **********\n");
    error = 0.0f;
    before = clock();
    for(iter=0; iter<400; iter++){
        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        dim3 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
        if(dim3<1 || dim3>MAX_DIMENSION_LENGTH) dim3 = 1;
        array3d_dynamic = (test_data_type***)malloc3d(dim1, dim2, dim3, sizeof(test_data_type));
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                for(k=0; k<dim3; k++)
                    array3d_dynamic[i][j][k] = rand()/RAND_MAX;
        /* only passes this test if "array3d_dynamic" is truely contiguous */
        memcpy((array3d_static), ADR3D(array3d_dynamic), dim1*dim2*dim3*sizeof(test_data_type));
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                for(k=0; k<dim3; k++)
                    error += fabs(array3d_dynamic[i][j][k]-array3d_static[i*dim2*dim3+j*dim3+k]);

        assert(error <= 2.23e-8f); /* if you land on this assertion, "array3d_dynamic" is not contiguously allocated */
        free(array3d_dynamic);
    }
    difference = clock() - before;
    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);

    
    /*********************************************************************************************************/
    printf("********** Malloc Speed Test - 3D DATA **********\n");
    before = clock();
    dim1 = MAX_DIMENSION_LENGTH-10;
    dim2 = MAX_DIMENSION_LENGTH;
    dim3 = MAX_DIMENSION_LENGTH-5;
    for(iter=0; iter<100; iter++){
        mangled_array3d_dynamic = malloc(dim1* dim2* dim3 * sizeof(test_data_type));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                for(k=0; k<dim3; k++)
                    mangled_array3d_dynamic[i*dim2*dim3 +j*dim3 +k] = rand();
        free(mangled_array3d_dynamic);
    }
    difference = clock() - before;
    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - Mangled array time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
    
    before = clock();
    for(iter=0; iter<100; iter++){
        array3d_dynamic = (test_data_type***)malloc3d(dim1, dim2, dim3, sizeof(test_data_type));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                for(k=0; k<dim3; k++)
                    array3d_dynamic[i][j][k] = rand();
        free(array3d_dynamic);
    }
    difference = clock() - before;
    msec2 = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - md_malloc time taken %d seconds %d milliseconds\n", msec2/1000, msec2%1000);
    
#ifdef ENABLE_C99_SPEED_TESTS
    /* run same test using C99 dynamic arrays */
    before = clock();
    for(iter=0; iter<100; iter++){
        test_data_type (*array3d_dynamic)[dim2][dim3] = malloc(sizeof(test_data_type[dim1][dim2][dim3]));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                for(k=0; k<dim3; k++)
                    array3d_dynamic[i][j][k] = rand();
        free(array3d_dynamic);
    }
    difference = clock() - before;
    msec3 = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - C99-style malloc time taken %d seconds %d milliseconds\n", msec3/1000, msec3%1000);
#endif
    
    if(msec2>msec)
        printf("md_malloc was %d seconds %d milliseconds SLOWER than Mangled array\n", (msec2-msec)/1000, (msec2-msec)%1000);
    else
        printf("md_malloc was %d seconds %d milliseconds FASTER than Mangled array\n", (msec-msec2)/1000, (msec-msec2)%1000);
#ifdef ENABLE_C99_SPEED_TESTS
    if(msec2>msec3)
        printf("md_malloc was %d seconds %d milliseconds SLOWER than C99-style array\n", (msec2-msec3)/1000, (msec2-msec3)%1000);
    else
        printf("md_malloc was %d seconds %d milliseconds FASTER than C99-style array\n", (msec3-msec2)/1000, (msec3-msec2)%1000);
#endif
    printf("\n");
    
    return 0;
}
