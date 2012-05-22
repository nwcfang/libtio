/**
 * @file   debugout.c
 * @author Egorov N.V. <egorov@rti-mints.ru>
 * @date   Thu Sep 30 15:46:19 2010
 * 
 * @brief  Файл реализации вывод отладочной информации
 * 
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


#include <tio.h>
#include <tiowerror.h>
#include <tiooutput.h>
#include <tioinit.h>



int tioDebug(const char* msg)
{
    if (!tio_self_state[0].set)
        return 0;
    if ( 0 > fprintf(stderr, "(DD): %s", msg))
        return (TEFAIL);
    return 0;
}

int tioDebugF(const char* template, ... )
{
    va_list ap;
    int res;

    if (!tio_self_state[0].set)
        return 0;
    va_start( ap, template );
    res = uniformstroutput(DEBUG, template, ap);
    va_end( ap );
    return res;
}
