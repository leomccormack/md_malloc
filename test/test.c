
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* TEST CONFIGURATION */

#define ENABLE_SPEED_TESTS  /* compares m_malloc to Mangled and C99-style.  */
//C9999999999, still do speed tests, but against mangled, unless this flag is enabled
#define ENABLE_CBLAS_TESTS
#define MAX_DIMENSION_LENGTH 800
typedef float test_data_type;

#ifdef ENABLE_CBLAS_TESTS
# ifdef __APPLE__
#  include <Accelerate/Accelerate.h>
# else
/* include some other library that supports CBLAS, e.g. Intel MKL: */
#  include "mkl.h"
# endif
#endif




#define SAF_ADR2D(A) (&A[0][0])
#define SAF_ADR3D(A) (&A[0][0][0])


/* 2-Dimensional malloc functions */

void** saf_malloc2d(size_t dim1, size_t dim2, size_t data_size)
{
    size_t i, stride;
    void** ptr;
    unsigned char* p2;
    stride = dim2*data_size;
    ptr = malloc(dim1*sizeof(void*) + dim1*stride);
    p2 = (unsigned char*)(ptr + dim1);
    for(i=0; i<dim1; i++)
        ptr[i] = &p2[i*stride];
    return ptr;
}

void** saf_calloc2d(size_t dim1, size_t dim2, size_t data_size)
{
    size_t i;
    void** ptr = calloc(dim1, sizeof(void*) + dim2*data_size);
    unsigned char* p2 = (unsigned char*)(ptr + dim1);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2*data_size];
    return ptr;
}

void** saf_realloc2d(void** ptr, size_t dim1, size_t dim2, size_t data_size)
{
    size_t i;
    ptr = realloc (ptr, dim1*sizeof(void*) + dim1*dim2*data_size);
    unsigned char* p2 = (unsigned char*)(ptr + dim1);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2*data_size];
    return ptr;
}

void saf_free2d(void** ptr)
{
    if(ptr!=NULL){
        free(ptr);
        ptr = NULL;
    }
}

void*** saf_malloc3d(size_t dim1, size_t dim2, size_t dim3, size_t data_size)
{
    size_t i, j, stride1, stride2;
    void*** ptr;
    void** p2;
    unsigned char* p3;
    stride1 = dim2*dim3*data_size;
    stride2 = dim3*data_size;
    ptr = malloc(dim1*sizeof(void**) + dim1*dim2*sizeof(void*) + dim1*stride1);
    p2 = (void**)(ptr + dim1);
    p3 = (unsigned char*)(p2 + dim1*dim2);
    for(i=0;i<dim1;i++)
        ptr[i] = &p2[i*dim2];
    for(i=0;i<dim1;i++)
        for(j=0;j<dim2;j++)
            p2[i*dim2+j] = &p3[i*stride1 + j*stride2];
    return ptr;
}

void test(test_data_type** Array, int dim1, int dim2){
    int i, j;
    for(i=0; i<dim1; i++)
        for(j=0; j<dim2; j++)
            Array[i][j] = 1;
}


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
    int msec;
    clock_t difference;
    clock_t before;
#ifdef ENABLE_SPEED_TESTS
    int msec2, msec3;
#endif
    
//    /*********************************************************************************************************/
//    printf("********** Malloc Test - RANDOM 2D DATA **********\n");
//    error = 0.0f;
//    before = clock();
//    for(iter=0; iter<100000; iter++){
//        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
//        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
//        array2d_dynamic = (test_data_type**)saf_malloc2d(dim1, dim2, sizeof(test_data_type));
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                array2d_dynamic[i][j] = rand()/RAND_MAX;
//        /* only passes this test if "array2d_dynamic" is truely contiguous */
//        memcpy(&array2d_static_rand[0], SAF_ADR2D(array2d_dynamic), dim1*dim2*sizeof(test_data_type));
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                error += fabs(array2d_dynamic[i][j]-array2d_static_rand[i*dim2 + j]);
//        assert(error <= 2.23e-8f); /* if you land on this assertion, "array2d_dynamic" is not contiguously allocated */
//        saf_free2d((void**)array2d_dynamic);
//    }
//    difference = clock() - before;
//    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
//    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);
//
//
//    /*********************************************************************************************************/
//    printf("********** calloc Test - 2D DATA **********\n");
//    error = 0.0f;
//    before = clock();
//    for(iter=0; iter<1000000; iter++){
//        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
//        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
//        array2d_dynamic = (test_data_type**)saf_calloc2d(dim1, dim2, sizeof(test_data_type));
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                error += fabs(array2d_dynamic[i][j]);
//        assert(error <= 2.23e-8f); /* if you land on this assertion, "array2d_dynamic" was not correctly allocated and/or zero'd */
//        saf_free2d((void**)array2d_dynamic);
//    }
//    difference = clock() - before;
//    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
//    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);


