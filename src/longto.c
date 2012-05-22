/**
 * @file   longto.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Thu Aug 19 15:33:34 2010
 * 
 * @brief Файл реализации функции преобразования целого числа в строку
 * 
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <tio.h>
#include <tioerror.h>
#include <tiowerror.h>

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif //HAVE_CONFIG_H

#ifndef USE_VSPRINTF

#if (SIZEOF_LONG * 8) % 3
#  define OCT_IN_LONG  ((SIZEOF_LONG * 8)/3 + 1)
#else
#  define OCT_IN_LONG  ((SIZEOF_LONG * 8)/3)
#endif

char* longtoahex(long obj, char *out, size_t bl, char* symbs)
{
    char buff[SIZEOF_LONG*2+1] = {0};
    char *p = buff;
    int i, j;
    
    for(i=0 ; i < SIZEOF_LONG * 2; ++i, ++p)
    {
        long d = obj >> ( i << 2 );
        if (d)
            *p = symbs[d & 0xF];
        else
            break;
    }
    ++i;
    --p;
    if (!(bl>i))
        return NULL;
    for( j = 0; p >= buff; ++j, --p)
        out[j]=  *p;
    out[j]='\0';

    return out;
}




inline char* longtoHEX(long obj, char* out, size_t bl)
{
    return longtoahex(obj, out, bl, "0123456789ABCDEF");
}

inline char* longtohex(long obj, char* out, size_t bl)
{
    return longtoahex(obj, out, bl, "0123456789abcdef");
}

char* longtooct(long obj, char* out, size_t bl)
{
    
    char buff[OCT_IN_LONG + 1] = { 0 };
    char *p=buff;
    char mass[] = "01234567";
    int  i, j;
    
    for(i=0; i < OCT_IN_LONG; ++i, ++p)
    {
        long d = obj >> (i*3);
        if (d)
            *p  = mass[d & 7];
        else 
            break;
    }
    ++i;
    --p;
    if(!(i<bl))
        return NULL;
    for( j = 0; p >= buff; ++j, --p)
        out[j]=  *p;
    out[j]='\0';
    
    return out;
}


char* longtodec(long obj, char *out, size_t bl)
{
    char buff[OCT_IN_LONG + 1] = { 0 };
    char *p=buff;
    char mass[] = "0123456789";
    int i;
    long d = obj;

    if ( d < 0 )
        d = -obj;
    ++p;
    for ( ; d > 0; ++p )
    {
        *p = mass[d % 10];
        d = d / 10;
    }       
    if ( obj < 0 )
        *p = '-';
    if (!((p-buff)<bl))
        return NULL;
    --p;
    for (i = 0; p>=buff ; ++i, --p)
    {
        out[i] = *p;
    }
    *p='\0';
    return out;
}

#endif //USE_VSPRINTF
