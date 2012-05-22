/**
 * @file   compare.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Mon Jul 26 12:59:36 2010
 * 
 * @brief  Набор фуцнкций для произведения сравнения
 * 
 * Данный набор функция является вспомогательным при работе с ошибками
 * и потоками сообщений об ошибках. 
 * 
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif //HAVE_CONFIG_H

typedef long long cmptype;
#ifndef uchar
typedef unsigned char uchar;
#endif


int cmpfoo(void* a, void* b, size_t sz)
{
    int n, m, i;
    cmptype *A, *B;
    char *c, *d;
    n = sz / sizeof(cmptype);
    m = sz % sizeof(cmptype);
    A = (cmptype*)a;
    B = (cmptype*)b;    
    for ( i = 0; i < n; ++A, ++B, ++i)
    {
        if (*A < *B)
            return -1;
        if (*A > *B)
            return 1;
    }
    for ( i = 0, c=(char*)A, d=(char*)B; i < m; ++i, ++c, ++d)
    {
        if (*c < *d)
            return -1;
        if (*c > *d)
            return 1;
    }
    return 0;
}


int cmppthread_t(pthread_t *a, pthread_t *b)
{
#if SIZEOF_PTHREAD_T <= SIZEOF_LONG_LONG
    cmptype A = (cmptype)*a;
    cmptype B = (cmptype)*b;
    return B-A;
#else
    return memcmp(a, b , sizeof(pthread_t));
#endif
}