#ifdef ENABLE_SPEED_TESTS
    /*********************************************************************************************************/
    printf("********** Malloc Test - SPEED 2D DATA **********\n");
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
        array2d_dynamic = (test_data_type**)saf_malloc2d(dim1, dim2, sizeof(test_data_type));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                array2d_dynamic[i][j] = rand();
        free(array2d_dynamic);
    }
    difference = clock() - before;
    msec2 = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - Multi-Malloc time taken %d seconds %d milliseconds\n", msec2/1000, msec2%1000);

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
    
    if(msec2>msec)
        printf("Multi-Malloc was %d seconds %d milliseconds SLOWER than Mangled array\n", (msec2-msec)/1000, (msec2-msec)%1000);
    else
        printf("Multi-Malloc was %d seconds %d milliseconds FASTER than Mangled array\n", (msec-msec2)/1000, (msec-msec2)%1000);
    if(msec2>msec3)
        printf("Multi-Malloc was %d seconds %d milliseconds SLOWER than C99-style array\n\n", (msec2-msec3)/1000, (msec2-msec3)%1000);
    else
        printf("Multi-Malloc was %d seconds %d milliseconds FASTER than C99-style array\n\n", (msec3-msec2)/1000, (msec3-msec2)%1000);
#endif
    
//    /*********************************************************************************************************/
//    printf("********** Malloc Test - REALLOC RANDOM 2D DATA **********\n");
//    error = 0.0f;
//    before = clock();
//    array2d_dynamic = (test_data_type**)saf_malloc2d(20, 20, sizeof(test_data_type));
//    for(iter=0; iter<100000; iter++){
//        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
//        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
//
//        array2d_dynamic = (test_data_type**)saf_realloc2d((void**)array2d_dynamic, dim1, dim2, sizeof(test_data_type));
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                array2d_dynamic[i][j] = rand()/RAND_MAX;
//        /* only passes this test if "array2d_dynamic" is truely contiguous */
//        memcpy(&array2d_static_rand[0], SAF_ADR2D(array2d_dynamic), dim1*dim2*sizeof(test_data_type));
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                error += fabs(array2d_dynamic[i][j]-array2d_static_rand[i*dim2 + j]);
//        assert(error <= 2.23e-8f); /* if you land on this assertion, "array2d_dynamic" is not contiguously allocated */
//    }
//    free(array2d_dynamic);
//    difference = clock() - before;
//    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
//    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);
//
//
//#ifdef ENABLE_CBLAS_TESTS
//    /*********************************************************************************************************/
//    printf("********** Malloc Test - CBLAS WITH RANDOM 2D DATA **********\n");
//    error = 0.0f;
//    before = clock();
//    for(iter=0; iter<10000; iter++){
//        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        dim3 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
//        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
//        if(dim3<1 || dim3>MAX_DIMENSION_LENGTH) dim3 = 1;
//
//        array2d_dynamic = (test_data_type**)saf_malloc2d(dim1, dim2, sizeof(test_data_type));
//        array2d_dynamic2 = (test_data_type**)saf_malloc2d(dim2, dim3, sizeof(test_data_type));
//        array2d_dynamic3 = (test_data_type**)saf_malloc2d(dim1, dim3, sizeof(test_data_type));
//
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                array2d_static_rand[i*dim2 + j] = rand()/RAND_MAX;
//        for(i=0; i<dim2; i++)
//            for(j=0; j<dim3; j++)
//                array2d_static_rand2[i*dim3 + j] = rand()/RAND_MAX;
//        memcpy(SAF_ADR2D(array2d_dynamic),  &array2d_static_rand[0], dim1*dim2*sizeof(test_data_type));
//        memcpy(SAF_ADR2D(array2d_dynamic2), &array2d_static_rand2[0], dim2*dim3*sizeof(test_data_type));
//
//        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim1, dim3, dim2, 1.0f,
//                    SAF_ADR2D(array2d_dynamic), dim2,
//                    SAF_ADR2D(array2d_dynamic2), dim3, 0.0f,
//                    SAF_ADR2D(array2d_dynamic3), dim3);
//        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dim1, dim3, dim2, 1.0f,
//                    array2d_static_rand, dim2,
//                    array2d_static_rand2, dim3, 0.0f,
//                    array2d_static_rand3, dim3);
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim3; j++)
//                error += fabs(array2d_dynamic3[i][j]-array2d_static_rand3[i*dim3 + j]);
//        assert(error <= 2.23e-8f);
//        free(array2d_dynamic);
//        free(array2d_dynamic2);
//        free(array2d_dynamic3);
//    }
//    difference = clock() - before;
//    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
//    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);
//#endif
 
//    /*********************************************************************************************************/
//    printf("********** Malloc Test - 3D DATA **********\n");
//    error = 0.0f;
//    before = clock();
//    for(iter=0; iter<1000; iter++){
//        dim1 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        dim2 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        dim3 = (int)((float)MAX_DIMENSION_LENGTH*(float)rand()/(float)RAND_MAX);
//        if(dim1<1 || dim1>MAX_DIMENSION_LENGTH) dim1 = 1;
//        if(dim2<1 || dim2>MAX_DIMENSION_LENGTH) dim2 = 1;
//        if(dim3<1 || dim3>MAX_DIMENSION_LENGTH) dim3 = 1;
//        array3d_dynamic = (test_data_type***)saf_malloc3d(dim1, dim2, dim3, sizeof(test_data_type));
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                for(k=0; k<dim3; k++)
//                    array3d_dynamic[i][j][k] = rand()/RAND_MAX;
//        /* only passes this test if "array3d_dynamic" is truely contiguous */
//        memcpy((array3d_static), SAF_ADR3D(array3d_dynamic), dim1*dim2*dim3*sizeof(test_data_type));
//        for(i=0; i<dim1; i++)
//            for(j=0; j<dim2; j++)
//                for(k=0; k<dim3; k++)
//                    error += fabs(array3d_dynamic[i][j][k]-array3d_static[i*dim2*dim3+j*dim3+k]);
//
//        assert(error <= 2.23e-8f); /* if you land on this assertion, "array3d_dynamic" is not contiguously allocated */
//        free(array3d_dynamic);
//    }
//    difference = clock() - before;
//    msec = difference * 1000.0f / (float)CLOCKS_PER_SEC;
//    printf("PASSED! - Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);
//
#ifdef ENABLE_SPEED_TESTS
    /*********************************************************************************************************/
    printf("********** Malloc Test - SPEED 3D DATA **********\n");
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
        array3d_dynamic = (test_data_type***)saf_malloc3d(dim1, dim2, dim3, sizeof(test_data_type));
        /* populate array */
        for(i=0; i<dim1; i++)
            for(j=0; j<dim2; j++)
                for(k=0; k<dim3; k++)
                    array3d_dynamic[i][j][k] = rand();
        free(array3d_dynamic);
    }
    difference = clock() - before;
    msec2 = difference * 1000.0f / (float)CLOCKS_PER_SEC;
    printf(" - Multi-Malloc time taken %d seconds %d milliseconds\n", msec2/1000, msec2%1000);
    
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
    
    if(msec2>msec)
        printf("Multi-Malloc was %d seconds %d milliseconds SLOWER than Mangled array\n", (msec2-msec)/1000, (msec2-msec)%1000);
    else
        printf("Multi-Malloc was %d seconds %d milliseconds FASTER than Mangled array\n", (msec-msec2)/1000, (msec-msec2)%1000);
    if(msec2>msec3)
        printf("Multi-Malloc was %d seconds %d milliseconds SLOWER than C99-style array\n\n", (msec2-msec3)/1000, (msec2-msec3)%1000);
    else
        printf("Multi-Malloc was %d seconds %d milliseconds FASTER than C99-style array\n\n", (msec3-msec2)/1000, (msec3-msec2)%1000);
#endif
    
    return 0;
}
